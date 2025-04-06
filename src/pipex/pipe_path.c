/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:49:24 by pamanzan          #+#    #+#             */
/*   Updated: 2025/04/06 11:19:14 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*char **enviroment(t_env *data)
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
}*/

char **enviroment(t_env *data)
{
    t_var *var;
    int count;
    char **env;
    int i;
    int j;
    int len;

    count = 0;
    var = data->head;
    while (var)
    {
        count++;
        var = var->next;
    }

    env = (char **)malloc((count + 1) * sizeof(char *));
    if (!env)
        return (NULL);

    i = 0;
    var = data->head;
    while (var)
    {
        len = ft_strlen(var->var_name) + ft_strlen(var->content) + 2;
        env[i] = (char *)malloc(len);
        if (!env[i])
        {
            j = 0;
            while (j < i)
            {
                free(env[j]);
                j++;
            }
            free(env);
            return (NULL);
        }
        ft_strcpy(env[i], var->var_name);
        ft_strcat(env[i], "=");
        ft_strcat(env[i], var->content);
        i++;
        var = var->next;
    }
    env[i] = NULL;
    return (env);
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
	printf("hay %i pipes,\n", num_pipes);
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
