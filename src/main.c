/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:04:17 by pamanzan          #+#    #+#             */
/*   Updated: 2024/12/05 13:09:37 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int main(int argc, char **argv)
{
	char *command_buff;

	if(argc < 0)
		return (0);
	if (*argv > 0)
		argv++;
	
	while (1)
	{
		command_buff = readline("minishell> ");
		if (ft_strlen(command_buff) > 0)
			add_history(command_buff);
		if (!strcmp(command_buff, "patata"))
			printf("%s 👾\n", "chachi piruli!!!");
		if (!strcmp(command_buff, "ls"))

			printf("%s \n", find_path("ls"));
		if (!strcmp(command_buff, "exit"))
		{
			rl_clear_history();
			free(command_buff);
			break;
		}
		free(command_buff);
	}
	return (0);
}
