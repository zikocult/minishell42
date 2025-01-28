/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:32:18 by Guillem Bar       #+#    #+#             */
/*   Updated: 2025/01/28 17:10:27 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_temp_data(t_parse *data)
{
	if (data->command)
		free(data->command);
	if (data->parameter)
		free(data->parameter);
	if (data->infile)
		free(data->infile);
	if (data->outfile)
		free(data->outfile);
	if (data->a_infile)
		free(data->a_infile);
	if (data->a_outfile)
		free(data->a_outfile);
}

void	copy_data(t_par *new_node, t_parse *data)
{
	if (data->command)
		new_node->command = ft_strdup(data->command);
	if (data->parameter)
		new_node->parameter = ft_strdup(data->parameter);
	if (data->infile)
		new_node->infile = ft_strdup(data->infile);
	if (data->outfile)
		new_node->outfile = ft_strdup(data->outfile);
	if (data->a_infile)
		new_node->a_infile = ft_strdup(data->a_infile);
	if (data->a_outfile)
		new_node->a_outfile = ft_strdup(data->a_outfile);
}

void	add_node(t_parse *data)
{
	t_par	*new_node;

	new_node = (t_par *)malloc(sizeof(t_par));
	if (!new_node)
		return ;
	init_newnode(new_node);
	copy_data(new_node, data);
	free_temp_data(data);
	if (!data->head)
	{
		data->head = new_node;
		data->tail = new_node;
	}
	else
	{
		data->tail->next = new_node;
		data->tail = new_node;
	}
	init_data(data);
}
