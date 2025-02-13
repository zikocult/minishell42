/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2025/02/13 17:34:18 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_process(char *path, t_par *current)
{
	pid_t	pid;
	int		*status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, &current->command, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, status, 0);
	else
		perror("Error en fork");
}

static void	execute_command2(t_par *current, t_env *data)
{
	char	*path;

	path = check_path(current, data);
	child_process(path, current);
	free(path);
}

static int	dollar_search(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	if (str[i] == '$')
		return (i);
	return (0);
}

static int	single_quotes(t_par *current)
{
	int		i;
	int		len;
	char	*new_com;

	len = ft_strlen(current->command) - 1;
	if (current->command[0] == '\'' && current->command[len] == '\'')
	{
		new_com = malloc(len);
		i = 0;
		while (++i < len)
			new_com[i - 1] = current->command[i];
		free(current->command);
		current->command = new_com;
		printf("%s\n", current->command);
		return (1) ;
	}
	else if((current->command[0] == '\'' && current->command[len] != '\''
			) || (current->command[0] != '\'' && current->command[len] == '\''))	
	{
		printf("syntax error \n");
		return (1);
	}
	return (0);
}

static int	handle_dollar(t_par *current, t_env *data)
{
	int i;
	char *temp;
	char *expansion;

	if (ft_strchr(current->command, '$'))
	{
		i = dollar_search(current->command);
		temp = ft_strndup(current->command, i);
		if (current->command[i++] == '$')
		{
			expansion = expand_variable(&current->command[i], data);
			if (!expansion)
				return (1);
			else
			{
				free(current->command);
				current->command = ft_strjoin(temp, expansion);
			}
		}
		free(temp);
	}
	return (0);
}

void	execute_command(t_parse *parse_data, t_env *data)
{
	t_par	*current;

	current = parse_data->head;
	while (current)
	{
		if (single_quotes(current))
		{
			current = current->next;
			continue ;
		}
		if (handle_dollar(current, data))
		{
			current = current->next;
			continue ;
		}
		if (!current->command)
		{
			current = current->next;
			continue ;
		}
		execute_command2(current, data);
		current = current->next;
	}
}
