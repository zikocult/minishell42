/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:29:23 by gbaruls-          #+#    #+#             */
/*   Updated: 2024/12/08 09:56:40 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H 
# define MINISHELL_H

# include "../mylibft/include/libft.h"
# include "../mylibft/include/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct s_env_vars
{
	char	*path;
	char	*home;
	char	*user;
	char	*shell;
	char	*pwd;
	char	*oldpwd;
	char	*env;
}			t_env_vars;

//COMMAND_FUNCTIONS
char	*find_path(char **command, t_env_vars *env);
void	execute_command(char **command, t_env_vars *env);

//TOKEN_FUNCTIONS
char	**parse_token(char *command_buff);

//INIT_FUNCTIONS
void	init_env_vars(t_env_vars *env);

//BODY_FUNCTIONS
int		select_type(char *command_buff, t_env_vars *env);

//SECURITY FUNCTIONS
void	free_memory(char **ptr);
void	malloc_error(char *str);

#endif
