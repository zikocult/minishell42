/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:38:31 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/04/08 12:01:30 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_args(char *param)
{
	char	**temp_param;
	int		count;

	count = 0;
	temp_param = ft_split(param, ' ');
	while (temp_param[count])
	{
		free(temp_param[count]);
		count++;
	}
	free(temp_param);
	return (count);
}

static int	update_oldpwd(t_env *data)
{
	char	*pwd;

	pwd = (char *)getcwd(NULL, 0);
	if (!pwd)
		return (printf("Minishell : cd : getcwd failed\n"), 1);
	add_elem(data, "OLDPWD", pwd, "env");
	free(pwd);
	return (0);
}

// hay que revisar el cd - con mas cuidado, parece que funciona
// pero necesito pruebas online, es decir con la builtin ya metida
// y ponerme a jugar con ella
static int	cd(char *param, t_env *data)
{
	int		ret;
	t_var	*current;

	update_oldpwd(data);
	if (!param)
	{
		current = (env_search(data, "HOME"));
		if (!current || !current->content || current->content[0] == '\0')
			return (printf("Minishell: cd : HOME not set\n"), 1);
		ret = chdir(current->content);
		return (ret);
	}
	if (!ft_strcmp(param, "-"))
	{
		current = (env_search(data, "OLDPWD"));
		if (!current || !current->content || current->content[0] == '\0')
			return (printf("Minishell: cd : OLDPWD not set\n"), 1);
		ret = chdir(current->content);
		if (ret == 0)
			printf("%s\n", current->content);
		return (ret);
	}
	ret = chdir(param);
	return (ret);
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
		printf("Minishell : cd : %s : ", param);
		printf ("No such file or directory or permission denied\n");
		return (-1);
	}
	return (0);
}
