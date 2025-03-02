/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/03/02 18:31:30 by patri            ###   ########.fr       */
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

/*int	handle_dollar(char **str, t_env *data)
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
}*/

/*static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}*/

int	handle_dollar(char **str, t_env *data)
{
	int		i;
	char	*temp;
	char	*start;
	char	*end;
	char	*name;
	char	*expansion;
	char	*new_str;
	char	*new_temp;

	if (ft_strchr(*str, '$')) 
	{
		i = dollar_search(*str); 
		temp = ft_strndup(*str, i); 
		if ((*str)[i++] == '$') 
		{
			start = &(*str)[i]; 
			end = start;
			while (*end && (ft_isalnum(*end) || *end == '_'))
				end++;
			name = ft_strndup(start, end - start);
			if (!name)
			{
				free(temp);
				return (1); 
			}
			expansion = expand_variable(name, data);
			free(name);
			if (!expansion)
			{
			//	expansion = ft_strdup("");
		/*		free(temp);
				return (1);*/
				new_str = ft_strjoin(temp, end);
                free(temp);
                free(*str);
                *str = new_str;
                return (0);
			}
		/*	new_temp = ft_strjoin(temp, expansion);
			new_str = ft_strjoin(new_temp, end);*/
			new_temp = ft_strjoin(expansion, end);

			new_str = ft_strjoin(temp, new_temp);
			free(new_temp);
			free(temp);
			free(*str);
			*str = new_str;

			return (0);
		}
	}
	return (0);
}	
