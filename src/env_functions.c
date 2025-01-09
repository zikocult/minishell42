/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:00:05 by pamanzan          #+#    #+#             */
/*   Updated: 2025/01/09 17:56:21 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*create_node2(char *env_var, t_var *new_node, char *equal_sign)
{
	size_t	name_length;
	size_t	i;

	name_length = equal_sign - env_var;
	i = 0;
	new_node->var_name = (char *)malloc(name_length + 1);
	if (!new_node->var_name)
	{
		free(new_node);
		return (NULL);
	}
	while (i < name_length)
	{
		new_node->var_name[i] = env_var[i];
		i++;
	}
	new_node->var_name[name_length] = '\0';
	new_node->content = ft_strdup(equal_sign + 1);
	if (!new_node->content)
	{
		free(new_node->var_name);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

t_var	*create_node(char *env_var)
{
	t_var	*new_node;
	char	*equal_sign;

	new_node = (t_var *)malloc(sizeof(t_var));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		if (!create_node2(env_var, new_node, equal_sign))
			return (NULL);
	}
	else
	{
		new_node->var_name = ft_strdup(env_var);
		if (!new_node->var_name)
		{
			free(new_node);
			return (NULL);
		}
		new_node->content = NULL;
	}
	new_node->next = NULL;
	return (new_node);
}

void	init_list(t_env *data, char **env)
{
	t_var	*new_node;
	int		i;

	i = 0;
	while (env[i])
	{
		new_node = create_node(env[i]);
		if (!new_node)
		{
			free_list(data);
			return ;
		}
		if (!data->head)
		{
			data->head = new_node;
			data->tail = new_node;
		}
		else
		{
			data->tail->next = new_node;
			data->tail = new_node;
		}
		i++;
		// Eliminar este printf, es sólo para comprobar,
	//	printf("var_name: %s\nContent: %s\n\n", data->tail->var_name, data->tail->content);
	}
}

t_var	env_search(t_env *data, char *str)
{
	while (data != NULL)
	{
		if(ft_strcmp(data->head, str) == 0)
			return (data->tail)
		data = data->next;
	}
}
