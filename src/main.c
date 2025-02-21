/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:04:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/02/20 20:19:48 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	// char	*command_buff;
	t_env	data;

	data.head = NULL;
	data.tail = NULL;
	if (argc == 1 && argv[0])
	{
		if (env == NULL || env[0] == NULL)
			init_envi_list(&data);
		else
			init_list(&data, env);
	}
	// unset_builtin(&data, "SYSTEMD_EXEC_PID");
	// unset_builtin(&data, "SSH_AUTH_SOCK");
	unset_builtin(&data, "LANG");
	add_elem(&data, "patata", "patata", "exp");
	add_elem(&data, "caracol", "lata", "exp");

	// unset_builtin(&data, "_");
	unset_builtin(&data, "SHLVL");
	// unset_builtin(&data, "PWD");
	
	add_elem(&data, "mandanga", "buena", "var");
	add_elem(&data, "patata", "Melon", "var");
	env_builtin(&data);
	// while (1)
	// {
	// 	command_buff = readline("💃 Minishell y olé 💃> ");
	// 	if (*command_buff == '\0')
	// 	{
	// 		free(command_buff);
	// 		continue ;
	// 	}
	// 	if (ft_strlen(command_buff) > 0)
	// 		add_history(command_buff);
	// 	if (select_type(command_buff, &data))
	// 	{
	// 		free(command_buff);
	// 		break ;
	// 	}
	// 	free(command_buff);
	// }
	
	return (free_list(&data), 0);
}
