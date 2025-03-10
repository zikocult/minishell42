/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/03/10 18:01:52 by pamanzan         ###   ########.fr       */
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

	if (ft_strchr(*str, '$') && !ft_strchr(*str, '\'') && !ft_strchr(*str, '\"'))
	{
		i = dollar_search(*str);
		temp = ft_strndup(*str, i);
		if ((*str)[i++] == '$')
		{
			new_str = extract_expand(*str, i, data, &end);
			return (build_new_string(str, temp, new_str, end), 1);
		}
		free(temp);
	}
	return (0);
}

char	*check_quotes(char *result)
{
	int		quotes_number;
	int		i;
	int		j;
	char	*new_result;

	i = 0;
	j = 0;
	quotes_number = mult_dollar(result, '\"');
	new_result = malloc(sizeof(char) * ((ft_strlen(result) - quotes_number) + 1));
	if (!new_result)
	{
		perror("malloc");
		exit(4);
	}
	printf("RESULT == %s\n", result);
	while (result[i] != '\0')
	{
		while (result[i] == '\"')
			i++;
		if (result[i] == '\0')
			break ;
		new_result[j] = result[i];
		i++;
		j++;
	}
	new_result[j] = '\0';
	free(result);
	return (new_result);
}

int	expand_mult(char **str, t_env *data)
{
	char	*result;
	char	*temp;
	int		flag;

	flag = 0;
	printf("entro en expandmult\n");
	result = ft_strdup("");
	temp = *str;
	printf("asi llega str:%s\n", temp);
	/* if ((*str)[0] == '\"') */
	/* 	flag = 0; */
	if ((*str)[0] == '\'')
		flag = 1;
	if (mult_dollar(temp, '$') > 1)
	{
		while (*temp != '\0')
		{	
			if (*temp == '$')
			{
				result = expansion(&temp, data, result);
				printf("Este es result en expand muult: %s\n", result);
			}
			else if (flag == 1 &&  (temp)[ft_strlen(temp) - 1] == '\'')
			{
				result = append_text(&temp, result, flag);
				return (1);
			}
			else
				result = append_text(&temp, result, flag);
			if (!result)
				return (1);
		}
		printf("Este es result before check_quotes: %s\n", result);
		result = check_quotes(result);
		free(*str);
		*str = result;
		printf("Este es result en expand mult: %s\n", result);
		return (1);
	}
	free(result);
	return (0);
}
