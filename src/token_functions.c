/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:37:35 by pamanzan          #+#    #+#             */
/*   Updated: 2024/12/07 12:11:00 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

char **parse_token(char *command_buff)
{
	char	**args;
	char	*new_cmbuff;
	int		i;
	int		j;

	new_cmbuff = malloc(sizeof(char *) * 42);
	if (!new_cmbuff)
		malloc_error("error de malloc en el parseo");
	i = 0;
	j = 0;
	while (command_buff[i])
	{
        if (command_buff[i] == 39) //TODO
			i++; //en este caso las variables no se expanden en el resto si
		if (command_buff[i] == 34)
			i++;
		new_cmbuff[j] = command_buff[i];
		i++;
		j++;
    }
	args = ft_split(new_cmbuff, ' ');
	return (args);	
}
