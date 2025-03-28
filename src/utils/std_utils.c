/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/14 18:49:32 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	internal_infile(t_par *temp, t_env *data,
	int (*func)(char **, t_env *), int *control)
{
	int	i;

	i = 0;
	while (temp->infile[i])
	{
		if (func(&temp->infile[i], data))
			(*control)++;
		i++;
	}
}

static void	internal_outfile(t_par *temp, t_env *data,
	int (*func)(char **, t_env *), int *control)
{
	int	i;

	i = 0;
	while (temp->outfile[i])
	{
		if (func(&temp->outfile[i], data))
			(*control)++;
		i++;
	}
}

static int	internal_data(t_par *temp, t_env *data,
	int (*func)(char **, t_env *), int *control)
{
	if (temp->command && func(&temp->command, data))
		(*control)++;
	if (temp->parameter && func(&temp->parameter, data))
		(*control)++;
	if (temp->infile)
		internal_infile(temp, data, func, control);
	if (temp->outfile)
		internal_outfile(temp, data, func, control);
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
