/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2025/02/22 20:32:44 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	child_process(char *path, t_par *current)
{
	pid_t	pid;
	int		*status;

	status = 0;
	pid = fork();
	if (pid == 0)
		execve(path, &current->command, NULL);
	else if (pid > 0)
		waitpid(pid, status, 0);
	else
		perror("Error en fork");
}

static void	execute_command2(t_par *current, t_env *data)
{
	char	*path;

	path = check_path(current, data);
	if (!path)
		return ;
	child_process(path, current);
	free(path);
}

/*void	execute_command(t_parse *parse_data, t_env *data)
{
	t_par	*current;

	current = parse_data->head;
	while (current)
	{
		if (process_data(parse_data, data, single_quotes))
		{
			execute_command2(current, data);
			current = current->next;
			continue ;
		}
		if (process_data(parse_data, data, double_simple_dollar))
		{
			execute_command2(current, data);
		 	current = current->next;
			continue ;
		}
		if (process_data(parse_data, data, double_quotes_dollar))
		{
			execute_command2(current, data);
			current = current->next;
			continue ;
		}
		if (process_data(parse_data, data, handle_dollar))
		{
			execute_command2(current, data);
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
}*/

static int	try_processes(t_par *current, t_parse *parse_data, t_env *data)
{
	if (process_data(parse_data, data, single_quotes))
	{
		execute_command2(current, data);
		return (1);
	}
	if (process_data(parse_data, data, double_simple_dollar))
	{
		execute_command2(current, data);
		return (1);
	}
	if (process_data(parse_data, data, double_quotes_dollar))
	{
		execute_command2(current, data);
		return (1);
	}
	if (process_data(parse_data, data, handle_dollar))
	{
		execute_command2(current, data);
		return (1);
	}
	return (0);
}

void	execute_command(t_parse *parse_data, t_env *data)
{
	t_par	*current;

	current = parse_data->head;
	while (current)
	{
		if (try_processes(current, parse_data, data))
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
