/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:09:11 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/31 17:56:13 by pamanzan         ###   ########.fr       */
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
    int     num_pipes;
    char    *path;
	int		**pipes;
    
    num_pipes = count_pipes(state);
    current = state->head;

    // Crear los pipes
	pipes = create_big_pip(num_pipes);
	create_pipes(pipes, num_pipes);

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
				close(pipes[i - 1][READ_END]);
            }

            // Redirigir salida si es necesario
            if (i == num_pipes && current->outfile) {
                int fd_out = open(current->outfile[0], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
                if (fd_out == -1) {
                    perror("open outfile");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            } else if (i < num_pipes) {
                dup2(pipes[i][WRITE_END], STDOUT_FILENO);
				close(pipes[i][WRITE_END]);
            }

            // Cerrar TODOS los pipes en los procesos hijos
			close_pipes(pipes, num_pipes);

            // Buscar el path del comando
            path = check_path(current, data);

            // Construir el array de argumentos correctamente
			// empieza funcion para esplitear y joinear comando y parametro
			
			if (current->command)
			{
				char **param = NULL;
				int k = 0;
				int count = 0;
				if (current->parameter)
				{
					param = ft_split(current->parameter, ' ');
					while (param && param[count])
						count++;
				}
				char **res;
				res = malloc(sizeof(char *) * (count + 2));
				res[0] = ft_strdup(current->command);
				if (current->parameter)
				{
					while (param[k])
					{
						res[k + 1] = ft_strdup(param[k]);
						free(param[k]);
						k++;
					}
					free(param);
				}
				res[k + 1] = '\0';
				char **env = enviroment(data);
				execve(path, res, env);			
			}

            /* perror("execve"); */
            exit(EXIT_FAILURE);
        }

        // *** IMPORTANTE ***
        // Cerrar pipes en el proceso padre para evitar escrituras redundantes
        if (i > 0) {
            close(pipes[i - 1][READ_END]);
        }
        if (i < num_pipes) {
            close(pipes[i][WRITE_END]);
        }

        current = current->next;
        i++;
    }

    // Esperar a que terminen todos los procesos hijos
    i = 0;
    while (i < num_pipes) {
        wait(&status);
        i++;
    }
	free_pipes(pipes, num_pipes);

}

