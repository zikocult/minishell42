/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:01:48 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/01/24 16:27:17 by gbaruls-         ###   ########.fr       */
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
    char            *a_infile;
    char            *a_outfile;
    struct s_par    *next;
}   t_par;

typedef struct s_parse
{
    char *command;
    char *parameter;
    char *infile;
    char *outfile;
    char *a_infile;
    char *a_outfile;
    t_par *head;
    t_par *tail;
} t_parse;

#endif
