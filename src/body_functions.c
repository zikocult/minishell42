/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:01 by patri             #+#    #+#             */
/*   Updated: 2024/12/07 11:57:19 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	select_type(char *command_buff, t_env_vars *env)
{
	char **args;
	int i = 0;

	args = parse_token(command_buff);
	if (!strcmp(args[0], "patata"))
		printf("%s 👾\n", "chachi piruli!!!");
	if (!strcmp(args[0],"ls"))
	{
		printf("%s\n", find_path("ls", env));
		while (args[i])
		{
			printf("%s\n", args[i]);
			i++;
		}
	}
	if (!strcmp(command_buff, "exit")) //TODO
	{ // definir si necesita manejo de "exit" 'exit' exit
		printf("USER: %s\n", env->user);//se ha de quitar antes de entrega	
		rl_clear_history();
		return (1);
	}
	return (0);
}
