/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:26:46 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/01/28 10:33:46 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	init_newnode(t_par *new_node)
{
	new_node->command = NULL;
	new_node->parameter = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->a_infile = NULL;
	new_node->a_outfile = NULL;
	new_node->next = NULL;
}

void	init_data(t_parse *data)
{
	data->command = NULL;
	data->parameter = NULL;
	data->infile = NULL;
	data->outfile = NULL;
	data->a_infile = NULL;
	data->a_outfile = NULL;
}

void	free_parse(t_parse *data)
{
	t_par	*current;
	t_par	*next;

	current = data->head;
	while (current)
	{
		next = current->next;
		if (current->command)
			free(current->command);
		if (current->parameter)
			free(current->parameter);
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		if (current->a_outfile)
			free(current->a_outfile);
		if (current->a_infile)
			free(current->a_infile);
		free(current);
		current = next;
	}
	data->head = NULL;
	data->tail = NULL;
}
