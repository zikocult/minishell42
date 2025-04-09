/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:17:54 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/04/09 16:35:59 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

void	env_list_builtin(t_env *data)
{
	t_var	*current;

	current = data->head;
	while (current->next)
	{
		if (!ft_strcmp(current->type, "env"))
			printf("%s=%s\n", current->var_name, current->content);
		current = current->next;
	}
}

static char	*create_var(char *str)
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
	int		i;
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

int	env_builtin(char *str, t_env *data)
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
		add_elem(data, var, value, "env");
		free (var);
		free(value);
		env_list_builtin(data);
	}
	else
	{
		printf("env: ‘%s’: No such file or directory\n", str);
		return (1);
	}
	return (0);
}

int	run_env(t_env *data, char **str)
{
	if (!str)
	{
		env_list_builtin(data);
		return (0);
	}
	if (count_args_double_pointer(str) > 1)
	{
		printf("env: '%s': No such file or directory\n", str[0]);
		return (1);
	}
	return (env_builtin(str[0], data));
}
