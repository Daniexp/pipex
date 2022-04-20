/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:36:25 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/20 14:39:37 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*	INCLUDES	*/
# include "../src/libft/libft.h"
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
int		parse_command_line(int argv, char **arg);
int		check_file(char *str, char md);
char	**take_cmd_path_of_env(char const **envp);
/*		pipex_utils.c			*/
void	initialize_struct_pipe(int argc, char **arg, t_var *res);
char	**save_cmds(int argc, char **argv);
char	*join_str(char *start, char *mid, char *end);
void	change_in_out_cmd(int fin, int fout);
void	close_unused_fd(int f1, int f2, int f3, int f4);
/*		pipex.c					*/
void	pipex(t_var *arg, char **envp);
void	child_process(int fd, char *cmd, t_pipe *pip, char **envp);
void	parent_process(int fd, char *cmd, t_pipe *pip, char **envp);
void	do_process(t_var *var, char **envp, t_pipe *pip, int n);
void	exec_cmd(char *cmd, char **envp);

#endif
