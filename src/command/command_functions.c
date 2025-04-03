/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2025/04/03 19:26:39 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	try_processes(t_parse *parse_data, t_env *data)
{
	if (process_data(parse_data, data, expand_mult))
		return (1);
	if (process_data(parse_data, data, handle_dollar))
		return (1);
	if (process_data(parse_data, data, double_simple_dollar))
		return (1);
	if (process_data(parse_data, data, simple_double_dollar))
		return (1);
	if (process_data(parse_data, data, double_quotes_dollar))
		return (1);
	if (process_data(parse_data, data, single_quotes))
		return (1);
	else
		return (0);
}

void	start_expansion(t_parse *parse_data, t_env *data)
{
	t_par	*current;

	current = parse_data->head;
	while (current)
	{
		if (try_processes(parse_data, data))
		{
			//pendiente desbloquar execute command;
			execute_command(current, data);
			current = current->next;
			continue ;
		}
		if (!current->command)
		{
			current = current->next;
			continue ;
		}

//		execute_pipex(parse_data, data);
		execute_command(current, data);
		current = current->next;
	}
	execute_pipex(parse_data, data);
}
	
void execute_command(t_par *current, t_env *env)
{
    char    *path;
    char    **res;
    char    **env_vars;
    
    path = check_path(current, env);
    build_command_args(current, &res);
    env_vars = enviroment(env);
    execve(path, res, env_vars);
//    exit(EXIT_FAILURE);
}
