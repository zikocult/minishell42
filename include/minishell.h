/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:29:23 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/01/28 17:19:01 by gbaruls-         ###   ########.fr       */
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
# include <stdbool.h>

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

typedef struct s_par
{
    char            *command;
    char            *parameter;
    char            *infile;
    char            *outfile;
    char            *a_infile;
    char            *a_outfile;
    struct s_par    *next;
}   t_par;

typedef struct s_parse
{
    char	*command;
    char	*parameter;
    char	*infile;
    char	*outfile;
    char	*a_infile;
    char	*a_outfile;
    t_par	*head;
    t_par	*tail;
}			t_parse;

//COMMAND_FUNCTIONS
char	*find_path(char **command, t_env *data);
void	execute_command(char **command, t_env *data);

//HANDLE_QUOTES
void	handle_quotes_general(t_parse *state, t_env *data, char *cmd_buff);
void	handle_squotes(t_parse *state, char *cmd_buff);
void	handle_dquotes(t_parse *state, t_env *data, char *cmd_buff);
void	without_quotes(t_parse *state, t_env *data, char *cmd_buff);
void	clean_quotes(t_parse *state, char c, char *cmd_buff);

//INIT_FUNCTIONS
void	init_parse_state(t_parse *state, char *command_buff);
void	init_list(t_env *data, char **env);
void	init_parse(char *command_buff, t_parse *state);

//BODY_FUNCTIONS
int		select_type(char *command_buff, t_env *data);

//SECURITY_FUNCTIONS
void	free_memory(char **ptr);
void	malloc_error(char *str);
void	free_list(t_env	*data);
char	*if_notstr(char *str);

//VARS_FUNCTIONS
char	*expand_variable(char *input, t_env *data);

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

//VALIDATE_BUFF
bool	validate_cmdbuff(char *cmd_buff);

//VALIDATE_UTILS
void	jump_quotes(char *cmd_buff, int *i);

//PARSE_NODE
void	free_temp_data(t_parse *data);
void	copy_data(t_par *new_node, t_parse *data);
void	add_node(t_parse *data);

//PARSE_INIT
void	init_newnode(t_par *new_node);
void	init_data(t_parse *data);
void	free_parse(t_parse *data);

//PARSE_UTILS
void	append_parameter(char **parameter, const char *token);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strcat(char *dst, const char *src);

//PARSE_TOKEN
void	process_token(char *start, char *end, int *mode, t_parse *data);
char	*handle_special_char(char *end, int *mode, t_parse *data);
void	parse_token(char *cmd_buff, t_parse *data);

#endif
