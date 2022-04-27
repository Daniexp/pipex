/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:36:25 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/27 20:08:02 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*	INCLUDES	*/
# include <libft.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/types.h>

/*	STRUCTURES	*/
typedef struct s_arg_bonus
{
	char	**cmd;
	int		nmb_cmd;
	char	*lmt;
	int		fin;
	int		fout;
}	t_var;

typedef struct s_pipe
{
	int		end[2];
	pid_t	id;
}	t_pipe;
/*		FUNCTIONS PROTOTYPES	*/
/*		parse_command_line.c	*/
void	check_heredoc(int argc, char **argv, t_var *arg);
int		parse_command_line(int argv, char **arg);
int		check_file(char *str, char md);
char	**take_cmd_path_of_env(char const **envp);
void	create_auxfin(t_var *var);
/*		pipex_utils.c			*/
void	initialize_struct_pipe(int argc, char **arg, t_var *res);
char	**save_cmds(int argc, char **argv);
char	*join_str(char *start, char *mid, char *end);
void	change_in_out_cmd(int *fin, int *fout);
void	rute_absolute(char **envp, char *cmd);
/*		exec_utils.c			*/
void	check_exec(char **envp, char *cmd);
/*		pipex.c					*/
void	pipex(t_var *arg, char **envp, t_pipe *pipant);
void	close_unused(t_var *var, t_pipe *pip1, t_pipe *pip2);
void	exec_cmd(char *cmd, char **envp);
void	free_doublestr(char **str);

#endif
