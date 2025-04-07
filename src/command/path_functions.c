/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:42:45 by pamanzan          #+#    #+#             */
/*   Updated: 2025/04/07 18:06:00 by pamanzan         ###   ########.fr       */
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

	// Buscar la variable PATH en la estructura t_env
	search = data->head;
	while (search && ft_strncmp(search->var_name, "PATH", 4) != 0)
		search = search->next;
	if (!search)
		return (NULL);

	// Separar los directorios de PATH
	paths = ft_split(search->content, ':');
	if (!paths || !*paths) // Evitar segfault si paths es NULL
		return (NULL);
	
	i = 0;
	full_path = NULL;
	while (paths[i])
	{
		full_path = get_full_path(paths[i], current->command);
		if (access(full_path, X_OK) == 0)
			break;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_memory(paths);
	return (full_path);
}

static int	path_messages(char *str)
{
	int	i;
	int	file;
	int	directory;

	i = 0;
	file = 0;
	directory = 0;
	while (str[i])
	{
		if (str[i] == '.')
			file = 1;
		else if (str[i] == '/')
			directory = 1;
		i++;
	}
	if (str[0] == '/' && file != 1)
		printf("%s: Is a directory\n", str); //CAMBIAR PRINTFS POR FUNCION CON WRITE PARA QUE
	else if (str[0] != '/')
		printf("%s: command NOT found\n", str); // SALIDA MENSAJE SEA STDERROR I NO STDOUPUT
	else if (file == 1 && directory == 1)
		printf("%s: Perimssion denied\n", str);
	return (0);
}

char	*check_path(t_par *current, t_env *data)
{
	char	*path;

	path = find_path(current, data);
	if (!path)
	{
		path_messages(current->command);
		return (NULL);
	}
	return (path);
}
