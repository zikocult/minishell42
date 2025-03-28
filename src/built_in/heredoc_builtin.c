/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:10:13 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/03/27 17:02:38 by gbaruls-         ###   ########.fr       */
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

static char	*free_strjoin(char *s1, const char *s2)
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

static char	*read_to_finish(char *delimiter, t_env *data)
{
	char	*line;
	char	*content;

	content = ft_strdup("");
	line = ft_strdup("");
	data->heredoc_delimeter = ft_strdup(delimiter);
	here_signals();
	while (content) 
	{
		if (line)
			free(line);
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (!line)
				handle_heredoc_eof(data);
			break ;
		}
		content = free_strjoin(content, line);
		content = free_strjoin(content, "\n");
	}
	if (line)
		free(line);
	return (content);
}

int	process_heredoc(char *delimiter, t_env *data, char *command)
{
	char	*heredoc_content;
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		heredoc_content = read_to_finish(delimiter, data);
		end_heredoc(heredoc_content, command, data);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status)
		{
			free(data->heredoc_delimeter);
			data->heredoc_delimeter = NULL;
			status = 130;
		}
	}
	restore_signals();
	return (status);
}
