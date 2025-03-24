/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:09:11 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/24 17:59:30 by pamanzan         ###   ########.fr       */
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

void execute_command(t_parse *state, t_env *data)
{
    t_par   *current;
    int     i, pid, status;
    int     command_count;
    char    *path;
    
    command_count = count_pipes(state) + 1;
    int pipes[command_count - 1][2]; 
    current = state->head;

    // Crear los pipes
    i = 0;
    while (i < command_count - 1) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    i = 0;
    while (current) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Proceso hijo
            // Redirigir entrada si es necesario
            if (i == 0 && current->infile) {
                int fd_in = open(current->infile[0], O_RDONLY);
                if (fd_in == -1) {
                    perror("open infile");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            } else if (i > 0) {
                dup2(pipes[i - 1][READ_END], STDIN_FILENO);
            }

            // Redirigir salida si es necesario
            if (i == command_count - 1 && current->outfile) {
                int fd_out = open(current->outfile[0], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
                if (fd_out == -1) {
                    perror("open outfile");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            } else if (i < command_count - 1) {
                dup2(pipes[i][WRITE_END], STDOUT_FILENO);
            }

            // Cerrar TODOS los pipes en los procesos hijos
            int j = 0;
            while (j < command_count - 1) {
                close(pipes[j][READ_END]);
                close(pipes[j][WRITE_END]);
                j++;
            }

            // Buscar el path del comando
            path = check_path(current, data);

            // Construir el array de argumentos correctamente
            char *args[] = {current->command, current->parameter, NULL};
            execve(path, args, NULL);

            /* perror("execve"); */
            exit(EXIT_FAILURE);
        }

        // *** IMPORTANTE ***
        // Cerrar pipes en el proceso padre para evitar escrituras redundantes
        if (i > 0) {
            close(pipes[i - 1][READ_END]);
        }
        if (i < command_count - 1) {
            close(pipes[i][WRITE_END]);
        }

        current = current->next;
        i++;
    }

    // Esperar a que terminen todos los procesos hijos
    i = 0;
    while (i < command_count) {
        wait(&status);
        i++;
    }
}

