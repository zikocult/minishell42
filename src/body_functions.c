/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:01 by patri             #+#    #+#             */
/*   Updated: 2025/04/15 16:36:05 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_token(t_parse *data)
{
	t_par	*current;
	int		i;

	current = data->head;
	printf("\n**************\n");
    while (current)
    {
        printf("\nCommand: %s\n", current->command);
		if (current->parameter)
		{
			i = 0;
			while (current->parameter[i])
			{
				printf("parameter[%d]: %s\n", i, current->parameter[i]);
				i++;
			}
		}
		else 
			printf("parameter: No parameters\n");
		if (current->infile)
		{
			i = 0;
			while (current->infile[i])
			{
				printf("Infile[%d]: %s\n", i, current->infile[i]);
				i++;
			}
		}
		else 
			printf("Infile: No infiles\n");
		if (current->outfile)
		{
			i = 0;
			while (current->outfile[i])
			{
				printf("Outfile[%d]: %s\n", i, current->outfile[i]);
				i++;
			}
		}
		else 
			printf("Outfile: No Outfiles\n");
		printf("\n******************\n");
        current = current->next;
    }
}

int	select_type(char *command_buff, t_env *data)
{
	t_parse	state;

	state.head = NULL;
	state.tail = NULL;
	init_data(&state, 1);
	if (!validate_cmdbuff(command_buff))
		return (0);
	parse_token(command_buff, &state);
	if (!ft_strcmp(&state.head->command[0], "cd"))
	{
		run_cd(data, state.head->parameter);
	 	free_parse(&state);
	 	return (0);
	}
	if (!ft_strcmp(&state.head->command[0], "exit"))
	{
		rl_clear_history();
		free_parse(&state);
	 	return (1);
	}
	else
	 	start_expansion(&state, data);
	print_token(&state);
	free_parse(&state);
	return (0);
}
