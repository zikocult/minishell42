/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/02/24 17:09:35 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	internal_data(t_par *temp, t_env *data,
	int (*func)(char **, t_env *), int *control)
{
	int		i;
	t_par	*temp;

	temp = node->head;
	while (temp)
	{
		if (temp->command)
			func(&temp->command);
		if (temp->parameter)
			func(&temp->parameter);
		if (temp->infile)
		{
			i = 0;
			while (temp->infile[i])
				func(&temp->infile[i++]);
		}
		if (temp->outfile)
		{
			i = 0;
			while (temp->outfile[i])
				func(&temp->outfile[i++]);
		}
		temp = temp->next;
		return (1);
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
