/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:01:48 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/01/31 13:50:45 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../mylibft/include/libft.h"
# include "../mylibft/include/ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_par
{
    char            *command;
    char            *parameter;
    char            *infile;
    char            *outfile;
    struct s_par    *next;
}   t_par;

typedef struct s_parse
{
    char	*command;
    char	*parameter;
    char	*infile;
    char	*outfile;
	int		in_quotes;
    t_par	*head;
    t_par	*tail;
}	t_parse;


bool	validate_cmdbuff(char *cmd_buff);
void	jump_quotes(char *cmd_buff, int *i);


void	init_newnode(t_par *new_node);
void	init_data(t_parse *data, bool mode);
void	free_parse(t_parse *data);

void	append_parameter(char **parameter, char *token, int mode);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strcat(char *dst, const char *src);

void	free_temp_data(t_parse *data);
void	copy_data(t_par *new_node, t_parse *data);
void	add_node(t_parse *data);

void	process_token(char *start, char *end, int *mode, t_parse *data);
char	*handle_special_char(char *end, int *mode, t_parse *data);
void	parse_token(char *cmd_buff, t_parse *data);

#endif
