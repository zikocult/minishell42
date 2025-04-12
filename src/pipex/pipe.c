/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:18:11 by pamanzan          #+#    #+#             */
/*   Updated: 2025/04/12 10:29:23 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int count_param(t_par *current, char ***param)
{
	int count;

	count = 0;
    if (current->parameter)
    {
        *param = ft_split(current->parameter, ' ');
        while (*param && (*param)[count])
			count++;
    }
	return (count);
}

static int count_outfile(t_par *current)
{
	int	count;

	count = 0;
	while (current->outfile[count])
		count++;
	printf("hay %i outfiles\n", count);
	return (count);
}

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
			free(param[k]);
			k++;
		}
	}
	res[k + 1] = NULL;
}

void    handle_child_process(t_par *current, int i, int **pipes, int num_pipes, t_env *data)
{
    char    *path;
    char    **res;
    char    **env_vars;
	int		count;
	char	**param;

	count = count_param(current, &param);
	res = ft_calloc(sizeof(char *), count + 2);
    redirect_io(current, i, pipes, num_pipes);
    close_pipes(pipes, num_pipes);
    path = check_path(current, data);
    build_command_args(current, res, param);
    env_vars = enviroment(data);
    execve(path, res, env_vars);
	free_pipes(pipes, num_pipes);
	free(*res);
	exit(EXIT_FAILURE);
}

static char *new_file_name(char *str)
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

    new_str = (char *)ft_calloc(ft_strlen(temp) + 1, sizeof(char)); // +1 para '\0'
    if (!new_str)
    {
        free(temp);
        return (NULL);
    }

    i = 1;
    while (temp[i])
    {
        new_str[i - 1] = temp[i];
        i++;
    }
    free(temp);

    trimmed_str = ft_strtrim(new_str, " \n");
    free(new_str); // Liberamos new_str después de usarlo
    return (trimmed_str); // Retornamos el resultado de ft_strtrim (puede ser NULL)
}

void    redirect_io(t_par *current, int i, int **pipes, int num_pipes)
{
    int		fd;
	char	*str;

    if (i == 0 && current->infile)
    {
		int position = 0;
		int last_fd = -1;  // Guardamos el fd del último archivo

		while (current->infile[position])
		{
			if (ft_strncmp(current->infile[position], "<", 1) == 0)  // Si es HereDoc (ej: << EOF)
			{
				printf("Aquí va el heredoc\n");
				fd = open("/dev/null", O_RDONLY);  // Abre un descriptor no bloqueante
				if (fd == -1)
					perror_exit("open /dev/null");			
			}
			else  // Redirección normal (< archivo)
			{
				str = new_file_name(current->infile[position]);
				if (!str)
					perror_exit("malloc failed");
				fd = open(str, O_RDONLY);
				if (fd == -1)
					perror_exit("open infile");
			}	
			if (last_fd != -1)  // Cerramos archivos anteriores (no se usan)
				close(last_fd);
			last_fd = fd;  // Actualizamos el último fd
			position++;
		}

		// Redirigimos stdin SOLO al último archivo (o HereDoc)
		if (last_fd != -1)
		{
			dup2(last_fd, STDIN_FILENO);
			close(last_fd);
		}
    }
    else if (i > 0)
        dup2(pipes[i - 1][READ_END], STDIN_FILENO);
    if (i == num_pipes && current->outfile)
    {
		int outf = count_outfile(current);
		int position = 0;
		int last_fd = -1;  // Guardaremos el fd del último archivo

		while (current->outfile[position])
		{
			str = new_file_name(current->outfile[position]);
			if (!str)
				perror_exit("malloc failed");
			if (position == outf)
				fd = open(str, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE);
			else
				fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
			if (fd == -1)
				perror_exit("open outfile");

			if (last_fd != -1)  // Cerrar archivos anteriores (no se escriben)
				close(last_fd);
			last_fd = fd;  // Actualizamos el último fd
			position++;
		}

		// Redirigimos stdout SOLO al último archivo
		if (last_fd != -1)
		{
			dup2(last_fd, STDOUT_FILENO);
			close(last_fd);
		}
		
	}
    else if (i < num_pipes)
		dup2(pipes[i][WRITE_END], STDOUT_FILENO);
}

void    execute_pipex(t_parse *state, t_env *data)
{
    t_par   *current;
    int     i;
    int     pid;
    int     num_pipes;
    int     **pipes;
    
    num_pipes = count_pipes(state);
    pipes = create_big_pip(num_pipes);
    create_pipes(pipes, num_pipes);
    current = state->head;
    i = 0;
    while (current)
    {
        pid = fork();
        if (pid == -1)
            perror_exit("fork");
        if (pid == 0)
            handle_child_process(current, i, pipes, num_pipes, data);
        close_parent_pipes(i, num_pipes, pipes);
        wait(NULL);
        current = current->next;
        i++;
    }
    free_pipes(pipes, num_pipes);
}

void    close_parent_pipes(int i, int num_pipes, int **pipes)
{
    if (i > 0)
        close(pipes[i - 1][READ_END]);
    if (i < num_pipes)
        close(pipes[i][WRITE_END]);
}

void    perror_exit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

