/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:04:17 by pamanzan          #+#    #+#             */
/*   Updated: 2024/12/06 10:39:45 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int main(void)
{
	char 		*command_buff;
	t_env_vars	env;

	init_env_vars(&env); 
/*	if (argc > 1)
	{
    printf("First argument: %s\n", argv[1]);
	}*/

	while (1)
	{
		command_buff = readline("minishell> ");
		if (ft_strlen(command_buff) > 0)
			add_history(command_buff);
		select_type(command_buff);
		if (!strcmp(command_buff, "exit"))
		{
			printf("USER: %s\n", env.user);	//se ha de quitar antes de entrega	
			rl_clear_history();
			free(command_buff);
			break;
		}
		free(command_buff);
	}
	return (0);
}
