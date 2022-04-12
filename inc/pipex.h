/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:36:25 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/12 18:43:38 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*	INCLUDES	*/
# include "../src/libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

/*	FUNCTIONS PROTOTYPES	*/
int	parse_command_line(int argv, char **arg);
int	check_file(char *str, char md);

#endif
