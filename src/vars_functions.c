/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/01/10 18:36:15 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*char	*get_env_value(t_env_vars *env, const char *var_name)
{
	if (ft_strcmp(var_name, "PATH") == 0)
		return (env->path);
	else if (ft_strcmp(var_name, "HOME") == 0)
		return (env->home);
	else if (ft_strcmp(var_name, "USER") == 0)
		return (env->user);
	else if (ft_strcmp(var_name, "SHELL") == 0)
		return (env->shell);
	else if (ft_strcmp(var_name, "PWD") == 0)
		return (env->pwd);
	else if (ft_strcmp(var_name, "OLDPWD") == 0)
		return (env->oldpwd);
	else
		return (NULL); //TODO comprobar si es necesario despues de modificar manejo en init
}*/

char	*expand_variable(char *input, t_env *data)
{
	char		*var_name;
	t_var		*value;
	int			i;

	i = 0;
	var_name = (char *)malloc(ft_strlen(input) + 1);
	//TODO posible error de size con value
	if (!var_name)
		return (NULL);
	while (*input && (ft_isalnum(*input) || (*input == '_')))
		var_name[i++] = *input++;
	var_name[i] = '\0';
/*	value = get_env_value(env, var_name);*/
	value = env_search(data, var_name);
	if (!value)
		return (ft_strdup(" "));
	free(var_name);
	return (value->content);
}

void	handle_echo(char **args)
{
	int	i;

	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!(args[1] && ft_strcmp(args[1], "-n") == 0))
		printf("\n");
}
