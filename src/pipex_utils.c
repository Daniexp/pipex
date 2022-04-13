/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:01:37 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/13 21:00:08 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	initialize_struct_pipe(char **arg, t_var *res)
{
	res->cmd[0] = arg[2];
	res->cmd[1] = arg[3];
	res->fd[0] = open(arg[1], O_RDONLY);
	res->fd[1] = open(arg[4], O_CREAT | O_RDWR | O_TRUNC);
//	res.fd[1] = open(arg[4], O_RDWR);
		if (res->fd[0] < 0 || res->fd[1] < 0)
			return (perror("Check the files permissions.\n"), exit(EXIT_FAILURE));
}
