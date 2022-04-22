/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:26:12 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/22 11:00:33 by dexposit         ###   ########.fr       */
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

void	check_heredoc(int argc, char **argv, t_var *arg)
{
	if (ft_strlen(argv[1]) == 8 && !ft_strncmp(argv[1], "here_doc", 8))
	{
	arg->lmt = ft_substr(argv[2], 0, ft_strlen(argv[2]));
		if (argc < 6)
			return (perror("./pipex here\\_doc LIMIT md cmd1 file\n"),
				exit(EXIT_FAILURE));
		arg->nmb_cmd = argc - 4;
		arg->cmd = save_cmds(argc - 1, argv + 1);
		create_auxfin(arg);
		arg->fout = open(argv[argc - 1], O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (arg->fout < 0)
			return (perror("fail to open fout\n"), exit(EXIT_FAILURE));
	}
	else
	{
		if (parse_command_line(argc, argv) < 0)
			exit(EXIT_FAILURE);
		initialize_struct_pipe(argc, argv, arg);
	}
}

void	create_auxfin(t_var *var)
{
	int		res;
	int		fd;
	char	*read;
	t_pipe	pip;

	pipe(pip.end);
	read = get_next_line(0);
	while (ft_strlen(var->lmt) != ft_strlen(read) - 1
		|| ft_strncmp(read, var->lmt, ft_strlen(var->lmt)))
	{
		ft_putstr_fd(read, pip.end[1]);
		free(read);
		read = get_next_line(0);
	}
	free(read);
	var->fin = pip.end[0];
	if (close(pip.end[1]) < 0)
		perror("no ha sido posible cerrar este lado del pipe");
}
