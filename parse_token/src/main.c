/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:05:42 by Guillem Bar       #+#    #+#             */
/*   Updated: 2025/01/31 13:53:39 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"


int main(int argc, char **argv)
{
    t_parse data;

	init_data(&data, 1);
    if (argc == 2)
    {
		if (!validate_cmdbuff(argv[1]))
			return (0);
        parse_token(argv[1], &data);
    }
    t_par *current = data.head;
	printf("\n**************");
    while (current)
    {
        printf("\nCommand: %s\nParameter: %s\nInfile: %s\nOutfile: %s\n\n**************\n",
        current->command, current->parameter, current->infile, current->outfile);
        current = current->next;
    }
    free_parse(&data);

    return (0);
}
