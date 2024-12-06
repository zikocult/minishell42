/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:01 by patri             #+#    #+#             */
/*   Updated: 2024/12/06 10:35:21 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	select_type(char *command_buff)
{
	if (!strcmp(command_buff, "patata"))
		printf("%s 👾\n", "chachi piruli!!!");
	if (!strcmp(command_buff, "ls"))
		printf("%s \n", find_path("ls"));
}
