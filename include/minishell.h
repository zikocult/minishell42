/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:29:23 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/01/20 17:22:32 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H 
# define MINISHELL_H

# include "../mylibft/include/libft.h"
# include "../mylibft/include/ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct s_var
{
	char			*var_name;
	char			*content;
	struct s_var	*next;
}	t_var;

typedef struct s_env
{
	t_var	*head;
	t_var	*tail;
}	t_env;

typedef struct s_parse
{
	char	**new_cmbuff;
	int		len;
	int		i;
	int		j;
}			t_parse;

//COMMAND_FUNCTIONS
char	*find_path(char **command, t_env *data);
void	execute_command(char **command, t_env *data);

//TOKEN_FUNCTIONS
char	**parse_token(char *command_buff, t_env *env, t_parse *state);
int		count_args(char **args);

//HANDLE_QUOTES
void	handle_quotes_general(t_parse *state, t_env *data, char *cmd_buff);
void	handle_squotes(t_parse *state, char *cmd_buff);
void	handle_dquotes(t_parse *state, t_env *data, char *cmd_buff);
void	without_quotes(t_parse *state, t_env *data, char *cmd_buff);
void	clean_quotes(t_parse *state, char c, char *cmd_buff);

//INIT_FUNCTIONS
void	init_parse_state(t_parse *state, char *command_buff);
void	init_list(t_env *data, char **env);

//BODY_FUNCTIONS
int		select_type(char *command_buff, t_env *data);

//SECURITY_FUNCTIONS
void	free_memory(char **ptr);
void	malloc_error(char *str);
void	free_list(t_env	*data);
char	*if_notstr(char *str);

//VARS_FUNCTIONS
char	*expand_variable(char *input, t_env *data);
void	handle_echo(char **args);

//ENV_FUNCTIONS
void	*create_node2(char *env_var, t_var *new_node, char *equal_sign);
t_var	*create_node(char *env_var);
t_var	*env_search(t_env *data, char *str);
t_var	*insert_blank_node(t_env *data);

//ECHO_FUNCTIONS
void	handle_echo(char **args);

//ENV_BUILTIN
void	env_builtin(t_env *data);
void	add_elem(t_env *data, char *name, char *content);

#endif
