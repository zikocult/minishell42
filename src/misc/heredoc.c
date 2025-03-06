/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:57:46 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/03/06 18:57:47 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	end_heredoc(t_env *data)
{
	free(data->heredoc_delimeter);
	data->heredoc_delimeter = NULL;
}

static char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

static void	write_heredoc(char *heredoc_content, int fd)
{
	if (fd == -1)
		write(STDOUT_FILENO, heredoc_content, ft_strlen(heredoc_content));
	else
		write(fd, heredoc_content, ft_strlen(heredoc_content));
	free(heredoc_content);
}

void	process_heredoc(const char *delimiter, t_env *data, int fd)
{
	char	*line;
	char	*heredoc_content;

	heredoc_content = ft_strdup("");
	data->heredoc_delimeter = ft_strdup(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			handle_heredoc_eof(data);
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		heredoc_content = ft_strjoin_free(heredoc_content, line);
		heredoc_content = ft_strjoin_free(heredoc_content, "\n");
		free(line);
	}
	write_heredoc(heredoc_content, fd);
	end_heredoc(data);
}
