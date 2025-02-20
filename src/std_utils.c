/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/02/20 18:06:25 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_data(t_parse *node, t_env *data, int (*func)(char **, t_env *))
{
	int		i;
	t_par	*temp;
	int		control;
	
	temp = node->head;
	while (temp)
	{
		control = 0;
		if (temp->command)
			if (func(&temp->command, data))
				control++;
		if (temp->parameter)
			if (func(&temp->parameter, data))
				control++;
		if (temp->infile)
		{
			i = 0;
			while (temp->infile[i])
				if (func(&temp->infile[i++], data))
					control++;
		}
		if (temp->outfile)
		{
			i = 0;
			while (temp->outfile[i])
				if (func(&temp->outfile[i++], data))
					control++;

		}
		temp = temp->next;
		if (control > 0)
			return (1);
	}
	return (0);
}
