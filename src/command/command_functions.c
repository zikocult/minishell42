/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:07:30 by patri             #+#    #+#             */
/*   Updated: 2025/02/11 19:39:33 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_process(char *path, t_par *current)
{
	pid_t	pid;
	int		*status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, &current->command, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, status, 0);
	else
		perror("Error en fork");
}

/* static void	next_node(t_par *current) */
/* { */
/* 	if (!current->command && !current->infile && !current->outfile) */
/* 	{ */
/* 		if (current->next) */
/* 			current = current->next; */
/* 	} */
/* } */

static void	execute_command2(t_par *current, t_env *data)
{
	char	*path;

	path = check_path(current, data);
	child_process(path, current);
	free(path);
}

static int	dollar_search(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	if (str[i] == '$')
		return (i);
	return (0);
}

void	execute_command(t_parse *parse_data, t_env *data)
{
	t_par	*current;
	char	*expansion;
	char	*temp;
	char	*new_com;
	int		i;
	int		j;
	int		len;

	current = parse_data->head;
	temp = NULL;
	while (current)
	{
		len = ft_strlen(current->command) - 1;
		new_com = malloc(len);
		if (current->command[0] == '\'' && current->command[len] == '\'')
		{
			i = 1;
			j = 0;
			while (i < len)
				new_com[j++] = current->command[i++];
			free(current->command);
			current->command = ft_strdup(new_com);
			free(new_com);
			printf("%s\n", current->command);
			current = current->next;
			continue ;
		}
		if ((current->command[0] == '\'' && current->command[len] != '\''
				) || (current->command[0] != '\'' && current->command[len] == '\''))	
		{
			printf("sytax error \n");
			current = current->next;
			continue ;
		}
		i = 0;
		len = 0;
		if (ft_strchr(current->command, '$'))
		{
			i = dollar_search(current->command);
			temp = (char *)malloc(i + 1 * sizeof(char));
			j = 0;
			while (j < i)
			{
				temp[j] = current->command[j];
				j++;
			}
			if (temp)
				temp[i] = '\0';
			if (current->command[i] == '$')
			{
				i++;
				expansion = expand_variable(&current->command[i], data);
				if (!expansion)
				{
					current = current->next;
					continue ;
				}
				else
				{
					free(current->command);
					if (temp)
						current->command = ft_strjoin(temp, expansion);
					else
						current->command = ft_strdup(expansion);
				}
			}
			free(temp);
		}
		if (!current->command)
		{
			current = current->next;
			continue ;
		}
		execute_command2(current, data);
		current = current->next;
	}
}
