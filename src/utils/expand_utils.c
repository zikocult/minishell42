/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:01:29 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/10 17:56:38 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mult_dollar(char *str, char c)
{
	int	i;
	int	dollar;

	dollar = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			dollar++;
		i++;
	}
	return (dollar);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

char	*expansion(char **temp, t_env *data, char *result)
{
	char	*start;
	char	*end;
	char	*name;
	char	*new_result;

	printf("llego a expansion\n");
	start = *temp;
	end = start + 1;
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	name = ft_strndup(start, end - start);
	printf("este es name en expansion: %s\n", name);
	printf("este es result en expansion: %s\n", result);
	if (!name)
		return (NULL);
	else
	{
		handle_dollar(&name, data);
		printf("Este es name en expansion despues de handle: %s\n", name);
		new_result = ft_strjoin_free(result, name);
	}
	*temp = end;
	return (new_result);
}

char	*append_text(char **temp, char *result, int flag)
{
	int		i;
	char	*substr;

	i = 0;
	if (flag == 1 && (*temp)[ft_strlen(*temp) - 1] == '\'')
	{
		printf ("paso el primer flag de append\n");
		free (result);
		result = ft_strdup(*temp);
//		result = ft_strjoin_free(result, substr);
	}
	else
	{
		while ((*temp)[i] != '\0' && (*temp)[i] != '$')
		{
			if ((*temp)[i] == '\'' && (*temp)[i + 1] == '$' && flag != 1)
				i++;
			i++;
		}
		substr = ft_strndup(*temp, i);
		result = ft_strjoin_free(result, substr);
		*temp += i;
	}
	return (result);
}
