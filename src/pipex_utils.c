/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:01:37 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/25 22:38:51 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	initialize_struct_pipe(char **arg, t_var *res)
{
	res->cmd1 = arg[2];
	res->cmd2 = arg[3];
	res->f1 = open(arg[1], O_RDONLY);
	res->f2 = open(arg[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (res->f1 < 0 || res->f2 < 0)
		return (perror("Check the files permits.\n"), exit(EXIT_FAILURE));
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
