/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:11:25 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/19 10:37:14 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_var	var;

	if (parse_command_line(argc, argv) < 0)
		return (0);
	initialize_struct_pipe(argv, &var);
	pipex(&var, envp);
}

void	pipex(t_var *arg, char **envp)
{
	t_pipe	pip;

	pipe(pip.end);
	pip.id = fork();
	if (pip.id < 0)
		return (perror("It wasn't possible to do fork.\n"), exit(EXIT_FAILURE));
	if (!pip.id)
		child_process(arg->f1, arg->cmd1, &pip, envp);
	else
		parent_process(arg->f2, arg->cmd2, &pip, envp);
}

/*if (dup2(pip->end[1], 1) < 0)
return(perror("Couldn't dup child stdout.\n"), exit(EXIT_FAILURE));
if (close(pip->end[0]) != 0)
return(perror("Couldn't close read extreme of the pipe.\n"), exit(EXIT_FAILURE));
	*/
void	child_process(int fd, char *cmd, t_pipe *pip, char **envp)
{
	if (dup2(fd, 0) < 0)
		return (perror("Couldn't dup child stdin.\n"), exit(EXIT_FAILURE));
	dup2(pip->end[1], 1);
	close(pip->end[0]);
	close(fd);
	close(pip->end[0]);
	exec_cmd(cmd, envp);
	perror("No ha sido posible ejecutar el commando");
	exit(EXIT_FAILURE);
}

	//int	status;

	//waitpid(pip->id, &status, 0);
	/*if (dup2(fd, 1) < 0)
		return(perror("Can't dup parent stdout.\n"), exit(EXIT_FAILURE));
	if (dup2(pip->end[0], 1) < 0)
		return(perror("Can't dup parent stdin.\n"), exit(EXIT_FAILURE));
	if (close(pip->end[1] != 0))
		return(perror("Error: can't close write pipe side.\n"), exit(EXIT_FAILURE));
	*/
void	parent_process(int fd, char *cmd, t_pipe *pip, char **envp)
{
	dup2(pip->end[0], 0);
	dup2(fd, 1);
	close(pip->end[1]);
	close(pip->end[0]);
	close(fd);
	exec_cmd(cmd, envp);
	perror("No ha sido posible ejecutar el commando");
	exit(EXIT_FAILURE);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	*path_cmd;
	char	**env_path;
	char	**split_cmd;
	int		i;

	env_path = take_cmd_path_of_env((const char **) envp);
	split_cmd = ft_split(cmd, ' ');
	i = -1;
	while (env_path[++i])
	{
		path_cmd = join_str(env_path[i], "/", split_cmd[0]);
		execve(path_cmd, split_cmd, envp);
		free(path_cmd);
	}
	if (!env_path[i])
		perror("Command not found");
	free(split_cmd);
	free(env_path);
	exit(EXIT_FAILURE);
}
