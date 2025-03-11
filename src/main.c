/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:04:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/11 17:07:05 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	first_init(t_env *data, char **env)
{
	data->head = NULL;
	data->tail = NULL;
	data->heredoc_delimeter = NULL;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (env == NULL || env[0] == NULL)
		init_envi_list(data);
	else
		init_list(data, env);
}

// Return values
// 		false or 0= continue
// 		truen or 1 = break
static bool	validation_main(char *command_buff, t_env *data)
{
	if (!command_buff)
	{
		free(command_buff);
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
	bool	return_main;

	if (argc == 1 && argv[0])
		first_init(&data, env);
	while (1)
	{
		return_main = false;
		printf("\nPrueba 1: Heredoc básico (escribe 'fin' para terminar)\n");
		process_heredoc("fin", &data, "echo");
		printf("Prueba 2: Heredoc básico (escribe 'inicio' para terminar)\n");
		process_heredoc("inicio", &data, "cat");
		command_buff = readline("Minishell 💻 y OLÉ!💃 ");
		return_main = validation_main(command_buff, &data);
		if (return_main) 
			break;
	}
	return (free_list(&data), 0);
}
