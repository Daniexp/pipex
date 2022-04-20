/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:11:25 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/20 14:40:56 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

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
	hijo ->	cmd1 cmd2 cmd3 si existe un cmd entre el ultimo y el que ejecutamos,  crea un proceso hijo y leera de el pipe al pipe.
	si no existe ese cmd en medio pues ejecutara el cmd como sin bonus.
	Tenemos dos partes diferenciadas heredoc y multiples cmd.
	1- Multiples comandos.
	2- Heredoc y << >>.
*/
int	main(int argc, char **argv, char **envp)
{
	t_var	var;

	if (parse_command_line(argc, argv) < 0)
		return (0);
	initialize_struct_pipe(argc, argv, &var);
	pipex(&var, envp);
}

void	pipex(t_var *arg, char **envp)
{
	static int	calls=0;
	int			cnt;
	t_pipe		pip;
	pid_t		id;
	int			status;
	
	cnt  = arg->nmb_cmd - calls;
	calls++;
	cnt--;
	if (cnt == 0)
	{
		printf("Aquí realizaremos el commando de infile a pipe\n");
		exit(EXIT_FAILURE);
	}
	else 
	{
		//Crear el proceso y llamar con siguiente commando
		pipe(pip.end);
		id = fork();
		if (id < 0)
			return (perror("fork fail... \n"), exit(EXIT_FAILURE));
		if (id == 0)
			pipex(arg, envp);
		else
		{
			waitpid(id, &status, 0);
			if (cnt == arg->nmb_cmd - 1)
				printf("Aquí ejecutaremos el ultimo commando a outfile\n");
			else
				printf("Aqui ejecutaremos el resto de procesos de pipe a pipe\n");
			exit(EXIT_FAILURE);
		}
	}
	/*if (!pip.id)
		printf("proceso hijo\n");
		//child_process(arg->f1, arg->cmd1, &pip, envp);
	else
		printf("proceso padre\n");
		//parent_process(arg->f2, arg->cmd2, &pip, envp);
*/}
void	do_process(t_var *var, char **envp, t_pipe * pip,  int n)
{
	//depende de que proceso ejecutemos tendremos unos in out y unos
	//fd distintos para cerrar.
	//cambiar in out.
	//close fd sin usar del proceso.
	//ejecutar commmando.
	if (n == 0)
	{
		change_in_out_cmd(var->fin, pip->end[1]);
		//close_unused_fd(var->fin, pip->end[0], pip->end[1]);
	}
	else if (n == var->nmb_cmd - 1)
	{
		change_in_out_cmd(pip->end[0], var->fout);
		//close_unused_fd();
	}
	else
	{
		change_in_out_cmd(pip->end[1], pip->end[0]);
		//close_unused_fd();
	}
	//revisar si podemos cerrar aqui todo.
	close_unused_fd(var->fin, var->fout, pip->end[0], pip->end[1]);
	exec_cmd(var->cmd[n], envp);
}

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
		perror("Command not found\n");
	free(split_cmd);
	free(env_path);
	exit(EXIT_FAILURE);
}
