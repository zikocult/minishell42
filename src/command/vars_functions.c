/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/03/04 18:34:44 by pamanzan         ###   ########.fr       */
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

int	handle_dollar(char **str, t_env *data)
{
	int		i;
	char	*temp;
	char	*new_str;
	char	*end;

	if (ft_strchr(*str, '$'))
	{
		i = dollar_search(*str);
		temp = ft_strndup(*str, i);
		if (mult_dollar(*str) > 1)
			return (expand_mult(str, data), 1);
		if ((*str)[i++] == '$')
		{
			new_str = extract_expand(*str, i, data, &end);
			return (build_new_string(str, temp, new_str, end));
		}
		free(temp);
	}
	return (0);
}

int	expand_mult(char **str, t_env *data)
{
	char	*result;
	char	*temp;

	result = ft_strdup("");
	if (!result)
		return (1);
	temp = *str;
	while (*temp)
	{	
		if (*temp == '$')
			result = expansion(&temp, data, result);
		else
			result = append_text(&temp, result);
		if (!result)
			return (1);
	}
	free(*str);
	*str = result;
	return (0);
}
