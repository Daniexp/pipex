/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:11:25 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/27 21:21:48 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv, char **envp)
{
	t_var	var;

	if (argc < 4)
	{
		perror("./pipex infile cmd ... cmd outfile\n");
		exit(EXIT_FAILURE);
	}
	check_heredoc(argc, argv, &var);
	pipex(&var, envp, 0);
}

void	pipex(t_var *arg, char **envp, t_pipe *pipant)
{
	static int	calls = 0;
	int			cnt;
	t_pipe		pipsig;

	cnt = arg->nmb_cmd - ++calls;
	pipe(pipsig.end);
	if (cnt == 0)
		change_in_out_cmd(&(arg->fin), &(pipant->end[1]));
	else
	{
		pipsig.id = fork();
		if (pipsig.id < 0)
			return (perror("fork fail... \n"), exit(EXIT_FAILURE));
		if (pipsig.id == 0)
			pipex(arg, envp, &pipsig);
		else if (cnt == arg->nmb_cmd - 1)
			change_in_out_cmd(&(pipsig.end[0]), &(arg->fout));
		else
			change_in_out_cmd(&(pipsig.end[0]), &(pipant->end[1]));
	}
	close_unused(arg, &pipsig, pipant);
	check_exec(envp, arg->cmd[cnt]);
	free_doublestr(arg->cmd);
}

void	close_unused(t_var *var, t_pipe *pip1, t_pipe *pip2)
{
	if (pip2 != 0)
	{
		close(pip2->end[0]);
		close(pip2->end[1]);
	}
	close(var->fin);
	close(var->fout);
	close(pip1->end[0]);
	close(pip1->end[1]);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	*path_cmd;
	char	**env_path;
	char	**split_cmd;
	int		i;

	split_cmd = ft_split(cmd, ' ');
	rute_absolute(envp, cmd);
	if (*envp == NULL)
		return (perror("command not found"), exit(EXIT_FAILURE));
	env_path = take_cmd_path_of_env((const char **) envp);
	i = -1;
	while (env_path[++i])
	{
		path_cmd = join_str(env_path[i], "/", split_cmd[0]);
		if (access(path_cmd, X_OK) == 0)
			execve(path_cmd, split_cmd, envp);
		free(path_cmd);
	}
	free_doublestr(split_cmd);
	free_doublestr(env_path);
	perror("command not found");
	exit(EXIT_FAILURE);
}

void	free_doublestr(char **str)
{
	char	**aux;

	aux = str;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(aux);
}
