/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:11:25 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/27 20:09:06 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*
	CAMBIOS A EFECTUAR PARA REALIZAR BONUS
	Lo primero es que si infile es heredocs tenemos que leer
	de stdin es decir de la pantalla hasta leer >heredoc o similar
	revisar subject bonus.
	si es sel caso usaramos las asignacions dobles >> << por lo que
	tendremos que identificar cual puso y si son estas pues escribiremos
	al final de lo que este en el outfile
	En otro caso tendremos el pipex inicial pero debe funcionar para x
	commandos no para 2 exclusivamente.
	para ello ahora mismo:
	hijo -> ejecuta primer com desde infile a pipe
	padre -> ejecuta segundo comm desde el pipe a outfile
	BONUS
	hijo ->	cmd1 cmd2 cmd3 si existe un cmd entre el ultimo y el que ejecutamos
,  crea un proceso hijo y leera de el pipe al pipe.
	si no existe ese cmd en medio pues ejecutara el cmd como sin bonus.
	Tenemos dos partes diferenciadas heredoc y multiples cmd.
	1- Multiples comandos.
	2- Heredoc y << >>.
*/

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
		exit(EXIT_FAILURE);
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
