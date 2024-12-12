/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2024/12/12 10:33:03 by patri            ###   ########.fr       */
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
	const char	*ptr;
	char		*value;
	char		*result;
	int			i;

	i = 0;
	ptr = input;
	var_name = (char *)malloc(1000);
	if (!var_name)
		return (NULL);
	while (*ptr && (ft_isalpha(*ptr) || (*ptr == '_')))
		var_name[i++] = *ptr++;
	var_name[i] = '\0';
	value = get_env_value(env, var_name);
	if (!value)
		return (ft_strdup(""));
	result = ft_strdup(value);
	free(var_name);
	return (result);
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
