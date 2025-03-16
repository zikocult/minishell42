/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2025/03/16 08:51:35 by pamanzan         ###   ########.fr       */
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
	{
		if (execve(path, &current->command, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, status, 0);
	else
		perror("Error en fork");
}

void	execute_command(t_par *current, t_env *data)
{
	char	*path;

	path = check_path(current, data);
	if (!path)
		return ;
	child_process(path, current);
	free(path);
}

static int	try_processes(t_parse *parse_data, t_env *data)
{
	if (process_data(parse_data, data, expand_mult))
		return (1);
	if (process_data(parse_data, data, handle_dollar))
		return (1);
	if (process_data(parse_data, data, double_simple_dollar))
		return (1);
	if (process_data(parse_data, data, simple_double_dollar))
		return (1);
	if (process_data(parse_data, data, double_quotes_dollar))
		return (1);
	if (process_data(parse_data, data, single_quotes))
		return (1);
	else
		return (0);
}

void	start_expansion(t_parse *parse_data, t_env *data)
{
	t_par	*current;

	current = parse_data->head;
	while (current)
	{
		if (try_processes(parse_data, data))
		{
			execute_command(current, data);
			current = current->next;
			continue ;
		}
		if (!current->command)
		{
			current = current->next;
			continue ;
		}
		execute_command(current, data);
		current = current->next;
	}
}
