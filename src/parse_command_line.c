/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:26:12 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/12 22:08:11 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	parse_command_line(int argv, char **arg)
{
	int	res;
	int	i;
	char	*str;

	res = check_file(arg[1], F_OK);
	res = check_file(arg[argv - 1], F_OK);
	i = 2;
	while (arg[i])
	{	
		res = check_file(arg[i], X_OK);
		free (str);
		printf("acces result is: %d\n", res);
		i++;
	}
	return (res);
}

int	check_file(char *str, char md)
{
	int	res;

	res = access(str, md);
	if (res < 0)
	{
		printf("archivo: %s\n", str);
		perror("Fail in the access of a file or command that don't exists.\n");
		exit(EXIT_FAILURE);
	}
	return (res);
}
