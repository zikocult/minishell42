/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:38:31 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/04/08 16:19:39 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	update_env(t_env *data, char *variable)
{
	char	*pwd;

	pwd = (char *)getcwd(NULL, 0);
	if (!pwd)
		return (printf("Minishell: cd: getcwd failed\n"), 1);
	add_elem(data, variable, pwd, "env");
	free(pwd);
	return (0);
}

static int	extra_options(t_env *data, char *variable)
{
	t_var	*current;
	int		ret;

	current = (env_search(data, variable));
	if (!current || !current->content || current->content[0] == '\0')
		return (printf("Minishell: cd: %s not set\n", variable), 1);
	ret = chdir(current->content);
	if (ret == -1)
		return (-1);
	if (!ret)
		update_env(data, variable);
	if (!ft_strcmp("OLDPWD", variable) && !ret)
		printf("%s\n", current->content);
	return (chdir(current->content));
}

static int	cd(char *param, t_env *data)
{
	if (!param)
		return (extra_options(data, "HOME"));
	if (!ft_strcmp(param, "-"))
		return (extra_options(data, "OLDPWD"));
	update_env(data, "OLDPWD");
	return (chdir(param));
}

int	run_cd(t_env *data, char *param)
{
	int	ret;
	int	arg_count;

	arg_count = 0;
	if (param)
		arg_count = count_args(param);
	if (arg_count > 1)
		return (printf("Minishell: cd: too many arguments\n"), 1);
	else
		ret = cd(param, data);
	if (ret == -1)
	{
		printf("Minishell: cd: %s: no such file or directory\n", param);
		return (-1);
	}
	update_env(data, "PWD");
	return (0);
}
