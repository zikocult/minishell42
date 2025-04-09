/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:08:18 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/04/09 16:12:51 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_args_double_pointer(char **ptr)
{
	int	count;

	count = 0;
	while (ptr[count])
		count++;
	return (count);
}

int	count_args_spaces(char *param)
{
	char	**temp_param;
	int		count;

	count = 0;
	temp_param = ft_split(param, ' ');
	while (temp_param[count])
	{
		free(temp_param[count]);
		count++;
	}
	free(temp_param);
	return (count);
}
