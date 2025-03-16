/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:51:23 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/16 13:04:26 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void setup_first_command(int i, t_parse *state, int **pipes)
{
    int fd_in;
    t_par *current;
    int j = 0;

    // Obtener el primer comando en la lista de comandos
    current = state->head;
    while (current != NULL && j < i - 1)  // Avanzamos hasta el comando adecuado
    {
        current = current->next;
        j++;
    }

    // Verificar si el archivo de entrada (infile) es válido
    if (current && current->infile)
    {
        // Abrir el archivo de entrada en modo solo lectura
        fd_in = open(*current->infile, O_RDONLY);
        if (fd_in == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        // Redirigir la entrada estándar (stdin) desde el archivo de entrada
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }

    // Redirigir la salida estándar (stdout) al pipe[i - 2]
    if (i > 2)
    {
        dup2(pipes[i - 2][1], STDOUT_FILENO);
    }
}

void setup_last_command(int i, t_parse *state, int **pipes)
{
    int fd_out;
    t_par *current;
    int j = 0;

    // Obtener el último comando en la lista de comandos
    current = state->head;
    while (current != NULL && j < i - 1)  // Avanzamos hasta el comando adecuado
    {
        current = current->next;
        j++;
    }

    // Verificar si el archivo de salida (outfile) es válido
    if (current && current->outfile)
    {
        // Abrir el archivo de salida en modo escritura (O_WRONLY, O_CREAT, O_TRUNC)
        fd_out = open(*current->outfile, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
        if (fd_out == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Redirigir la entrada estándar (stdin) al pipe[i - 3]
        if (i > 2)
        {
            dup2(pipes[i - 3][0], STDIN_FILENO);
        }

        // Redirigir la salida estándar (stdout) al archivo de salida
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}

void	setup_intermediate_command(int i, int **pipes)
{
	dup2(pipes[i - 3][0], STDIN_FILENO);
	dup2(pipes[i - 2][1], STDOUT_FILENO);
}

void	setup_redirection(int i, t_parse *state, int **pipes)
{
	t_par	*current;
	int		num_commands;

	// Contamos el número de comandos en la lista enlazada
	current = state->head;
	num_commands = 0;
	while (current)
	{
		num_commands++;
		current = current->next;
	}

	// Determinar qué configuración aplicar según la posición del comando
	if (i == 0)
		setup_first_command(i, state, pipes);
	else if (i == num_commands - 1)
		setup_last_command(i, state, pipes);
	else
		setup_intermediate_command(i, pipes);
}
