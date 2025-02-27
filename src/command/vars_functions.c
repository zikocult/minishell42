/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/02/27 17:59:20 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_variable(char *input, t_env *data)
{
	char	*var_name;
	t_var	*value;
	int		i;

	i = 0;
	var_name = (char *)malloc(ft_strlen(input) + 1);
	if_notstr(var_name);
	while (*input)
		var_name[i++] = *input++;
	var_name[i] = '\0';
	value = env_search(data, var_name);
	free(var_name);
	if (!value)
		return (NULL);
	return (value->content);
}

int	dollar_search(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	if (str[i] == '$')
		return (i);
	return (0);
}

int	handle_dollar(char **str, t_env *data)
{
	int		i;
	char	*temp;
	char	*expansion;

	if (ft_strchr(*str, '$'))
	{
		i = dollar_search(*str);
		temp = ft_strndup(*str, i);
		if ((*str)[i++] == '$')
		{
			expansion = expand_variable(&(*str)[i], data);
			if (!expansion)
			{
				free(temp);
				return (1);
			}
			free(*str);
			*str = ft_strjoin(temp, expansion);
			free(temp);
			return (0);
		}
	}
	return (0);
}

