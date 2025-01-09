/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:04:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/01/09 17:56:26 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*command_buff;
	t_env	data;

	data.head = NULL;
	data.tail = NULL;
	
	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		init_list(&data, env);
	}
	free_list(&data);
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
		if (select_type(command_buff, &data))
		{
			free(command_buff);
			break ;
		}
		free(command_buff);
	}
	return (0);
}
