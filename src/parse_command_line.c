/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:26:12 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/14 20:08:50 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	parse_command_line(int argv, char **arg)
{
	int	res;

	res = 0;
	if (argv != 5)
		return (perror("./pipex infile command command outfile\n"), -1);
	res = check_file(arg[1], F_OK);
	if (res >= 0)
		res = check_file(arg[argv - 1], F_OK);
	return (res);
}

int	check_file(char *str, char md)
{
	int	res;

	res = access(str, md);
	if (res < 0)
	{
		perror("At least one file doesn't exists.\n");
		//exit(EXIT_FAILURE);
	}
	return (res);
}

char	*take_cmd_path_of_env(char const **envp)
{
	char	*paths;
	char	**split_paths;

	/*while (*envp)
	{
		//printf("%s", *envp++);
		if (!ft_strncmp("PATH", *envp, 4))
			printf("%s", *envp);
		envp++;
	}*/
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	paths = ft_strchr(*envp, '/');
	split_paths = ft_split(paths, ':');
	char **aux;
	aux = split_paths;
	while (*aux)
		printf("%s", *aux++);
	free(split_paths);
	printf("\n");
	return ("finish");
}
