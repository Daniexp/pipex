/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <dexposit@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:47:53 by dexposit          #+#    #+#             */
/*   Updated: 2022/04/26 19:11:25 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/pipex_bonus.h"

void	check_exec(t_var *var, char **envp, char *cmd)
{
	// aqui vamos a comprobar como funciona access y execve
	//en acces comprobamos los permisos de ejecucion de un path por lo que
//puede ser la ruta absoluta como "/usr/bin/ls -la" con o sin argumentos eso da igual o puede ser un sinónimo como ls -la o ruta relativa cono ../ o ./?? revisar si shell lo permite con script¿¿
// execve resive ruta split envp
//access un path
	//la ruta es /usr/bin/cmd y el split es 0ls 1-la y asi...
	char	**split;

	split = ft_split(cmd, ' ');
	if (!split)
		exit(EXIT_FAILURE);
	if (access(*split, X_OK))
		execve(*split, split, envp);
	
}
