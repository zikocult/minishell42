/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_temp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:29:23 by gbaruls-          #+#    #+#             */
/*   Updated: 2025/01/10 17:30:43 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TEMP_H
# define ENV_TEMP_H

# include "../mylibft/include/libft.h"
# include <stdlib.h>
# include <stdio.h>

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

#endif
