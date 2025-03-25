/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:49:24 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/25 18:50:24 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdlib.h>
#include <string.h>

char **enviroment(t_env *data)
{
    t_var *var;
    int count = 0;
    char **env;
    int i = 0;

    // Contar cuántas variables de entorno hay
    var = data->head;
    while (var)
    {
        count++;
        var = var->next;
    }

    // Reservar memoria para el array de strings (+1 para NULL al final)
    env = (char **)malloc((count + 1) * sizeof(char *));
    if (!env)
        return (NULL);

    // Llenar el array con las variables de entorno
    var = data->head;
    while (var)
    {
        // Reservar espacio para "VAR=VAL\0"
        int len = strlen(var->var_name) + strlen(var->content) + 2;
        env[i] = (char *)malloc(len);
        if (!env[i])
            return (NULL);

        // Construir el string manualmente
        strcpy(env[i], var->var_name);  // Copiar "VAR"
        strcat(env[i], "=");            // Agregar "="
        strcat(env[i], var->content);   // Agregar "VALUE"

        i++;
        var = var->next;
    }
    env[i] = NULL; // Último elemento NULL para `execve`

    return env;
}


/* char	*find_path(char *copy, char *command) */
/* { */
/* 	int		i; */
/* 	char	*full_path; */
/* 	char	*path; */
/* 	char	**result; */
/* 	int		found; */

/* 	found = 0; */
/* 	result = ft_split(copy, ':'); */
/* 	free(copy); */
/* 	i = 0; */
/* 	while (result[i++] != NULL) */
/* 	{ */
/* 		path = ft_strjoin(result[i], "/"); */
/* 		full_path = ft_strjoin(path, command); */
/* 		free(path); */
/* 		if (access(full_path, X_OK) == 0) */
/* 		{ */
/* 			found = 1; */
/* 			break ; */
/* 		} */
/* 		free(full_path); */
/* 	} */
/* 	if (!found) */
/* 		ft_printf("Comando no encontrado"); */
/* 	return (free_memory(result), full_path); */
/* } */

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
