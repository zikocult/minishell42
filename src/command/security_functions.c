/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:43:16 by patri             #+#    #+#             */
/*   Updated: 2025/04/12 11:22:52 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	malloc_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	*if_notstr(char *str)
{
	if (!str)
		return (NULL);
	return (str);
}

void	error_msg(char *str, int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else if (flag == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command NOT found\n", 2);
	}
	else if (flag == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Perimssion denied\n", 2);
	}
}
