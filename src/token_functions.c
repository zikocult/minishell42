/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:37:35 by pamanzan          #+#    #+#             */
/*   Updated: 2024/12/10 18:45:42 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **parse_token(char *command_buff, t_env_vars *env)
{
    char **args;
    char *new_cmbuff = malloc(strlen(command_buff) * 2); // Asegura suficiente espacio para variables expandidas
    t_parse_state state;
    
    if (!new_cmbuff)
        malloc_error("error de malloc en el parseo");

    // Inicializa la estructura t_parse_state
    state.cmbuff = command_buff;
    state.new_cmbuff = new_cmbuff;
    state.i = 0;
    state.j = 0;

    // Procesa el buffer de entrada
    while (state.cmbuff[state.i])
    {
        if (state.cmbuff[state.i] == '\'')
        {
			state.i++;
            handle_squotes(&state);
        }
        else if (state.cmbuff[state.i] == '\"')
        {
			state.i++;
            handle_dquotes(&state, env);
        }
        else
        {
            state.new_cmbuff[state.j++] = state.cmbuff[state.i++];
        }
    }

    // Termina el nuevo buffer con un carácter nulo
    state.new_cmbuff[state.j] = '\0';

    args = ft_split(state.new_cmbuff, ' ');
    free(state.new_cmbuff);

    return args;
}
		
/*esta ya no se usa de momento*/
int	count_args(char **args) 
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}
