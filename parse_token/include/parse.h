/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:01:48 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/01/22 20:38:21 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../mylibft/include/libft.h"
# include "../mylibft/include/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

typedef struct s_par
{
	char			*command;
	char			*variable;
	char			*infile;
	char			*outfile;
	struct s_par	*next;
}	t_par;

typedef struct s_parse
{
	t_par	*head;
	t_par	*tail;
}	t_parse;

#endif
