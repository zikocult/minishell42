/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:18:11 by pamanzan          #+#    #+#             */
/*   Updated: 2025/04/03 19:19:42 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    build_command_args(t_par *current, char ***res)
{
    char    **param;
    int     k;
    int     count;

    param = NULL;
    count = 0;
    if (current->parameter)
    {
        param = ft_split(current->parameter, ' ');
        while (param && param[count])
            count++;
    }
    *res = malloc(sizeof(char *) * (count + 2));
    (*res)[0] = ft_strdup(current->command);
    k = -1;
    while (param && param[++k])
    {
        (*res)[k + 1] = ft_strdup(param[k]);
        free(param[k]);
    }
    free(param);
    (*res)[k + 1] = NULL;
}

void    handle_child_process(t_par *current, int i, int **pipes, int num_pipes, t_env *data)
{
    char    *path;
    char    **res;
    char    **env_vars;
    
    redirect_io(current, i, pipes, num_pipes);
    close_pipes(pipes, num_pipes);
    path = check_path(current, data);
    build_command_args(current, &res);
    env_vars = enviroment(data);
    execve(path, res, env_vars);
    exit(EXIT_FAILURE);
}

void    redirect_io(t_par *current, int i, int **pipes, int num_pipes)
{
    int fd;

    if (i == 0 && current->infile)
    {
        fd = open(current->infile[0], O_RDONLY);
        if (fd == -1)
            perror_exit("open infile");
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    else if (i > 0)
        dup2(pipes[i - 1][READ_END], STDIN_FILENO);
    if (i == num_pipes && current->outfile)
    {
        fd = open(current->outfile[0], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
        if (fd == -1)
            perror_exit("open outfile");
        dup2(fd, STDOUT_FILENO);
        close(fd);
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

