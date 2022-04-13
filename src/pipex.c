/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:11:25 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/13 21:04:11 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv)
{
	t_var	var;

	if(parse_command_line(argc, argv) < 0)
		return (0);
	initialize_struct_pipe(argv, &var);
	//pipex(&var);
}

void	pipex(t_var *var)
{
	t_pipe pip;

	printf("llega");
	pipe(pip.end);
	printf("llega");
	pip.id = fork();
	printf("llega");
	if (pip.id < 0)
		return (perror("It wasn't possible to do fork."), exit(EXIT_FAILURE));
	if (!pip.id)
		printf("EStamos en el proceso hijo que creamos con fork");
	else
		printf("EStamos en el procesa padre");
}

