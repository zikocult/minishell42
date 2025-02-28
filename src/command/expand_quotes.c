/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:05:43 by pamanzan          #+#    #+#             */
/*   Updated: 2025/02/28 18:44:54 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	single_quotes(char **str, t_env *data)
{
	int		i;
	int		len;
	char	*new_com;

	(void)data;
	len = ft_strlen(*str);
	if (len == 0)
		return (printf("minishell: '' Command not found \n"), 1);
	if ((*str)[0] == '\'' && (*str)[len - 1] == '\'')
	{
		new_com = malloc(len + 1);
		i = 0;
		while (++i < len)
			new_com[i - 1] = (*str)[i];
		new_com[len - 2] = '\0';
		free (*str);
		*str = ft_strdup(new_com);
		free(new_com);
		return (1);
	}
	return (0);
}

int	double_simple_dollar(char **str, t_env *data)
{
	int		i;
	int		len;
	char	*new_com;

	if ((*str)[0] == '\"' && (*str)[1] == '\'')
	{
		new_com = return_str_parse(*str);
		handle_dollar(&new_com, data);
		len = ft_strlen(new_com);
		*str = (char *)malloc(sizeof(char) * (len + 2 + 1));
		(*str)[0] = '\'';
		i = 0;
		while (i < len)
		{
			(*str)[i + 1] = new_com[i];
			i++;
		}
		(*str)[len + 1] = '\'';
		(*str)[len + 2] = '\0';
		free(new_com);
		return (1);
	}
	return (0);
}

static int	mult_dollar(char *str)
{
	int	i;
	int	dollar;

	dollar = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			dollar++;
		i++;
	}
	printf("hola dollar\n");
	return (dollar);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static int	expand_mult(char **str, t_env *data)
{
	char	*result;
	char	*temp;
	char	*start;
	char	*end;
	char	*name;
	int		i;

	result = ft_strdup(""); 
	if (!result)
		return (1); 
	temp = *str;
	while (*temp)
	{
		if (*temp == '$') 
		{
			start = temp; 
			end = start + 1;
			while (*end && (ft_isalnum(*end) || *end == '_'))
				end++;
			name = ft_strndup(start, end - start);
			if (!name)
			{
				free(result);
				return (1); 
			}
			if (handle_dollar(&name, data) == 0)
				result = ft_strjoin_free(result, name);
			else if (handle_dollar(&name, data) == 1)
				free(name);
			temp = end;
		}
		else
		{
			i = 0;
			while (temp[i] && temp[i] != '$')
				i++;
			result = ft_strjoin_free(result, ft_strndup(temp, i));
			temp += i;
		}
	}
	free(*str); 
	*str = result; 
	return (0); 
}


int	double_quotes_dollar(char **str, t_env *data)
{
	char	*new_str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(*str);
	if (len == 0)
		return (0);
	if ((*str)[0] == '\"' && (*str)[len - 1] == '\"')
	{

		if (mult_dollar(*str)> 1)
		{
			printf("hola\n");
			expand_mult(str, data);
			return (1);
		}
		else
		{	
			while ((*str)[i] == 32)
				i++;
			new_str = remove_double_quotes(*str);
			handle_dollar(&new_str, data);
			*str = new_str;
			return (1);
		}
	}
	return (0);
}
