/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:49:24 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/16 09:52:42 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*enviroment(char **env)
{
	int		i;
	int		found;
	char	*copy;

	copy = NULL;
	found = 0;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			copy = ft_strdup(env[i]);
			found = 1;
			break ;
		}
		i++;
	}
	if (!found)
		printf("no encontrado :<");
	return (copy);
}

char	*find_path(char *copy, char *command)
{
	int		i;
	char	*full_path;
	char	*path;
	char	**result;
	int		found;

	found = 0;
	result = ft_split(copy, ':');
	free(copy);
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
}

void	free_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	**create_big_pip(int num_pipes)
{
	int	**pipes;
	int	i;

	pipes = malloc(num_pipes * sizeof(int *));
	if (pipes == NULL)
	{
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (pipes[i] == NULL)
		{
			perror("Error al asignar memoria");
			while (i > 0)
				free(pipes[--i]);
			free(pipes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}
