/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:08:35 by pamanzan          #+#    #+#             */
/*   Updated: 2025/04/15 16:27:22 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes(t_parse *state)
{
	int		count;
	t_par	*current;

	count = 0;
	current = state->head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count - 1);
}

/* int	count_param(t_par *current, char ***param) */
/* { */
/* 	int	count; */

/* 	count = 0; */
/* 	if (current->parameter) */
/* 	{ */
/* 		*param = ft_split(current->parameter, ' '); */
/* 		while (*param && (*param)[count]) */
/* 			count++; */
/* 	} */
/* 	return (count); */
/* } */

int	count_outfile(t_par *current)
{
	int	count;

	count = 0;
	while (current->outfile[count])
		count++;
	return (count);
}

int	count_vars(t_env *data)
{
	t_var	*var;
	int		count;

	count = 0;
	var = data->head;
	while (var)
	{
		count++;
		var = var->next;
	}
	return (count);
}
