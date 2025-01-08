/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:39:54 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/01/08 21:51:33 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env_temp.h"

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

void	free_list(t_env	*data)
{
	t_var	*current;
	t_var	*next_node;

	current = data->head;
	while (current)
	{
		next_node = current->next;
		free(current->content);
		free(current->var_name);
		free(current);
		current = next_node;
	}
	data->head = NULL;
	data->tail = NULL;
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
		printf("var_name: %s\nContent: %s\n\n", data->tail->var_name, data->tail->content);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	data;

	data.head = NULL;
	data.tail = NULL;
	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		init_list(&data, env);
	}
	free_list(&data);
	return (0);
}
