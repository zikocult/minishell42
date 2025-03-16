/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:51:23 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/16 09:52:10 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_first_command(int i, t_command_data *cmd_data, int **pipes)
{
	int	fd_in;

	fd_in = open(cmd_data->argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(pipes[i - 2][1], STDOUT_FILENO);
}

void	setup_last_command(int i, t_command_data *cmd_data, int **pipes)
{
	int	fd_out;

	fd_out = open(cmd_data->argv[cmd_data->argc - 1], \
	O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
	if (fd_out == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(pipes[i - 3][0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	setup_intermediate_command(int i, int **pipes)
{
	dup2(pipes[i - 3][0], STDIN_FILENO);
	dup2(pipes[i - 2][1], STDOUT_FILENO);
}

void	setup_redirection(int i, t_command_data *cmd_data, int **pipes)
{
	if (i == 2)
		setup_first_command(i, cmd_data, pipes);
	else if (i == cmd_data->argc - 2)
		setup_last_command(i, cmd_data, pipes);
	else
		setup_intermediate_command(i, pipes);
}
