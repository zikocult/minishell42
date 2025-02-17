/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/02/17 16:17:06 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_par(t_parse *node, int (*func) (char *))
{
	int		i;
	int		result;
	t_par	*temp;

	result = 0;
	temp = node->head;
	while (temp)
	{
		if (temp->command)
			result = func(temp->command);
		if (temp->parameter)
			result = func(temp->parameter);
		if (temp->infile || temp->outfile)
		{
			i = 0;
			while (temp->infile[i++])
				result = func(temp->infile[i]);
			while (temp->outfile[i++])
				result = func(temp->outfile[i]);
		}
		temp = temp->next;
		return (result);
	}
	return (result);
}

char	process_data(t_parse *node, t_env *data, int (*func)(char **, t_env *))
{
	int		i;
	t_par	*temp;

	temp = node->head;
	while (temp)
	{
		if (temp->command)
			func(&temp->command, data);
		if (temp->parameter)
			func(&temp->parameter, data);
		if (temp->infile || temp->outfile)
		{
			i = 0;
			while (temp->infile[i++])
				func(&temp->infile[i], data);
			while (temp->outfile[i++])
				func(&temp->outfile[i], data);
		}
		temp = temp->next;
		return (1);
	}
	return (0);
}
