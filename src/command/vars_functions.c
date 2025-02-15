/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/02/15 13:33:11 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_variable(char *input, t_env *data)
{
	char	*var_name;
	t_var	*value;
	int		i;

	i = 0;
	var_name = (char *)malloc(ft_strlen(input) + 1);
	if_notstr(var_name);
	while (*input)
		var_name[i++] = *input++;
	var_name[i] = '\0';
	value = env_search(data, var_name);
	free(var_name);
	if (!value)
		return ("\0");
	return (value->content);
}

int	single_quotes(char *str)
{
	int		i;
	int		len;
	char	*new_com;

	len = ft_strlen(str) - 1;
	if (str[0] == '\'' && str[len] == '\'')
	{
		new_com = malloc(len + 1);
		i = 0;
		while (++i < len)
			new_com[i - 1] = str[i];
		new_com[len - 1] = '\0'; 
		str = NULL;
		str = ft_strdup(new_com);
		free(new_com);
		printf("%s\n", str);
		free(str);
		return (1) ;
	}
	else if((str[0] == '\'' && str[len] != '\''
		) || (str[0] != '\'' && str[len] == '\''))
	{
		printf("syntax error \n");
		return (1);
	}
	return (0);
}

int	dollar_search(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	if (str[i] == '$')
		return (i);
	return (0);
}

int	handle_dollar(char *str, t_env *data)
{
	int i;
	char *temp;
	char *expansion;

	if (ft_strchr(str, '$'))
	{
		i = dollar_search(str);
		temp = ft_strndup(str, i);
		if (str[i++] == '$')
		{
			expansion = expand_variable(&str[i], data);
			if (!expansion)
				return (1);
			else
			{
				free(str);
				str = ft_strjoin(temp, expansion);
			}
		}
		free(temp);
	}
	return (0);
}

int process_pardata(t_par *node, t_env *data, int (*func) (char *, t_env *))
{
	int	i;

    if (node->command)
		return(func(node->command, data));
	if (node->parameter)
		return (func(node->parameter, data)); 
	if (node->infile || node->outfile)
	{
		i = 0;
		while (node->infile[i++])
			func(node->infile[i], data);
		while (node->outfile[i++])
			func(node->outfile[i], data);
		return (1);
	}
	return (0);
}

int process_par(t_par *node, int (*func) (char *))
{
	int	i;

    if (node->command)
		return(func(node->command));
	if (node->parameter)
		return (func(node->parameter)); 
	if (node->infile || node->outfile)
	{
		i = 0;
		while (node->infile[i++])
			func(node->infile[i]);
		while (node->outfile[i++])
			func(node->outfile[i]);
		return (1);
	}
	return (0);
}
