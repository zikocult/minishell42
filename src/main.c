/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:04:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/27 14:23:20 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	first_init(t_env *data, char **env)
{
	interactive_signals();
	data->head = NULL;
	data->tail = NULL;
	data->heredoc_delimeter = NULL;
	if (env == NULL || env[0] == NULL)
		init_envi_list(data);
	else
		init_list(data, env);
}

// Return values
// 		false or 0= continue
// 		true or 1 = break
static bool	validation_main(char *command_buff, t_env *data)
{
	if (!command_buff)
	{
		free(command_buff);
		printf("exit\n");
		return (true);
	}
	if (*command_buff == '\0')
	{
		free(command_buff);
		return (false);
	}
	if (ft_strlen(command_buff) > 0)
		add_history(command_buff);
	if (select_type(command_buff, data))
	{
		free(command_buff);
		return (true);
	}
	free(command_buff);
	return (false);
}

int	main(int argc, char **argv, char **env)
{
	char	*command_buff;
	t_env	data;

	if (argc == 1 && argv[0])
		first_init(&data, env);
	while (1)
	{
		// interactive_signals();
		command_buff = readline("Minishell 💻 y OLÉ!💃 ");
		if (validation_main(command_buff, &data))
			break ;
		printf("\nPrueba 1: Heredoc básico (escribe 'fin' para terminar)\n");
		process_heredoc("fin", &data, "echo");
		printf("Prueba 2: Heredoc básico (escribe 'inicio' para terminar)\n");
		process_heredoc("inicio", &data, "cat");
	}
	return (free_list(&data), 0);
}
