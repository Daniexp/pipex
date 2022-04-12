/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:11:25 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/12 18:36:46 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc == 5)
		parse_command_line(argc, argv);
	else
		perror("./pipex infile command1 command2 outfile\n");
	pid = fork();
	if (!pid)
		printf("Soy el hijo (%d, hijo de %d)\n", getpid(), getppid());
	else
		printf("Soy el padre (%d, hijo de %d)\n", getpid(), getppid());
}
