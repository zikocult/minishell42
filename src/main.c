/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:04:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/01/07 17:25:01 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int main(void)
{
	char 		*command_buff;
	t_env_vars	env;

	init_env_vars(&env); 
	while (1)
	{
		command_buff = readline("minishell> ");
		
		if (*command_buff == '\0')
		{
			free(command_buff);
			continue ;
		}
		if (ft_strlen(command_buff) > 0)
			add_history(command_buff);
	//	env_vars(command_buff, env);
		if (select_type(command_buff, &env))
		{
			free(command_buff);
			break ;
		}
		free(command_buff);
	}
	return (0);
}
