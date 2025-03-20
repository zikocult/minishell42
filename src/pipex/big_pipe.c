/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamanzan <pamanzan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:07:54 by pamanzan          #+#    #+#             */
/*   Updated: 2024/10/31 12:59:52 by pamanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
	
int main(int argc, char **argv, char **env) {
    if (argc < 5) { // Verificar que hay al menos dos comandos y dos archivos (entrada y salida)
        fprintf(stderr, "Uso: %s archivo_in comando1 comando2 ... comandoN archivo_out\n", argv[0]);
        return (1);
    }

    int pipes[argc - 4][2]; // Necesitas (argc - 4) pipes para (argc - 3) comandos
    int pid;
    int status;
    char **result;
    char *find;
    char *path;

    find = enviroment(env);

    // Crear los pipes
    int i = 0;
    while (i < argc - 4) {
        if (pipe(pipes[i]) == -1) { // Verificar error en la creación del pipe
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Crear procesos hijos para cada comando
    i = 2; // Empezar desde el primer comando
    while (i < argc - 1) {
        pid = fork();
        if (pid == -1) { // Verificar error en fork
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Proceso hijo
            if (i == 2) { // Primer comando: redireccionar stdin desde el archivo de entrada
                int fd_in = open(argv[1], O_RDONLY);
                if (fd_in == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
                dup2(pipes[i - 2][1], STDOUT_FILENO);
            } else if (i == argc - 2) { // Último comando: redireccionar stdout al archivo de salida
                int fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_out == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(pipes[i - 3][0], STDIN_FILENO);
                close(pipes[i - 3][0]);
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            } else { // Comandos intermedios: redireccionar stdin y stdout a los pipes apropiados
                dup2(pipes[i - 3][0], STDIN_FILENO);
                close(pipes[i - 3][0]);
                dup2(pipes[i - 2][1], STDOUT_FILENO);
                close(pipes[i - 2][1]);
            }

            // Cerrar todos los pipes en los procesos hijos
            int j = 0;
            while (j < argc - 4) {
                close(pipes[j][0]);
                close(pipes[j][1]);
                j++;
            }

            result = ft_split(argv[i], 32);
            path = find_path(find, result[0]);
            execve(path, result, env);
            perror("execve"); // En caso de error en execve
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Cerrar todos los pipes en el proceso padre
    i = 0;
    while (i < argc - 4) {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }

    // Esperar a que terminen todos los procesos hijos
    i = 0;
    while (i < argc - 3) {
        wait(&status);
        i++;
    }

    free(find);
    return (0);
}    
