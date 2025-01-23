/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:05:42 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/01/23 19:24:22 by Guillem Barulls  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/parse.h"

void add_node(t_parse *data)
{
    t_par *new_node = (t_par *)malloc(sizeof(t_par));
    if (!new_node)
        return;

    new_node->command = NULL;
    new_node->variable = NULL;
    new_node->infile = NULL;
    new_node->outfile = NULL;
    new_node->a_infile = NULL;
    new_node->a_outfile = NULL;
    new_node->next = NULL;

    if (data->command)
	{
        new_node->command = strdup(data->command);
		free(data->command);
	}
    if (data->variable)
    {
        new_node->variable = strdup(data->variable);
        free(data->variable);
    }
    if (data->infile)
    {
        new_node->infile = strdup(data->infile);
        free(data->infile);
    }
    if (data->outfile)
    {
        new_node->outfile = strdup(data->outfile);
        free(data->outfile);
    }
    if (data->a_infile)
    {
        new_node->a_infile = strdup(data->a_infile);
        free(data->a_infile);
    }
    if (data->a_outfile)
    {
        new_node->a_outfile = strdup(data->a_outfile);
        free(data->a_outfile);
    }

    if (!data->head)
    {
        data->head = new_node;
        data->tail = new_node;
    }
    else
    {
        data->tail->next = new_node;
        data->tail = new_node;
    }
    data->command = NULL;
    data->variable = NULL;
    data->infile = NULL;
    data->outfile = NULL;
    data->a_infile = NULL;
    data->a_outfile = NULL;
}

void append_variable(char **variable, const char *token)
{
    if (*variable)
    {
        size_t len = strlen(*variable) + strlen(token) + 2;
        char *temp = (char *)malloc(len);
        if (temp)
        {
            strcpy(temp, *variable);
            strcat(temp, " ");
            strcat(temp, token);
            free(*variable);
            *variable = temp;
        }
    }
    else
    {
        *variable = strdup(token);
    }
}

void parse_token(char *cmd_buff, t_parse *data)
{
    char *start = cmd_buff;
    char *end = cmd_buff;
    int mode = 0;

    while (*end)
    {
        if (*end == ' ' || *end == '|' || *end == '<' || *end == '>')
        {
            if (start != end)
            {
                char *token = strndup(start, end - start);
                if (mode == 1)
                {
                    data->infile = token;
                    mode = 0;
                }
                else if (mode == 2)
                {
                    data->outfile = token;
                    mode = 0;
                }
                else if (mode == 3)
                {
                    data->a_infile = token;
                    mode = 0;
                }
                else if (mode == 4)
                {
                    data->a_outfile = token;
                    mode = 0;
                }
                else if (!data->command)
                {
                    data->command = token;
                }
                else
                {
                    append_variable(&data->variable, token);
                    free(token);
                }
            }
            if (*end == '|')
            {
                add_node(data);
            }
            else if (*end == '<')
            {
                if (*(end + 1) == '<')
                {
                    mode = 3;
                    end++;
                }
                else
                {
                    mode = 1;
                }
            }
            else if (*end == '>')
            {
                if (*(end + 1) == '>')
                {
                    mode = 4;
                    end++;
                }
                else
                {
                    mode = 2;
                }
            }
            start = end + 1;
        }
        end++;
    }
    if (start != end)
    {
        char *token = strndup(start, end - start);
        if (mode == 1)
        {
            data->infile = token;
        }
        else if (mode == 2)
        {
            data->outfile = token;
        }
        else if (mode == 3)
        {
            data->a_infile = token;
        }
        else if (mode == 4)
        {
            data->a_outfile = token;
        }
        else if (!data->command)
        {
            data->command = token;
        }
        else
        {
            append_variable(&data->variable, token);
            free(token);
        }
    }
    add_node(data);
}

void free_parse(t_parse *data)
{
    t_par *current = data->head;
    t_par *next;

    while (current)
    {
        next = current->next;
        if (current->command)
            free(current->command);
        if (current->variable)
            free(current->variable);
        if (current->infile)
            free(current->infile);
        if (current->outfile)
            free(current->outfile);
        if (current->a_outfile)
            free(current->a_outfile);
        if (current->a_infile)
            free(current->a_infile);
        free(current);
        current = next;
    }
    data->head = NULL;
    data->tail = NULL;
}

int main(int argc, char **argv)
{
    t_parse data;
    data.head = NULL;
    data.tail = NULL;
    data.command = NULL;
    data.variable = NULL;
    data.infile = NULL;
    data.outfile = NULL;
    data.a_infile = NULL;
    data.a_outfile = NULL;

    if (argc == 2)
    {
        parse_token(argv[1], &data);
    }
    t_par *current = data.head;
    while (current)
    {
        printf("Command: %s, Variable: %s, Infile: %s, Outfile: %s, A_Infile: %s, A_Outfile: %s\n",
               current->command, current->variable, current->infile, current->outfile, current->a_infile, current->a_outfile);
        current = current->next;
    }
    free_parse(&data);

    return 0;
}
