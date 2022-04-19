/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:26:12 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/19 16:57:52 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

int	parse_command_line(int argv, char **arg)
{
	int	res;

	res = 0;
	if (argv <= 4)
		return (perror("./pipex infile cmd1 ... last_cmd outfile\n"), -1);
	res = check_file(arg[1], F_OK);
	return (res);
}

int	check_file(char *str, char md)
{
	int	res;

	res = access(str, md);
	if (res < 0)
		perror("Read file don't exists.\n");
	return (res);
}

char	**take_cmd_path_of_env(char const **envp)
{
	char	*paths;
	char	**split_paths;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	paths = ft_strchr(*envp, '/');
	split_paths = ft_split(paths, ':');
	if (!split_paths)
		return (perror("Error in envp PATH\n"), exit(1), NULL);
	return (split_paths);
}
