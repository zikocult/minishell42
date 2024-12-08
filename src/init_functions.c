/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 09:23:05 by patri             #+#    #+#             */
/*   Updated: 2024/12/08 10:56:22 by patri            ###   ########.fr       */
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
