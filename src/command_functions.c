/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2025/02/02 01:50:34 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**generate_command(t_par *current)
{
	char	**command;

	command = malloc(3 * sizeof(char *));
	if (!command)
	{
		perror("Error allocating memory");
		return (NULL);
	}
	command[0] = current->command;
	command[1] = current->parameter;
	command[2] = NULL;
	return (command);
}

void	child_process(char *path, char **command)
{
	pid_t	pid;
	int		*status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, command, NULL) == -1)
		{
			printf("%s: command not found\n", command[0]);
			free(path);
			free(command);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, status, 0);
	else
		perror("Error en fork");
}

void	execute_command(t_parse *parse_data, t_env *data)
{
	char	*path;
	char	**command;
	t_par	*current;

	current = parse_data->head;
	while (current != NULL)
	{
		command = generate_command(current);
		if (command == NULL)
		{
			current = current->next;
			continue ;
		}
		path = find_path(command, data);
		if (!path) //MIRAR COMO QUEREMOS MANEJAR ERROR DE PATH... 
		{
			printf("%s: command not found\n", command[0]);
			free(command);
			current = current->next;
			continue ;
		}
		child_process(path, command);
		free(path);
		free(command);
		current = current->next;
	}
}

char	*find_path(char **command, t_env *data)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;
	t_var	*search;

	search = env_search(data, "PATH");
	if (!search)
		return (NULL);
	paths = ft_split(search->content, ':');
	if_notstr(*paths);
	i = 0;
	full_path = NULL;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, command[0]);
		free(path);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_memory(paths);
	if_notstr(full_path);
	return (full_path);
}
