/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:09:11 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/16 09:52:29 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (i > 0)
			{
				close(pipes[--i][0]);
				close(pipes[i][1]);
			}
			free_pipes(pipes, num_pipes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	execute_commands(t_command_data *cmd_data, int **pipes, int num_pipes)
{
	int	pid;
	int	i;

	i = 2;
	while (i < cmd_data->argc - 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			exec_child(i, cmd_data, pipes, num_pipes);
		i++;
	}
}

void	exec_child(int i, t_command_data *cmd_data, int **pipes, int num_pipes)
{
	char	**result;
	char	*path;

	setup_redirection(i, cmd_data, pipes);
	close_pipes(pipes, num_pipes);
	result = ft_split(cmd_data->argv[i], 32);
	path = find_path(cmd_data->find, result[0]);
	execve(path, result, cmd_data->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	wait_for_children(int argc)
{
	int	i;
	int	status;

	i = 0;
	while (i < argc - 3)
	{
		wait(&status);
		i++;
	}
}
