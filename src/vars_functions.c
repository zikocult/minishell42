/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2024/12/13 16:38:48 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(t_env_vars *env, const char *var_name)
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
		return (NULL);
}

char	*expand_variable(const char *input, t_env_vars *env)
{
	char		*var_name;
//	const char	*ptr;
	char		*value;
//	char		*result; en return si se descomenta
	int			i;

	i = 0;
//	ptr = input;
	var_name = (char *)malloc(ft_strlen(input) + 1);
	if (!var_name)
		return (NULL);
	while (*input && (ft_isalpha(*input) || (*input == '_')))
		var_name[i++] = *input++;
	var_name[i] = '\0';
	//value = (char *)malloc(10000);
	//if(!value)
	//	return (NULL);
	value = get_env_value(env, var_name);

	if (!value)
		return (ft_strdup(""));
//	result = ft_strdup(value);
	free(var_name);
	return (value);
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
