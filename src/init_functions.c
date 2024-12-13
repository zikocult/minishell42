/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 09:23:05 by patri             #+#    #+#             */
/*   Updated: 2024/12/13 09:49:00 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_env_vars(t_env_vars *env)
{
	env->path = getenv("PATH");
	env->home = getenv("HOME");
	env->user = getenv("USER");
	env->shell = getenv("SHELL");
	env->pwd = getenv("PWD");
	env->oldpwd = getenv("OLDPWD");
	env->env = getenv("ENV");
}

void	init_parse_state(t_parse_state *state, char *command_buff)
{
	char *new_cmbuff;

	new_cmbuff = malloc(ft_strlen(command_buff) * 2);
	if (!new_cmbuff)
		malloc_error("error de malloc en el parseo, new_cmbuff");
	state->cmbuff = command_buff;
	state->new_cmbuff = new_cmbuff;
	state->i = 0;
	state->j = 0;
}
