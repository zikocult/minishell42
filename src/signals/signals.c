/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:42:31 by Guillem Bar       #+#    #+#             */
/*   Updated: 2025/03/27 14:35:45 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_catch_signals = 0;
	exit(130);
}

void	interactive_signals(void)
{
	signal(SIGINT,handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 1;
}

void	here_signals(void)
{
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
