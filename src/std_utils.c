/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/02/24 17:19:44 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	internal_data(t_par *temp, t_env *data,
	int (*func)(char **, t_env *), int *control)
{
	int	i;

	if (temp->command)
		if (func(&temp->command, data))
			(*control)++;
	if (temp->parameter)
		if (func(&temp->parameter, data))
			(*control)++;
	if (temp->infile)
	{
		i = 0;
		while (temp->infile[i])
		{
			if (func(&temp->infile[i], data))
				(*control)++;
			i++;
		}
	}
	if (temp->outfile)
	{
		i = 0;
		while (temp->outfile[i])
		{
			if (func(&temp->outfile[i], data))
				(*control)++;
			i++;
		}
	}
	return (0);
}

int	process_data(t_parse *node, t_env *data, int (*func)(char **, t_env *))
{
	t_par	*temp;
	int		control;

	control = 0;
	temp = node->head;
	while (temp)
	{
		internal_data(temp, data, func, &control);
		temp = temp->next;
	}
	if (control > 0)
		return (1);
	return (0);
}
