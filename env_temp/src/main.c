# include "../include/env_temp.h"

t_var	*create_node(char *env_var)
{
	t_var	*new_node;
	size_t	name_lenght;
	size_t	i;
	char	*equal_sign;

	new_node = (t_var *)malloc(sizeof(t_var));
	if (!new_node)
		return (NULL);
    equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		name_lenght = equal_sign - env_var;
		i = 0;
		new_node->var_name = (char *)malloc(name_lenght + 1);
		if (!new_node->var_name)
		{
			free(new_node);
			return (NULL);
		}
		while (i < name_lenght) 
		{
			new_node->var_name[i] = env_var[i];
			i++;
		}
		new_node->var_name[name_lenght] = '\0';
		new_node->content = ft_strdup(equal_sign + 1);
		if (!new_node->content)
		{
			free(new_node->var_name);
			free(new_node);
			return (NULL);
		}
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

void	add_node(t_env *data, char *env_var)
{
	t_var	*new_node;
	new_node = create_node(env_var);
	if (!new_node)
		return ;
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
}

void	free_list(t_env	*data)
{
    t_var *current = data->head;
    t_var *next_node;

    while (current) {
        next_node = current->next;
        free(current->var_name);
        free(current->content);
        free(current);
        current = next_node;
    }
    data->head = NULL;
    data->tail = NULL;
}

int main (int argc, char **argv, char **env)
{
	t_env	data;
	data.head = NULL;
	data.tail = NULL;
	int		i;

	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		i = 0;
		while (env[i])
		{
			add_node(&data, env[i]);
            printf("var_name: %s\nContent: %s\n\n", data.tail->var_name, data.tail->content);
			i++;
		}
	}
	free_list(&data);
	return (0);
}
