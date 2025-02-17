/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 23:34:30 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/02/17 23:34:55 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	validate_quotes(char *cmd_buff)
{
	int		i;
	bool	in_single_quotes;
	bool	in_double_quotes;

	i = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (cmd_buff[i])
	{
		if (cmd_buff[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (cmd_buff[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		i++;
	}
	if (in_single_quotes || in_double_quotes)
	{
		printf("minishell: parse_error: unclosed quotes\n");
		return (false);
	}
	return (true);
}
