/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2024/12/08 12:57:04 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(char **command, t_env_vars *env)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;

	paths = ft_split(env->path, ':');
	if (!paths)
		return (printf("Error al dividir el PATH\n"), NULL);
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
	if (!full_path)
		return (NULL);
	return (full_path);
}

void	execute_command(char **command, t_env_vars *env)
{
	char	*path;
	pid_t	pid;
	int		status;

	path = find_path(command, env);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, command, NULL) == -1)
		{
			printf("command not found: %s\n", command[0]);
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
