/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:29:23 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/01/07 15:08:37 by pamanzan         ###   ########.fr       */
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

typedef struct s_parse_state
{
    char	*cmbuff;
    char	*new_cmbuff;
    int		i;
    int		j;
}			t_parse_state;

//COMMAND_FUNCTIONS
char	*find_path(char **command, t_env_vars *env);
void	execute_command(char **command, t_env_vars *env);

//TOKEN_FUNCTIONS
char	**parse_token(char *command_buff, t_env_vars *env);
int		count_args(char **args);

//HANDLE_QUOTES
void	handle_quotes_general(t_parse_state *state, t_env_vars *env);
void	handle_squotes(t_parse_state *state);
void	handle_dquotes(t_parse_state *state, t_env_vars *env);
void	without_quotes(t_parse_state *state, t_env_vars *env);

//INIT_FUNCTIONS
void	init_env_vars(t_env_vars *env);
void	env_vars(char command_buf, char **env);
void	init_parse_state(t_parse_state *state, char *command_buff);

//BODY_FUNCTIONS
int		select_type(char *command_buff, t_env_vars *env);

//SECURITY_FUNCTIONS
void	free_memory(char **ptr);
void	malloc_error(char *str);

//VARS_FUNCTIONS
char	*get_env_value(t_env_vars *env, const char *var_name);
char	*expand_variable(const char *input, t_env_vars *env);
void	handle_echo(char **args);




#endif
