/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2025/02/04 18:57:27 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			printf("%s: command not found\n", current->command);
			free(path);
			free(current);
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
	t_par	*current;
	char	*expansion;

	int i;

	i = 0;

	current = parse_data->head;
	while (current)
	{
		if (!current->command && !current->infile && !current->outfile)
		{
			if (current->next)
				current = current->next;
			continue ;
		}
		if (current->command[0] == '$')
		{
			i++;
			expansion = expand_variable(&current->command[i], data);
			free(current->command);
			current->command = ft_strdup(expansion);
			printf("patata: %s\n", current->command);
	
		}	
		path = find_path(current, data);
//		if (!path) //MIRAR COMO QUEREMOS MANEJAR ERROR DE PATH... 
		/* { */
		/* 	printf("%s: command not found\n", current->command); */

	//		current = current->next;
	//		continue ;
	//	}
		child_process(path, current);
		free(path);
		current = current->next;
	}
}

char	*find_path(t_par *current, t_env *data)
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
		full_path = ft_strjoin(path, current->command);
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
