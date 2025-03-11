/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:01:29 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/11 18:25:51 by pamanzan         ###   ########.fr       */
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
	int		j;
	char	*substr;

	j = ft_strlen(*temp);
	
	(void)flag;
	printf("el len de temp es: %d\n", j);
	i = 0;
	printf("flag en append es : %d\n", flag);
	while ((*temp)[i] != '\0' && (*temp)[i] != '$')
	{
		printf("entro en bucle de append\n");
		if (flag == 1 && (*temp)[j - 1] != '\'')
		{
			i++;
			while ((*temp)[i] != '\'')
				i++;
		}
		else if (flag != 1 && (*temp)[j - 1] == '\'')
		{
			i++;
			while ((*temp)[i] != '\'')
				i++;
		}
		i++;
	}
	printf("esta es la posicion de i: %d\n", i);
	printf("este es temp despues del bucle append: %s\n", *temp);
	substr = ft_strndup(*temp, i);
	printf("este es substr despues del dup append: %s\n", substr);

	result = ft_strjoin_free(result, substr);

	printf("este es result despues del join append: %s\n", result);

	*temp += i;
	return (result);
}
