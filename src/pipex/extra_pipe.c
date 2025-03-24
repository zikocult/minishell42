/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:08:35 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/24 16:36:25 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_pipes(t_parse *state)
{
    int count;
    t_par *current;

	count = 0;
	current = state->head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return (count - 1);
}

/* char **get_argv_from_parse(t_par *current) */
/* { */
/*     char **argv; */
/*     int argc = 0; */

/*     // Contamos los argumentos del comando */
/*     t_par *temp = current;  // Usamos un puntero temporal para recorrer la lista */
/*     while (temp != NULL) */
/*     { */
/*         argc++; */
/*         temp = temp->next; */
/*     } */

/*     // Asignamos memoria para argv */
/*     argv = malloc((argc + 1) * sizeof(char *)); */
/*     if (!argv) */
/*     { */
/*         perror("malloc"); */
/*         exit(EXIT_FAILURE);  // En caso de error al asignar memoria */
/*     } */

/*     // Llenamos el arreglo argv con los comandos */
/*     temp = current;  // Reiniciamos el puntero temporal */
/*     int i = 0; */
/*     while (temp != NULL) */
/*     { */
/*         argv[i] = ft_strdup(temp->command);  // Copiamos el comando en argv */
/*         temp = temp->next; */
/*         i++; */
/*     } */
/*     argv[argc] = NULL;  // Terminamos con NULL */
/*     return argv; */
/* } */

void execute_pipex(t_parse *state, t_env *data)
{
	int		num_pipes;
//	int		**pipes;
	int		num_commands;

	num_pipes = count_pipes(state);
	num_commands = num_pipes + 1;
	if (num_commands < 1)
		return;
	/* pipes = create_big_pip(num_pipes); */
	/* create_pipes(pipes, num_pipes); */
	execute_command(state, data);	
	/* close_pipes(pipes, num_pipes); */
	/* wait_for_children(num_commands); */
//	free_pipes(pipes, num_pipes);
}	
