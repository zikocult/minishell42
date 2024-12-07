/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2024/12/07 10:16:16 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

char	*find_path(char *command, t_env_vars *env)
{
	int		i;
	char	*full_path;
	char	*path;
	char	**result;
	int		found;
//	char	*copy;

//	copy = getenv("PATH");
	found = 0;
	result = ft_split(env->path, ':');

	i = 0;
	while (result[i++] != NULL)
	{
		path = ft_strjoin(result[i], "/");
		full_path = ft_strjoin(path, command);
		free(path);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			break ;
		}
		free(full_path);
	}
	if (!found)
		ft_printf("Comando no encontrado");
	return (free_memory(result), full_path);
}

