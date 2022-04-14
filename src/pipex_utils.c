/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:01:37 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/14 17:47:33 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	initialize_struct_pipe(char **arg, t_var *res)
{
	res->cmd1 = arg[2];
	res->cmd2 = arg[3];
	res->f1 = open(arg[1], O_RDONLY);
	res->f2 = open(arg[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
//	res.fd[1] = open(arg[4], O_RDWR);
		if (res->f1 < 0 || res->f2 < 0)
			return (perror("Check the files permissions.\n"), exit(EXIT_FAILURE));
}
