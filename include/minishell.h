/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:29:23 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/03/10 17:03:41 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../mylibft/include/ft_printf.h"
# include "../mylibft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_var
{
	char			*var_name;
	char			*content;
	struct s_var	*next;
}					t_var;

typedef struct s_env
{
	t_var			*head;
	t_var			*head_env;
	t_var			*tail;
}					t_env;

typedef struct s_par
{
	char			*command;
	char			*parameter;
	char			**infile;
	char			**outfile;
	struct s_par	*next;
}					t_par;

typedef struct s_parse
{
	char			*command;
	char			*parameter;
	char			*infile;
	char			*outfile;
	int				in_single_quotes;
	int				in_double_quotes;
	int				mode;
	t_par			*head;
	t_par			*tail;
}					t_parse;

// HANDLE_QUOTES
// void				handle_quotes_general(t_parse *state, t_env *data,
// 						char *cmd_buff);
// void				handle_squotes(t_parse *state, char *cmd_buff);
// void				handle_dquotes(t_parse *state, t_env *data, char *cmd_buff);
// void				without_quotes(t_parse *state, t_env *data, char *cmd_buff);
// void				clean_quotes(t_parse *state, char c, char *cmd_buff);

// COMMAND
char				*command_needed(char *command, t_env *data);
void				execute_command(t_parse *parse_data, t_env *data);

// PATH
char				*find_path(t_par *current, t_env *data);
char				*check_path(t_par *current, t_env *data);
char				*get_full_path(char *path, char *command);

// INIT_FUNCTIONS
void				init_envi_list(t_env *data);
void				init_parse_state(t_parse *state, char *command_buff);
void				init_list(t_env *data, char **env);
void				init_parse(char *command_buff, t_parse *state);

// BODY_FUNCTIONS
int					select_type(char *command_buff, t_env *data);
void				print_token(t_parse *data);

// SECURITY_FUNCTIONS
void				free_memory(char **ptr);
void				malloc_error(char *str);
void				free_list(t_env *data);
char				*if_notstr(char *str);

// VARS_FUNCTIONS
char				*expand_variable(char *input, t_env *data);
int					handle_dollar(char **str, t_env *data);
int		expand_mult(char **str, t_env *data);

//VARS_UTILS
int		not_expansion(char **str, char *temp, char *end);
char	*extract_expand(char *str, int i, t_env *data, char **end_ptr);
int		build_new_string(char **str, char *temp, char *new_str, char *end);
int		dollar_search(char *str);

//EXPAND_QUOTES
int				single_quotes(char **str, t_env *data);
int				double_simple_dollar(char **str, t_env *data);
int				double_quotes_dollar(char **str, t_env *data);

//EXPAND_UTILS
int		mult_dollar(char *str, char c);
char	*ft_strjoin_free(char *s1, char *s2);
char	*expansion(char **temp, t_env *data, char *result);
char	*append_text(char **temp, char *result, int flag);
int		expand_mult(char **str, t_env *data);

// STD_UTILS
int				process_data(t_parse *node, t_env *data, int (*func)(char **, t_env *));

// ENV_FUNCTIONS
void				*create_node2(char *env_var, t_var *new_node,
						char *equal_sign);
t_var				*create_node(char *env_var);
t_var				*env_search(t_env *data, char *str);
t_var				*insert_blank_node(t_env *data);

// ECHO_FUNCTIONS
void				handle_echo(char **args);

// ENV_BUILTIN
void				env_builtin(t_env *data);
void				var_builtin(t_env *data);
void				add_elem(t_env *data, char *name, char *content);

// UNSET_BUILTIN
void				unset_builtin(t_env *data, char *str);

// VALIDATE_REDIRECTIONS
bool				check_consecutive_redirections(char *cmd_buff);

// VALIDATE_BUFF
bool				validate_cmdbuff(char *cmd_buff);
bool				check_parse_error(char c, int count);

// VALIDATE_UTILS
void				jump_single_quotes(char *cmd_buff, int *i);
void				jump_double_quotes(char *cmd_buff, int *i);
void				init_vars(int *i, int *count, char *last_char);
void				validation_reset(int *count, char *last_char);

// PARSE_NODE
void				free_temp_data(t_parse *data);
void				copy_data(t_par *new_node, t_parse *data);
void				add_node(t_parse *data);

// PARSE_INIT
void				init_newnode(t_par *new_node);
void				init_data(t_parse *data, bool mode);
void				free_parse(t_parse *data);

// PARSE_UTILS
void				append_parameter(char **parameter, char *token, int mode);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strcat(char *dst, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);

// PARSE_TOKEN
void				process_token(char *start, char *end, int *mode,
						t_parse *data);
char				*handle_special_char(char *end, int *mode, t_parse *data);
void				parse_token(char *cmd_buff, t_parse *data);

// PARSE_REMOVE_QUOTES
void				remove_quotes_from_par(t_par *current);
void				remove_quotes_from_par2(t_par *current, int i);
bool				search_dollar_parse(char *str);
char				*return_str_parse(char *str);
char				*remove_single_quotes(char *str);
char				*remove_double_quotes(char *str);

// VALIDATE_QUOTES
bool				validate_quotes(char *cmd_buff);
bool				len_buff(char *cmd_buff);

#endif
