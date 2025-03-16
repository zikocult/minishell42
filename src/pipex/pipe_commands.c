/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:09:11 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/16 14:18:55 by pamanzan         ###   ########.fr       */
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

void execute_command(t_parse *state, t_env *data, int **pipes, int num_pipes)
{
    t_par   *current;
    int     i;
    pid_t   pid;
    int     status;

    current = state->head;
    i = 0;

    while (current)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) // Proceso hijo
            exec_child(i, state, pipes, num_pipes, data);

        current = current->next;
        i++;
    }

    // Esperar a que todos los hijos terminen usando while
    i = 0;
    while (i < num_pipes + 1)
    {
        waitpid(-1, &status, 0); // Esperar cualquier hijo
        i++;
    }
}

void exec_child(int i, t_parse *state, int **pipes, int num_pipes, t_env *data)
{
    t_par   *current_command;
    char    **args;
    char    *path;
 //   char    **envp;
    int     j;

    // Obtener el comando correspondiente en la lista de comandos
    current_command = state->head;
    j = 0;
    while (j < i && current_command)
    {
        current_command = current_command->next;
        j++;
    }

    if (!current_command || !current_command->command)
    {
        perror("Invalid command");
        exit(EXIT_FAILURE);
    }

    // Configurar redirección de pipes
    setup_redirection(i, state, pipes);

    // Cerrar los pipes innecesarios
    close_pipes(pipes, num_pipes);

    // Dividir comando en argumentos
    args = ft_split(current_command->command, ' ');

    // Obtener la ruta del comando
    path = find_path(current_command, data);

    if (!path)
    {
        fprintf(stderr, "Command not found: %s\n", current_command->command);
        exit(EXIT_FAILURE);
    }

    // Convertir el entorno a un array
 //   envp = env_to_array(data);

    // Ejecutar el comando
    if (execve(path, args, NULL) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }

    free(path);
    free(args);
//    free(envp);
    exit(EXIT_FAILURE);
}

/* void execute_command(t_parse *state, t_env *data, int **pipes, int num_pipes) */
/* { */
/* 	t_par	*current; */
/* 	int		pid; */
/* 	int		i; */

/* 	current = state->head; */
/* 	i = 0; */

/* 	while (current) */
/* 	{ */
/* 		pid = fork(); */
/* 		if (pid == -1) */
/* 		{ */
/* 			perror("fork"); */
/* 			exit(EXIT_FAILURE); */
/* 		} */
/* 		if (pid == 0) // Proceso hijo */
/* 		{ */
/* 			exec_child(i, state, pipes, num_pipes, data); */
/* 		} */

/* 		current = current->next; */
/* 		i++; */
/* 	} */
/* } */

/* void exec_child(int i, t_parse *state, int **pipes, int num_pipes, t_env *data) */
/* { */
/*     char    **result; */
/*     char    *path; */
/*     t_par   *current_command; */
/*     int     j; */

/*     // Obtener el comando correspondiente en la lista de comandos */
/*     current_command = state->head; */
/*     j = 0; */

/*     // Recorrer hasta el i-ésimo comando (el índice i empieza desde 0) */
/*     while (j < i) */
/*     { */
/*         current_command = current_command->next; */
/*         j++; */
/*     } */

/*     // Verificar si el comando existe */
/*     if (!current_command || !current_command->command) */
/*     { */
/*         perror("Invalid command"); */
/*         exit(EXIT_FAILURE); */
/*     } */

/*     // Configurar la redirección si es necesario (por ejemplo, redirigir archivos) */
/*     setup_redirection(i, state, pipes); */

/*     // Cerrar los pipes que no son necesarios para este proceso hijo */
/*     close_pipes(pipes, num_pipes); */

/*     // Dividir el comando en sus argumentos */
/*     result = ft_split(current_command->command, ' '); */

/*     // Buscar el path del comando utilizando la función find_path, pasando 'data' que es de tipo 't_env' */
/*     path = find_path(current_command, data);  // Cambié 'state->env' por 'data' */

/*     // Verificar si find_path devolvió un path válido */
/*     if (!path) */
/*     { */
/*         perror("Command not found"); */
/*         exit(EXIT_FAILURE); */
/*     } */

/*     // Ejecutar el comando con execve */
/*     if (execve(path, result, NULL) == -1)  // También cambié 'state->env' por 'data->env' */
/*     { */
/*         perror("execve"); */
/*         exit(EXIT_FAILURE); */
/*     } */

/*     // Si execve falla, liberar memoria y terminar el proceso */
/*     free(path); */
/*     free(result); */
/*     exit(EXIT_FAILURE); */
/* } */
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
