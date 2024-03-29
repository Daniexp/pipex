/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:01:37 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/27 21:19:10 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	initialize_struct_pipe(int argc, char **arg, t_var *res)
{
	res->cmd = save_cmds(argc, arg);
	res->nmb_cmd = argc - 3;
	res->fin = open(arg[1], O_RDONLY);
	res->fout = open(arg[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (res->fin < 0 || res->fout < 0)
		return (perror("Check the files permits.\n"), exit(EXIT_FAILURE));
}

char	**save_cmds(int argc, char **argv)
{
	int		x_arg;
	int		x_cmd;
	char	**res;

	res = ft_calloc(argc - 2, sizeof(char *));
	x_arg = 1;
	x_cmd = 0;
	while (argv[++x_arg] && x_arg < argc - 1)
		res[x_cmd++] = ft_substr(argv[x_arg], 0, ft_strlen(argv[x_arg]));
	res[x_cmd] = 0;
	return (res);
}

char	*join_str(char *start, char *mid, char *end)
{
	char	*join;
	char	*res;

	if (start == 0 || mid == 0 || end == 0)
		return (NULL);
	join = ft_strjoin(start, mid);
	if (!join)
		perror("fail join start to mid");
	res = ft_strjoin(join, end);
	if (!res)
		perror("fail join join to mid");
	free(join);
	return (res);
}

void	change_in_out_cmd(int *fin, int	*fout)
{
	if (dup2(*fin, 0) < 0)
		return (perror("Fails the dup to cmd in\n"), exit(EXIT_FAILURE));
	if (dup2(*fout, 1) < 0)
		return (perror("Fails the dup to cmd out\n"), exit(EXIT_FAILURE));
}

void	rute_absolute(char **envp, char *cmd)
{
	char	**split_cmd;
	char	**aux;

	split_cmd = ft_split(cmd, '/');
	aux = split_cmd;
	while (*(split_cmd + 1))
	{
		free(*split_cmd);
		split_cmd++;
	}
	if (access(*split_cmd, X_OK))
		execve(cmd, split_cmd, envp);
	free(*split_cmd);
	free(aux);
}
