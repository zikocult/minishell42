/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:37:35 by pamanzan          #+#    #+#             */
/*   Updated: 2024/12/05 13:07:22 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"


void	free_memory(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

char	*find_path(char *command)
{
	int		i;
	char	*full_path;
	char	*path;
	char	**result;
	int		found;
	char	*copy;

	copy = getenv("PATH");
	found = 0;
	result = ft_split(copy, ':');

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
