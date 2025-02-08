/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2025/02/08 13:15:28 by pamanzan         ###   ########.fr       */
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
		{
//			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, status, 0);
	else
		perror("Error en fork");
}

char	*command_needed(char *command, t_env *data)
{
	int		i;
	char	*expansion;

	i = 0;
	if (command[0] == '$')
	{
		i++;
		expansion = expand_variable(&command[i], data);
		if (expansion)
		{
			free(command);
			command = ft_strdup(expansion);
			free(expansion);
		}
	}
	return (command);
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
		if (!current->command && !current->infile && !current->outfile)
		{
			if (current->next)
				current = current->next;
			continue ;
		}
		/* if (current->command[0] == '$') */
		/* 	current->command = command_needed(current->command, data); */
		i = 0;
		if (current->command[0] == '$')
		{
			i++;
			expansion = expand_variable(&current->command[i], data);
			if (!expansion)
			{
				current = current->next;
				continue ;
			}
			else
			{
			free(current->command);
			current->command = ft_strdup(expansion);
		//	free(expansion);
			}
		}

		if (!current->command)
		{
			current = current->next;
			continue ;
		}
		path = check_path(current, data);
		child_process(path, current);
		free(path);
		current = current->next;
	}
}
