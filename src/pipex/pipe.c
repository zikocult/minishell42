/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:18:11 by pamanzan          #+#    #+#             */
/*   Updated: 2025/04/08 19:48:35 by pamanzan         ###   ########.fr       */
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
	res[k + 1] = '\0';
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

static char	*new_file_name(char *str)
{
	char	*temp;
	char	*new_str;
	int		i;

	temp = ft_strdup(str);
	if (!temp)
		return (NULL);
	new_str = (char *)ft_calloc(ft_strlen(temp), sizeof(char));
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
	return (new_str);
}

void    redirect_io(t_par *current, int i, int **pipes, int num_pipes)
{
    int		fd;
	char	*str;

    if (i == 0 && current->infile)
    {
		str = new_file_name(current->infile[0]);
        fd = open(str, O_RDONLY);
        if (fd == -1)
            perror_exit("open infile");
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    else if (i > 0)
        dup2(pipes[i - 1][READ_END], STDIN_FILENO);
    if (i == num_pipes && current->outfile)
    {
		int outf = count_outfile(current);
		int position = 0;
		while(current->outfile[position])
		{
			if (position == 0 && outf != 1) // primera posicion pero hay mas
			{
				str = new_file_name(current->outfile[position]);
				fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
			}
			if (position > 0 && position != outf) // posiciones intermedias
			{
				str = new_file_name(current->outfile[position]);
				fd = open(str, O_WRONLY | O_CREAT  FILE_MODE);
			}
			if (position > 0 && position == outf) // posicion final pero hay anteriores
			{
				str = new_file_name(current->outfile[position]);
				fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
			}
			if (position == 0 && outf == 1) // solo hay 1
			{
				str = new_file_name(current->outfile[0]);
				fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
			}
			if (fd == -1)
				perror_exit("open outfile");
			dup2(fd, STDOUT_FILENO);
			close(fd);	
			position++;
		}
	}
    else if (i < num_pipes)
		dup2(pipes[i][WRITE_END], STDOUT_FILENO);
}

void    handle_pipes(t_parse *state, t_env *data)
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

