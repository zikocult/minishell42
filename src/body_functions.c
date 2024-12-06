/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:01 by patri             #+#    #+#             */
/*   Updated: 2024/12/06 12:46:56 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	select_type(char *command_buff, t_env_vars *env)
{
	char **args;

	args = parse_token(command_buff);
	if (!strcmp(args[0], "patata"))
		printf("%s 👾\n", "chachi piruli!!!");
	if (!strcmp(command_buff, "ls"))
		printf("%s \n", find_path("ls"));
	if (!strcmp(command_buff, "exit"))
	{
		printf("USER: %s\n", env->user);	//se ha de quitar antes de entrega	
		rl_clear_history();
		return (1);
	}
	return (0);
}
