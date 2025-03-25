/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:10:13 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/03/25 19:07:15 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_heredoc_eof(t_env *data)
{
	printf("warning: here-document delimited by end-of-file (wanted `%s\')\n",
		data->heredoc_delimeter);
	if (data->heredoc_delimeter)
	{
		free(data->heredoc_delimeter);
		data->heredoc_delimeter = NULL;
	}
}

static char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

static void	end_heredoc(char *heredoc_content, char *command, t_env *data)
{
	if (!ft_strcmp(command, "cat"))
		printf("%s", heredoc_content);
	free(heredoc_content);
	free(data->heredoc_delimeter);
	data->heredoc_delimeter = NULL;
}

void	process_heredoc(char *delimiter, t_env *data, char *command)
{
	char	*line;
	char	*heredoc_content;

	heredoc_content = ft_strdup("");
	data->heredoc_delimeter = ft_strdup(delimiter);
	g_in_heredoc = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			handle_heredoc_eof(data);
			break ;
		}
		if (!ft_strcmp(line, delimiter) || g_in_heredoc == 2)
		{
			free(line);
			break ;
		}
		heredoc_content = ft_strjoin_free(heredoc_content, line);
		heredoc_content = ft_strjoin_free(heredoc_content, "\n");
		free(line);
	}
	end_heredoc(heredoc_content, command, data);
}
