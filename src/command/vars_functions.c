/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/02/17 19:30:13 by pamanzan         ###   ########.fr       */
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
		return ("\0");
	return (value->content);
}

int	single_quotes(char **str)
{
	int		i;
	int		len;
	char	*new_com;

	len = ft_strlen(*str) - 1;
	if ((*str)[0] == '\'' && (*str)[len] == '\'')
	{
		new_com = malloc(len + 1);
		i = 0;
		while (++i < len)
			new_com[i - 1] = (*str)[i];
		new_com[len - 1] = '\0';
		free (*str);
		*str = ft_strdup(new_com);
		free(new_com);
		return (1);
	}
	else if (((*str)[0] == '\'' && (*str)[len] != '\''
		) || ((*str)[0] != '\'' && (*str)[len] == '\''))
		return (printf("syntax error \n"), 1);
	return (0);
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
			free(*str);
			*str = ft_strjoin(temp, expansion);
			free(temp);
		}
	}
	return (0);
}

int double_simple_dollar(char **str, t_env *data)
{
	int		i;
	int		len;
	char	*new_com;

	if ((*str)[0] == '\"' && (*str)[1] == '\'')
	{
		new_com = ft_strdup(return_str_parse(*str));
		handle_dollar(&new_com, data);

		len = ft_strlen(new_com);
		*str = NULL;
		(*str)[0] = '\'';
		i = 1;
		while (++i < len)
			(*str)[i - 1] = new_com[i];
		(*str)[len] = '\'';
		(*str)[len + 1] = '\0';
		free(new_com);
		return (1);
	}
	return (0);
}
