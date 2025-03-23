/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:09:11 by pamanzan          #+#    #+#             */
/*   Updated: 2025/03/23 13:34:45 by patri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (i > 0)
			{
				close(pipes[--i][0]);
				close(pipes[i][1]);
			}
			free_pipes(pipes, num_pipes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void execute_command(t_parse *state, t_env *data, int **pipes)
{
	t_par   *current;
	int     i;
	pid_t   pid;
	int     status;

	current = state->head;
	i = 0;
	while (current)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) 
			exec_child(i, state, pipes, data);
		current = current->next;
		i++;
	}
	close_pipes(pipes, i - 1);
	while (i > 0)
	{
		wait(&status);
		i--;
	}
}

static char **get_envp(t_env *data)
{
    int count = 0;
    t_var *current = data->head;

    // Contar cuántas variables de entorno hay
    while (current)
    {
        count++;
        current = current->next;
    }

    // Asignar memoria para el array de strings
    char **envp = (char **)malloc((count + 1) * sizeof(char *));
    if (!envp)
        return NULL;

    // Rellenar el array con "NOMBRE=VALOR"
    current = data->head;
    int i = 0;
    while (current)
    {
        int len = ft_strlen(current->var_name) + ft_strlen(current->content) + 2;
        envp[i] = (char *)malloc(len * sizeof(char));
        if (!envp[i])
        {
            while (i > 0)
                free(envp[--i]);
            free(envp);
            return NULL;
        }
        ft_strlcpy(envp[i], current->var_name, len);
        ft_strlcat(envp[i], "=", len);
        ft_strlcat(envp[i], current->content, len);
        current = current->next;
        i++;
    }
    envp[i] = NULL; // Terminar con NULL

    return envp;
}

void exec_child(int i, t_parse *state, int **pipes, t_env *data)
{
    t_par *current = state->head;
    int j = 0;
    int num_pipes = 0;

    // Contar cuántos pipes hay
    t_par *temp = state->head;
    while (temp && temp->next)
    {
        num_pipes++;
        temp = temp->next;
    }
    // Avanzar hasta el comando correspondiente
    while (j < i && current)
    {
        current = current->next;
        j++;
    }
    if (!current || !current->command)
        exit(EXIT_FAILURE); // Seguridad en caso de error
    // Redirección de entrada y salida
    if (i > 0) 
        dup2(pipes[i - 1][0], STDIN_FILENO);
    if (i < num_pipes)
        dup2(pipes[i][1], STDOUT_FILENO);

    // Cerrar todos los pipes en el hijo
/*    for (j = 0; j < num_pipes; j++)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }*/
	close_pipes(pipes, num_pipes);

    // Convertir parameter a char ** si es necesario
    char *argv[3]; 
    argv[0] = current->command;
    argv[1] = current->parameter;
    argv[2] = NULL;

    // Obtener el path del comando
    char *path = check_path(current, data);
    if (!path)
    {
        fprintf(stderr, "Command not found: %s\n", current->command);
        exit(EXIT_FAILURE);
    }

    // Obtener variables de entorno
    char **envp = get_envp(data);

    // Ejecutar el comando
    execve(path, argv, envp);

    // Si execve falla
    perror("execve");
    exit(EXIT_FAILURE);
}

void	wait_for_children(int argc)
{
	int	i;
	int	status;

	i = 0;
	while (i < argc - 3)
	{
		wait(&status);
		i++;
	}
}
