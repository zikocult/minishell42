/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:10:13 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/03/27 14:16:18 by Guillem Barulls  ###   ########.fr       */
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
		content = ft_strjoin_free(content, line);
		content = ft_strjoin_free(content, "\n");
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
		// printf("Status = %i\n", status);
		// if (WIFEXITED(status) && WEXITSTATUS(status) == 1) ...
		// lo siguiente es equivalente, pero como no sé si se pueden usar estas macros..
		// WIFEXITED verifica que el proceso hijo terminó correctamente
		// WEXITSTATUS revisa el valor del código exit()
		// if (((status)&0xFF) == 0 && ((status >> 8) & 0xFF) == 1)
		if (status)
		{
			free(data->heredoc_delimeter);
			data->heredoc_delimeter = NULL;
		}
	}
	interactive_signals();
	return (status);
}
