/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:31:22 by patri             #+#    #+#             */
/*   Updated: 2025/02/06 16:37:58 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
	
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

void	commands(t_parse *parse_data, t_env *data)
{
	char	*expansion;
	int		i;
	t_par		*current;

	i = 0;
	current = parse_data->head;
	while(current)	
	{
		if (current->command[0] == '$')
		{
			i++;
			expansion = expand_variable(&current->command[i], data);
			free(current->command);
			current->command = ft_strdup(expansion);
			current->command = NULL;
		}	
			execute_command(parse_data, data);
		current = current->next;
		
	}
}
