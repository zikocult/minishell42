/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/02/13 16:18:34 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_variable(char *input, t_env *data)
{
	char		*var_name;
	t_var		*value;
	int			i;

	i = 0;
	var_name = (char *)malloc(ft_strlen(input) + 1);
	if_notstr(var_name);
	while (*input)
		var_name[i++] = *input++;
	var_name[i] = '\0';
	value = env_search(data, var_name);
	free(var_name);
	if (!value)
		return ("\0");
	return (value->content);
}
