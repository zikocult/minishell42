/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:04:17 by pamanzan          #+#    #+#             */
/*   Updated: 2024/12/05 08:04:36 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int main(void)
{
	char *command_buff;

	while (1)
	{
		command_buff = readline("minishell> ");
		if (ft_strlen(command_buff) > 0)
			add_history(command_buff);
		if (!strcmp(command_buff, "exit"))
		{
			rl_clear_history();
			free(command_buff);
			break;
		}
		free(command_buff);
	}
}
