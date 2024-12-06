/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:37:35 by pamanzan          #+#    #+#             */
/*   Updated: 2024/12/06 12:01:22 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

char	*find_path(char *command)
{
	int		i;
	char	*full_path;
	char	*path;
	char	**result;
	int		found;
	char	*copy;

	copy = getenv("PATH");
	found = 0;
	result = ft_split(copy, ':');

	i = 0;
	while (result[i++] != NULL)
	{
		path = ft_strjoin(result[i], "/");
		full_path = ft_strjoin(path, command);
		free(path);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			break ;
		}
		free(full_path);
	}
	if (!found)
		ft_printf("Comando no encontrado");
	return (free_memory(result), full_path);
}

char **parse_token(char *command_buff)
{
	int 	i;
	char	**args;
	char 	*start;
	size_t	len;

	i = 0;
	start = command_buff;
	args = malloc(sizeof(char *) * 42);
	len = 0;
	if (!args)
		malloc_error("error de malloc en el parseo");
	while (*command_buff)
	{
        if (*command_buff == ' ')
		{
            if (len > 0) 
			{
                args[i] = strndup(start, len);
                i++;
                len = 0;
            }
            start = command_buff + 1; 
        }
		else 
            len++;
        command_buff++;
    }
    if (len > 0)   
		args[i++] = strndup(start, len);
    args[i] = NULL;    
	return args;	
}
