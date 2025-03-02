/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/03/02 21:18:59 by patri            ###   ########.fr       */
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

static int	not_expansion(char **str, char *temp, char *end)
{
	char	*new_str;

	new_str = ft_strjoin(temp, end);
	if (!new_str)
	{
		free(temp);
		return (1);
	}
	free(temp);
	free(*str);
	*str = new_str;
	return (0);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*extract_and_expand_variable(char *str,
	int i, t_env *data, char **end_ptr)
{
	char	*start;
	char	*end;
	char	*new_temp;
	char	*new_str;

	start = &str[i];
	end = start;
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	new_temp = ft_strndup(start, end - start);
	new_str = expand_variable(new_temp, data);
	free(new_temp);
	*end_ptr = end;
	return (new_str);
}

static int	build_new_string(char **str, char *temp, char *new_str, char *end)
{
	char	*new_temp;

	if (!new_str)
		return (not_expansion(str, temp, end));
	new_temp = ft_strjoin(new_str, end);
	new_str = ft_strjoin_free(temp, new_temp);
	free(*str);
	*str = new_str;
	return (0);
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
		if ((*str)[i++] == '$')
		{
			new_str = extract_and_expand_variable(*str, i, data, &end);
			return (build_new_string(str, temp, new_str, end));
		}
	}
	return (0);
}
