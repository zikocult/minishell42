/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:01:29 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/04 18:53:19 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mult_dollar(char *str)
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

	start = *temp;
	end = start + 1;
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	name = ft_strndup(start, end - start);
	if (!name)
		return (free(result), NULL);
	if (handle_dollar(&name, data) == 0)
		result = ft_strjoin_free(result, name);
	else
		free(name);
	*temp = end;
	return (result);
}

char	*append_text(char **temp, char *result)
{
	int		i;
	char	*substr;

	i = 0;
	while ((*temp)[i] && (*temp)[i] != '$')
		i++;
	substr = ft_strndup(*temp, i);
	result = ft_strjoin_free(result, substr);
	*temp += i;
	return (result);
}
