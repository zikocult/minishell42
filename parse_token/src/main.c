/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Guillem Barulls <Guillem Barulls>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:05:42 by Guillem Barulls   #+#    #+#             */
/*   Updated: 2025/01/24 16:54:08 by gbaruls-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/parse.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*ptr;
	size_t	len;

	i = 0;
	if (n < ft_strlen(s))
		len = n;
	else
	 	len = ft_strlen(s);
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i] && i < n)
	{
		ptr[i] = (char)s[i];
		i++;
	}
	return (ptr);
}

char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dst);
	while (src[i] != '\0')
	{
		dst[len] = src[i];
		i++;
		len++;
	}
	dst[len] = '\0';
	return (dst);
}

void add_node(t_parse *data)
{
    t_par *new_node = (t_par *)malloc(sizeof(t_par));
    if (!new_node)
        return;

    new_node->command = NULL;
    new_node->parameter = NULL;
    new_node->infile = NULL;
    new_node->outfile = NULL;
    new_node->a_infile = NULL;
    new_node->a_outfile = NULL;
    new_node->next = NULL;

    if (data->command)
	{
        new_node->command = ft_strdup(data->command);
		free(data->command);
	}
    if (data->parameter)
    {
        new_node->parameter = ft_strdup(data->parameter);
        free(data->parameter);
    }
    if (data->infile)
    {
        new_node->infile = ft_strdup(data->infile);
        free(data->infile);
    }
    if (data->outfile)
    {
        new_node->outfile = ft_strdup(data->outfile);
        free(data->outfile);
    }
    if (data->a_infile)
    {
        new_node->a_infile = ft_strdup(data->a_infile);
        free(data->a_infile);
    }
    if (data->a_outfile)
    {
        new_node->a_outfile = ft_strdup(data->a_outfile);
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
    data->parameter = NULL;
    data->infile = NULL;
    data->outfile = NULL;
    data->a_infile = NULL;
    data->a_outfile = NULL;
}

void append_parameter(char **parameter, const char *token)
{
    if (*parameter)
    {
        size_t len = ft_strlen(*parameter) + ft_strlen(token) + 2;
        char *temp = (char *)malloc(len);
        if (temp)
        {
            ft_strcpy(temp, *parameter);
            ft_strcat(temp, " ");
            ft_strcat(temp, token);
            free(*parameter);
            *parameter = temp;
        }
    }
    else
    {
        *parameter = ft_strdup(token);
    }
}

void parse_token(char *cmd_buff, t_parse *data)
{
    char *start = cmd_buff;
    char *end = cmd_buff;
    int mode = 0;
	char	*token;

    while (*end)
    {
        if (*end == ' ' || *end == '|' || *end == '<' || *end == '>')
        {
            if (start != end)
            {
                token = ft_strndup(start, end - start);
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
                    data->command = token;
                else
                {
                    append_parameter(&data->parameter, token);
                    free(token);
                }
            }
            if (*end == '|')
                add_node(data);
            else if (*end == '<')
            {
                if (*(end + 1) == '<')
                {
                    mode = 3;
                    end++;
                }
                else
                    mode = 1;
            }
            else if (*end == '>')
            {
                if (*(end + 1) == '>')
                {
                    mode = 4;
                    end++;
                }
                else
                    mode = 2;
            }
            start = end + 1;
        }
        end++;
    }
    if (start != end)
    {
        token = ft_strndup(start, end - start);
        if (mode == 1)
            data->infile = token;
        else if (mode == 2)
            data->outfile = token;
        else if (mode == 3)
            data->a_infile = token;
        else if (mode == 4)
            data->a_outfile = token;
        else if (!data->command)
            data->command = token;
        else
        {
            append_parameter(&data->parameter, token);
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
        if (current->parameter)
            free(current->parameter);
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
    data.parameter = NULL;
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
        printf("Command: %s, parameter: %s, Infile: %s, Outfile: %s, A_Infile: %s, A_Outfile: %s\n",
               current->command, current->parameter, current->infile, current->outfile, current->a_infile, current->a_outfile);
        current = current->next;
    }
    free_parse(&data);

    return 0;
}
