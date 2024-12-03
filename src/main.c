# include "../include/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *command_buff;

	while (1)
	{
		command_buff = readline("minishell> ");
		if (ft_strlen(command_buff) > 0)
			add_history(command_buff);
		if (!strcmp(command_buff, "exit"))
		{
			rl_clear_history();
			free(command_buff);
			break;
		}
		free(command_buff);
	}
}
