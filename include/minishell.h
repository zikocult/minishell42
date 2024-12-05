/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:29:23 by gbaruls-          #+#    #+#             */
/*   Updated: 2024/12/05 13:02:38 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H 
# define MINISHELL_H

# include "../mylibft/include/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

#include <unistd.h>   // For access() and X_OK
#include <stdio.h>    // For printf() (or ft_printf if it's custom)
# include "../mylibft/include/ft_printf.h"

# include <fcntl.h>
# include <string.h>
# include <errno.h>

//TOKEN_FUNCTIONS
char	*enviroment(char **env);
char	*find_path(char *command);
void	free_memory(char **ptr);

#endif
