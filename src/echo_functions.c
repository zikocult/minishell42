/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:23:37 by pamanzan          #+#    #+#             */
/*   Updated: 2025/01/14 18:08:08 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_echo(char **args)
{
	int	i;

	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
	}
	if (!(args[1] && ft_strcmp(args[1], "-n") == 0))
		printf("\n");
}

