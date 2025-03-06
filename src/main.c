/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:04:17 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/06 19:13:54 by Guillem Barulls  ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*command_buff;
	t_env	data;

	if (argc == 1 && argv[0])
		first_init(&data, env);
	while (1)
	{
		command_buff = readline("💃 Minishell y olé 💃 ");
		if (!command_buff)
		{
			if (is_heredoc_active(&data))
			{
				handle_heredoc_eof(&data);
				continue ;
			}
			free_main(command_buff, &data);
			break ;
		}
		if (*command_buff == '\0')
		{
			free_main(command_buff, &data);
			continue ;
		}
		if (ft_strlen(command_buff) > 0)
			add_history(command_buff);
		if (select_type(command_buff, &data))
		{
			free_main(command_buff, &data);
			break ;
		}
		free_main(command_buff, &data);
	}
	return (free_list(&data), 0);
}
