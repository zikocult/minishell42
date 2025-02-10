/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:42:45 by pamanzan          #+#    #+#             */
/*   Updated: 2025/02/10 17:45:40 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_full_path(char *path, char *command)
{
	char	*full_path;
	char	*temp_path;

	temp_path = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp_path, command);
	free(temp_path);
	return (full_path);
}

char	*find_path(t_par *current, t_env *data)
{
	char	**paths;
	char	*full_path;
	int		i;
	t_var	*search;

	search = env_search(data, "PATH");
	if (!search)
		return (NULL);
	paths = ft_split(search->content, ':');
	if_notstr(*paths);
	i = 0;
	full_path = NULL;
	while (paths[i])
	{
		full_path = get_full_path(paths[i], current->command);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_memory(paths);
	if_notstr(full_path);
	return (full_path);
}

static void	path_messages(char *str)
{
	int	i;
	int	file;

	i = 0;
	file = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			printf("%s: Perimssion denied\n", str);
			file = 1;
		}
		i++;
	}
	if (str[0] == '/' && file != 1)
		printf("%s: Is a directory\n", str);
	else if (str[0] != '/')
		printf("%s: command NOT found\n", str);
}

char	*check_path(t_par *current, t_env *data)
{
	char	*path;
//PONER EN ESTA FUNCION COMPROBANTE DE QUE LA VARIABLE EXISTE ANTES DE PRINTAR MENSAJES 
	path = find_path(current, data);
	if (!path)
	{
		path_messages(current->command);
		current = current->next;
		return (NULL);
	}
	return (path);
}
