/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:00:05 by pamanzan          #+#    #+#             */
/*   Updated: 2025/01/09 17:01:58 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Te voy subiendo comentarios para que te sea mas fácil la integración en minishell.
// Si quieres que te explique, estaré luchando por una lavadora, pero te respondo rápido jejeje

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
	// De esta función no te voy a contar mucho, sólo que tuve que crear create node2 por tema
	// de norminette, pero es una función que se podría haber metido dentro de create_node.
	t_var	*new_node;
	char	*equal_sign;

	new_node = (t_var *)malloc(sizeof(t_var));
	if (!new_node)
		return (NULL);
	// si ves el truquito que he usado aquí te gustará, como contar el número de carácteres sin contar
	// el número de carácteres, pues aquí tienes un ejemplo jejejee
	// el truqui, sólo funciona luego volcando a un size_t, si no, no funciona y la parte mas guai, está
	// en la otra función: name_length = equal_sign - env_var
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
	// YO esta función la sacaría de este fichero, sirve para limpiar todo lo que tenga
	// la lista. A modo personal siempre creo un fichero con todas las funciones de limpieza
	// y una función que las llama a todas, esta podría ser una de ellas.
	// Eso si, sacarla del fichero no quiere decir que no sea necesaria, si no se pone hay leaks.
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
	// No es necesario realizar la asignación de tail, la he puesto, pues me iba bien para las pruebas
	// y a lo mejor tu la puedes usar, lo dejo a tu elección si lo ves necesario o no.
	// Lo anterior puede ser muy útil si nos ponemos a limpiar lineas.
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
		// Eliminar este printf, es sólo para comprobar, pero lo dejo de momento para que el programa haga algo, es realmente el único error de norminette si no fuera por los comentarios.
		printf("var_name: %s\nContent: %s\n\n", data->tail->var_name, data->tail->content);
	}
}

/*int	main(int argc, char **argv, char **env)
{
	t_env	data;
	// Estas dos asignaciones a NULL se deberían subir a init_list, pero me supera entonces el número de lineas
	// El subirlas a init, significará, que el main se deberá modificar muy poco,
	// básicamente el main de minishell sólo deberemos llamar a init_list y free_list, de manera directa o no.
	// evidentemente también deben ser creadas las listas, pero mi pensamiento es que data, sea la lista genérica
	// la que usamos para traspasar datos por todo el programa.
	data.head = NULL;
	data.tail = NULL;
	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		init_list(&data, env);
	}
	free_list(&data);
	return (0);
}*/
