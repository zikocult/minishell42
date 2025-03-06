/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:57:39 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/03/06 18:57:41 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_heredoc_active(t_env *data)
{
	return (data->heredoc_delimeter != NULL);
}

void	handle_heredoc_eof(t_env *data)
{
	printf("warning: here-document delimited by end-of-file (wanted `%s\')\n",
		data->heredoc_delimeter);
	free(data->heredoc_delimeter);
	data->heredoc_delimeter = NULL;
}

