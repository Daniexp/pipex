/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:26:12 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/12 21:20:33 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	parse_command_line(int argv, char **arg)
{
	int		res;

	res = check_file(arg[1], F_OK);
	res = check_file(arg[argv - 1], F_OK);
	return (res);
}

int	check_file(char *str, char md)
{
	int	res;

	res = access(str, md);
	if (res < 0)
	{
		perror("At least one file don't exists or don't have permissions.\n");
		exit(EXIT_FAILURE);
	}
	return (res);
}
