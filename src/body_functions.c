/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:01 by patri             #+#    #+#             */
/*   Updated: 2025/01/28 19:01:31 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void print_token(t_parse *data)
{
	t_par	*current;

	current = data->head;
	printf("\n**************");
    while (current)
    {
        printf("\nCommand: %s\nParameter: %s\nInfile: %s\nOutfile: %s\nA_Infile: %s\nA_Outfile: %s\n\n**************\n",
        current->command, current->parameter, current->infile, current->outfile, current->a_infile, current->a_outfile);
        current = current->next;
	}
}

int	select_type(char *command_buff, t_env *data)
{
	t_parse	state;


	state.head = NULL;
	state.tail = NULL;
	if (!data->head)
		printf("Hello world\n");
	init_data(&state);
	if (!validate_cmdbuff(command_buff))
		return (0);
	parse_token(command_buff, &state);
	print_token(&state);
	// if (!args[0])
	// 	return (0);
	if (!ft_strcmp(&state.head->command[0], "patata"))
	{
	 	printf("%s 👾\n", "chachi piruli!!!");
	 //	free(state);
	 	return (0);
	}
	// else if (!ft_strcmp(args[0], "echo"))
	// {
	// 	handle_echo(args);
	// 	free_memory(args);
	// 	return (0);
	// }
	// else if (!ft_strcmp(args[0], "env"))
	// 	env_builtin(data);
	if (!ft_strcmp(&state.head->command[0], "exit"))
	{
		rl_clear_history();
	// 	free_memory(args);
	 	return (1);
	}
	// else
	// {
	// 	execute_command(args, data);
	// 	free_memory(args);
	// 	return (0);
	// }
	free_parse(&state);
	return (0);
}
