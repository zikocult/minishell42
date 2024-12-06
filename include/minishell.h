/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:29:23 by gbaruls-          #+#    #+#             */
/*   Updated: 2024/12/06 09:52:24 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H 
# define MINISHELL_H

# include "../mylibft/include/libft.h"
# include "../mylibft/include/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
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

//TOKEN_FUNCTIONS
char	*enviroment(char **env);
char	*find_path(char *command);
void	free_memory(char **ptr);

//INIT_FUNCTIONS
void	init_env_vars(t_env_vars *env);

#endif
