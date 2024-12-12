/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:01 by patri             #+#    #+#             */
/*   Updated: 2024/12/12 09:23:14 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	select_type(char *command_buff, t_env_vars *env)
{
	char	**args;

	args = parse_token(command_buff, env);
	if (!ft_strcmp(args[0], "patata"))
	{
		printf("%s 👾\n", "chachi piruli!!!");
		free_memory(args);
		return (0);
	}
	if (!ft_strcmp(args[0], "echo"))
	{
		handle_echo(args);
		free_memory(args);
		return (0);
	}
	if (!ft_strcmp(args[0], "exit")) //TODO
	{ // definir si necesita manejo de "exit" 'exit' exit
		printf("USER: %s\n", env->user);//se ha de quitar antes de entrega	
		rl_clear_history();
		free_memory(args);
		return (1);
	}
	execute_command(args, env);
//	free_memory(args);
	return (0);
}
