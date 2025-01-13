/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/01/13 16:52:02 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_variable(char *input, t_env *data)
{
	char		*var_name;
	t_var		*value;
	int			i;

	i = 0;
	var_name = (char *)malloc(ft_strlen(input) + 1);
	if_notstr(var_name);
	while (*input && (ft_isalnum(*input) || (*input == '_')))
		var_name[i++] = *input++;
	var_name[i] = '\0';
	value = env_search(data, var_name);
	if (!value)
		return (NULL);
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
