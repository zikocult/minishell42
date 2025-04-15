/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:18:11 by pamanzan          #+#    #+#             */
/*   Updated: 2025/04/15 16:04:00 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    build_command_args(t_par *current, char **res, char **param)
{
    int     k;

	k = 0;
    res[0] = ft_strdup(current->command);
	if (current->parameter)
	{
		while (param && param[k])
		{
			res[k + 1] = ft_strdup(param[k]);
			k++;
		}
		free_memory(param);
	}

	res[k + 1] = NULL;
}

void handle_child_process(t_par *current, t_child params, t_env *data)
{
    char *path;
    char **res;
    char **env_vars;
    int count;
    char **param;

    count = count_param(current, &param);
    res = ft_calloc(sizeof(char *), count + 2);
    if (!res)
        exit(EXIT_FAILURE);
    redirect_io(current, params);
    close_pipes(params.pipes, params.num_pipes);
    path = check_path(current, data);
    build_command_args(current, res, param);
    env_vars = enviroment(data);
    execve(path, res, env_vars);
    free_pipes(params.pipes, params.num_pipes);
    free(*res);

    exit(EXIT_FAILURE);
}

char *new_file_name(char *str)
{
    char *temp;
    char *new_str;
    char *trimmed_str;
    int i;

    if (!str)
        return (NULL);
    temp = ft_strdup(str);
    if (!temp)
        return (NULL);
    new_str = (char *)ft_calloc(ft_strlen(temp) + 1, sizeof(char));
    if (!new_str)
        return (free(temp), NULL);
    i = 1;
    while (temp[i])
    {
        new_str[i - 1] = temp[i];
        i++;
    }
    free(temp);
    trimmed_str = ft_strtrim(new_str, " \n");
    return (free(new_str), trimmed_str);
}

static void handle_heredoc(void)
{
	int fd;

	printf("Aquí va el heredoc\n");
	fd = open("/dev/null", O_RDONLY);  // Abre un descriptor no bloqueante
	if (fd == -1)
		malloc_error("open /dev/null");	
}


void    redirect_io(t_par *current, t_child params)
{
    int		fd;
	char	*str;

    if (params.i == 0 && current->infile)
    {
		params.position = 0;
		params.last_fd = -1;  // Guardamos el fd del último archivo
		while (current->infile[params.position])
		{
			if (ft_strncmp(current->infile[params.position], "<", 1) == 0)  // Si es HereDoc (ej: << EOF)
				handle_heredoc();
			else  // Redirección normal (< archivo)
			{
				str = new_file_name(current->infile[params.position]);
				if (!str)
					malloc_error("malloc failed");
				fd = open(str, O_RDONLY);
				if (fd == -1)
					malloc_error("open infile");
			}	
			if (params.last_fd != -1)  // Cerramos archivos anteriores (no se usan)
				close(params.last_fd);
			params.last_fd = fd;  // Actualizamos el ultimo fd
			params.position++;
		}

		// Redirigimos stdin SOLO al ultimo archivo (o HereDoc)
		if (params.last_fd != -1)
		{
			dup2(params.last_fd, STDIN_FILENO);
			close(params.last_fd);
		}
    }
    else if (params.i > 0)
        dup2(params.pipes[params.i - 1][READ_END], STDIN_FILENO);
    if (params.i == params.num_pipes && current->outfile)
    {
		int outf = count_outfile(current);
		int position = 0;
		int last_fd = -1;  // Guardaremos el fd del ultimo archivo

		while (current->outfile[position])
		{
			str = new_file_name(current->outfile[position]);
			if (!str)
				malloc_error("malloc failed");
			if (position == outf)
				fd = open(str, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE);
			else
				fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
			if (fd == -1)
				malloc_error("open outfile");

			if (last_fd != -1)  // Cerrar archivos anteriores (no se escriben)
				close(last_fd);
			last_fd = fd;  // Actualizamos el ultimo fd
			position++;
		}

		// Redirigimos stdout SOLO al ultimo archivo
		if (last_fd != -1)
		{
			dup2(last_fd, STDOUT_FILENO);
			close(last_fd);
		}
		
	}
    else if (params.i < params.num_pipes)
		dup2(params.pipes[params.i][WRITE_END], STDOUT_FILENO);
}

void execute_pipex(t_parse *state, t_env *data)
{
    t_par *current = state->head;
    t_child params;
    pid_t pid;

    params.i = 0;
    params.num_pipes = count_pipes(state);
    params.pipes = create_big_pip(params.num_pipes);
    create_pipes(params.pipes, params.num_pipes);
    while (current)
    {
        pid = fork();
        if (pid == -1)
            malloc_error("fork");
        if (pid == 0)
            handle_child_process(current, params, data);
        close_parent_pipes(params.i, params.num_pipes, params.pipes);
		wait(NULL);
        current = current->next;
		params.i++;
    }
    free_pipes(params.pipes, params.num_pipes);
}


