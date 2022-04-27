/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:47:53 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/27 17:56:42 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

void	check_exec(char **envp, char *cmd)
{
	char	**split;

	split = ft_split(cmd, ' ');
	if (!split)
		exit(EXIT_FAILURE);
	if (access(cmd, X_OK))
		execve(*split, split, envp);
	exec_cmd(cmd, envp);
}
