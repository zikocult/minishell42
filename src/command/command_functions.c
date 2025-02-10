/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2025/02/10 17:15:02 by pamanzan         ###   ########.fr       */
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

static void	next_node(t_par *current)
{
	if (!current->command && !current->infile && !current->outfile)
	{
		if (current->next)
			current = current->next;
	}
}

static void	not_expansion(t_par *current, char *expansion)
{
	if (!expansion)
		current = current->next;
	else
	{
		free(current->command);
		current->command = ft_strdup(expansion);
	}
}

void	execute_command(t_parse *parse_data, t_env *data)
{
	t_par	*current;
	char	*path;
	int		i;
	char	*expansion;

	current = parse_data->head;
	while (current)
	{
		next_node(current);
		i = 0;
		if (current->command[0] == '$')
		{
			i++;
			expansion = expand_variable(&current->command[i], data);
			not_expansion(current, expansion);
		}
		if (!current->command)
			current = current->next;
		path = check_path(current, data);
		child_process(path, current);
		free(path);
		current = current->next;
	}
}
