/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:01 by patri             #+#    #+#             */
/*   Updated: 2025/01/14 17:30:14 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	select_type(char *command_buff, t_env *data)
{
	char	**args;

	args = parse_token(command_buff, data);
	if (!args[0])
		return (0);
	if (!ft_strcmp(args[0], "patata"))
	{
		printf("%s 👾\n", "chachi piruli!!!");
		free_memory(args);
		return (0);
	}
/*	else if (!ft_strcmp(args[0], "echo"))
	{
		handle_echo(args);
		free_memory(args);
		return (0);
	}*/
	else if (!ft_strcmp(args[0], "env"))
		env_builtin(data);
	else if (!ft_strcmp(args[0], "exit"))
	{
		rl_clear_history();
		free_memory(args);
		return (1);
	}
	else
	{
		execute_command(args, data);
		free_memory(args);
		return (0);
	}
	return (0);
}
