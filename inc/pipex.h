/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:36:25 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/13 21:03:03 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*	INCLUDES	*/
# include "../src/libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/types.h>

/*	STRUCTURES	*/
typedef struct s_arg
{
	char	**cmd;
	int		fd[2];
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
/*		pipex_utils.c			*/
void	initialize_struct_pipe(char **arg, t_var *res);
/*		pipex.c					*/
void	pipex(t_var *var);
#endif
