/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:39:26 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/03/03 20:24:49 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *create_var(char *str)
{
	char	*var;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i] != '=' && str[i])
	{
		count++;
		i++;
	}
	var = (char *)ft_calloc(count + 1, sizeof(char));
	if (!var)
		return (NULL);
	while (j < i)
	{
		var[j] = str[j];
		j++;
	}
	return (var);
}

static char	*create_value(char *str)
{
	int 	i;
	char	*value;

	i = 0;
	value = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!value)
		return (NULL);
	while (str[i])
	{
		value[i] = str[i];
		i++;
	}
	return (value);
}

static void	change_type(char *str, t_env *data)
{
	t_var	*current;

	current = NULL;
	current = env_search(data, str);
	if (current && ft_strcmp(current->type, "env"))
	{
			free(current->type);
			current->type = ft_strdup("exp");
	}
	else if (!current)
		add_elem(data, str, NULL, "exp");
}

int	export_builtin(char *str, t_env *data)
{
	char	*var;
	char	*value;
	int		count;

	count = 0;
	if (ft_strchr(str, '='))
	{
		var = create_var(str);
		count = 0;
		while (str[count] != '=' && str[count])
			count++;
		value = create_value((str + count + 1));
		add_elem(data, var, value, "exp");
		free (var);
		free(value);
	}
	else
		change_type(str, data);
	return (0);
}
