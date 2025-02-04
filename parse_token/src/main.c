/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaruls- <gbaruls-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:05:42 by Guillem Bar       #+#    #+#             */
/*   Updated: 2025/02/04 19:11:47 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include <stdio.h>


int main(int argc, char **argv)
{
    t_parse data;
	int	i;

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
        printf("\nCommand: %s\nParameter: %s\n",
        current->command, current->parameter);
		if (current->infile)
		{
			i = 0;
			while (current->infile[i])
			{
				printf("Infile[%d]: %s\n", i, current->infile[i]);
				i++;
			}
		}
		else 
			printf("Infile: No infiles\n");
		if (current->outfile)
		{
			i = 0;
			while (current->outfile[i])
			{
				printf("Outfile[%d]: %s\n", i, current->outfile[i]);
				i++;
			}
		}
		else 
			printf("Outfile: No Outfiles\n");
		printf("\n******************\n");
        current = current->next;
    }
    free_parse(&data);
    return (0);
}
