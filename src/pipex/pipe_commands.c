/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:09:11 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/16 13:00:33 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (i > 0)
			{
				close(pipes[--i][0]);
				close(pipes[i][1]);
			}
			free_pipes(pipes, num_pipes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

/* void	execute_commands(t_command_data *cmd_data, int **pipes, int num_pipes) */
/* { */
/* 	int	pid; */
/* 	int	i; */

/* 	i = 2; */
/* 	while (i < cmd_data->argc - 1) */
/* 	{ */
/* 		pid = fork(); */
/* 		if (pid == -1) */
/* 		{ */
/* 			perror("fork"); */
/* 			exit(EXIT_FAILURE); */
/* 		} */
/* 		if (pid == 0) */
/* 			exec_child(i, cmd_data, pipes, num_pipes); */
/* 		i++; */
/* 	} */
/* } */

void exec_child(int i, t_parse *state, int **pipes, int num_pipes, t_env *data)
{
    char    **result;
    char    *path;
    t_par   *current_command;
    int     j;

    // Obtener el comando correspondiente en la lista de comandos
    current_command = state->head;
    j = 0;

    // Recorrer hasta el i-ésimo comando (el índice i empieza desde 0)
    while (j < i)
    {
        current_command = current_command->next;
        j++;
    }

    // Verificar si el comando existe
    if (!current_command || !current_command->command)
    {
        perror("Invalid command");
        exit(EXIT_FAILURE);
    }

    // Configurar la redirección si es necesario (por ejemplo, redirigir archivos)
    setup_redirection(i, state, pipes);

    // Cerrar los pipes que no son necesarios para este proceso hijo
    close_pipes(pipes, num_pipes);

    // Dividir el comando en sus argumentos
    result = ft_split(current_command->command, ' ');

    // Buscar el path del comando utilizando la función find_path, pasando 'data' que es de tipo 't_env'
    path = find_path(current_command, data);  // Cambié 'state->env' por 'data'

    // Verificar si find_path devolvió un path válido
    if (!path)
    {
        perror("Command not found");
        exit(EXIT_FAILURE);
    }

    // Ejecutar el comando con execve
    if (execve(path, result, NULL) == -1)  // También cambié 'state->env' por 'data->env'
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // Si execve falla, liberar memoria y terminar el proceso
    free(path);
    free(result);
    exit(EXIT_FAILURE);
}
void	wait_for_children(int argc)
{
	int	i;
	int	status;

	i = 0;
	while (i < argc - 3)
	{
		wait(&status);
		i++;
	}
}
