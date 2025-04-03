/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:08:35 by pamanzan          #+#    #+#             */
/*   Updated: 2025/04/03 19:24:05 by pamanzan         ###   ########.fr       */
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

void execute_pipex(t_parse *state, t_env *data)
{
	/* int		num_pipes; */
	/* int		num_commands; */

	/* num_pipes = count_pipes(state); */
	/* num_commands = num_pipes + 1; */
	/* if (num_commands < 2) */
	/* { */
	/* 	execute_command(current, data); */
	/* } */
	handle_pipes(state, data);	
}	
