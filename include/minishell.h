/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:29:23 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/04/03 18:47:13 by pamanzan         ###   ########.fr       */
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

# define READ_END 0       //index pipe extremo escritura
# define WRITE_END 1		//index pipe extremo lectura
# define FILE_MODE 0644

typedef struct s_var
{
	char			*type;
	char			*var_name;
	char			*content;
	struct s_var	*next;
}					t_var;

typedef struct s_env
{
	t_var			*head;
	t_var			*last_node;
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


// COMMAND
void				start_expansion(t_parse *parse_data, t_env *data);
//void				execute_command(t_par *current, t_env *data);

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
int					expand_mult(char **str, t_env *data);

//VARS_UTILS
int					not_expansion(char **str, char *temp, char *end);
char				*extract_expand(char *str, int i, t_env *data, char **end_ptr);
int					build_new_string(char **str, char *temp, char *new_str, char *end);
int					dollar_search(char *str);

//EXPAND_QUOTES
int					single_quotes(char **str, t_env *data);
int					double_simple_dollar(char **str, t_env *data);
int					simple_double_dollar(char **str, t_env *data);
int					double_quotes_dollar(char **str, t_env *data);

//EXPAND_UTILS
int					mult_dollar(char *str, char c);
char				*ft_strjoin_free(char *s1, char *s2);
char				*expansion(char **temp, t_env *data, char *result);
char				*append_text(char **temp, char *result, int flag);
int					expand_mult(char **str, t_env *data);

// STD_UTILS
int				process_data(t_parse *node, t_env *data, int (*func)(char **, t_env *));

// EXPORT_BUILTIN
void				export_list_builtin(t_env *data);
int					export_builtin(char *str, t_env *data);

// ENV_FUNCTIONS
void				*create_node2(char *env_var, t_var *new_node,
						char *equal_sign);
t_var				*create_node(char *env_var);
t_var				*env_search(t_env *data, char *str);
t_var				*insert_blank_node(t_env *data);

// ECHO_FUNCTIONS
void				handle_echo(char **args);

// PWD_BUILTIN
void				pwd_builtin(void);

// ENV_BUILTIN
void				env_list_builtin(t_env *data);
int					env_builtin(char *str, t_env *data);

//ADD_VAR
int					add_elem(t_env *data, char *name, char *content, char *type);

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

//PIPE_PATH.C
char	**enviroment(t_env *data);
//char	*find_path(char *copy, char *command);
void	free_pipes(int **pipes, int num_pipes);
int		**create_big_pip(int num_pipes);

//PIPE_COMMAND.C
void	create_pipes(int **pipes, int num_pipes);
void	close_pipes(int **pipes, int num_pipes);

//EXTRA_PIPE
int		count_pipes(t_parse *state);
void	execute_pipex(t_parse *state, t_env *data);

//PIPE
void    handle_child_process(t_par *current, int i, int **pipes, int num_pipes, t_env *env);
void    redirect_io(t_par *current, int i, int **pipes, int num_pipes);
void	close_parent_pipes(int i,  int num_pipes, int **pipes);
void	perror_exit(char *msg);
char	**buid_comand_args(t_par *current);
void	handle_pipes(t_parse *state, t_env *data);


#endif
