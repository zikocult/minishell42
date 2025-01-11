/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2025/01/11 09:02:48 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(char **command, t_env *data)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;
	t_var	*search;

	search = env_search(data, "PATH");
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

void	execute_command(char **command, t_env *data)
{
	char	*path;
	pid_t	pid;
	int		status;

	path = find_path(command, data);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, command, NULL) == -1)
		{
			printf("%s: command not found\n", command[0]);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("Error en fork");
	free(path);
}
