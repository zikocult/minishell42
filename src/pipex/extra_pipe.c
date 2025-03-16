/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:08:35 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/16 14:05:00 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_pipes(t_parse *state)
{
    int count = 0;
    t_par *current = state->head;

    // Recorremos la lista de comandos
    while (current != NULL)
    {
        if (ft_strchr(current->command, '|'))  // Si hay un pipe en el comando
            count++;
        current = current->next;
    }

    return count;
}

char **get_argv_from_parse(t_par *current)
{
    char **argv;
    int argc = 0;

    // Contamos los argumentos del comando
    t_par *temp = current;  // Usamos un puntero temporal para recorrer la lista
    while (temp != NULL)
    {
        argc++;
        temp = temp->next;
    }

    // Asignamos memoria para argv
    argv = malloc((argc + 1) * sizeof(char *));
    if (!argv)
    {
        perror("malloc");
        exit(EXIT_FAILURE);  // En caso de error al asignar memoria
    }

    // Llenamos el arreglo argv con los comandos
    temp = current;  // Reiniciamos el puntero temporal
    int i = 0;
    while (temp != NULL)
    {
        argv[i] = ft_strdup(temp->command);  // Copiamos el comando en argv
        temp = temp->next;
        i++;
    }
    argv[argc] = NULL;  // Terminamos con NULL
    return argv;
}

void execute_pipex(t_parse *state, t_env *data)
{
	int				num_pipes;
	int				**pipes;

	// Contar número de comandos en la lista enlazada
	t_par *current = state->head;
	int num_commands = 0;
	while (current)
	{
		num_commands++;
		current = current->next;
	}

	// Si no hay comandos, terminamos
	if (num_commands < 1)
		return;

	// Configuración de pipes
	num_pipes = num_commands - 1;
	pipes = create_big_pip(num_pipes);

	// Configuración de cmd_data
	/* cmd_data.argc = num_commands + 3;  // Simulamos argc para que pipex funcione */
	/* cmd_data.argv = get_argv_from_parse(state->head); */
	/* cmd_data.env = env_to_array(data); */
	/* cmd_data.find = enviroment(cmd_data.env); */

	// Ejecutar pipeline
	create_pipes(pipes, num_pipes);
	execute_command(state, data, pipes, num_pipes);	
	close_pipes(pipes, num_pipes);
	wait_for_children(num_commands);

	// Liberar memoria
//	free(cmd_data.find);
	free_pipes(pipes, num_pipes);
//	free_memory(cmd_data.argv);
}	
