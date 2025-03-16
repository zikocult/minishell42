/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:08:35 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/16 12:51:57 by pamanzan         ###   ########.fr       */
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
