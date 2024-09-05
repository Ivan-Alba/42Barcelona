/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:30:27 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/05 17:48:09 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 *	Function Name: minishell
 *
 *	Description:
 *
 *		Main function that manages the calls to the rest of the necessary
 *		functions for program execution.
 *
 *	Parameters:
 *
 *		t_data *data - The pointer to the t_data struct with all execution data. 
 */
void	minishell(t_data *data)
{
	char	*aux;

	aux = data->prompt;
	data->prompt_init = ft_strtrim(data->prompt, " ");
	free(aux);
	data->prompt = data->prompt_init;
	if (check_syntax(data))
		return ;
	ft_token_split("<>|& ();\\\'\"", data);
	if (tokenizer(data))
		return ;
	sectionizer(data);
	/*------TODO TEST PRINTS------*/
	//print_tokens(data);
	//print_sections(data->sections);
	//printf("\nOUTPUT:\n");
	/*---------------------------*/
	execute_controller(data);
}

/**
 *	Function Name: read_prompt
 *
 *	Description:
 *
 *		This function waits for the prompt input from the user, calls the
 *		functions in charge of its execution and releases the necessary data
 *		between inputs.
 *		If the function receives a NULL, the execution is ended.
 *
 *	Parameters:
 *
 *		t_data *data - The pointer to the t_data struct with all execution data. 
 */
void	read_prompt(t_data *data)
{
	while (1)
	{
		data->prompt = readline("minishell: ");
		if (data->prompt && data->prompt[0])
		{
			add_history(data->prompt);
			minishell(data);
			clean_prompt_data(data);
		}
		else if (!data->prompt)
		{
			write(2, "exit\n", 5);
			break ;
		}
		else
			free(data->prompt);
		data->heredoc_eof_line++;
	}
}

/**
 *	Function Name: init_data
 *
 *	Description:
 *
 *		This function receives a pointer to the address of the struct variable
 *		t_data and initializes it with all the necessary values.
 *		This t_data structure will be used during the whole execution.
 *
 *	Parameters:
 *
 *		t_data **data	- A pointer to the variable t_data* to initialize.
 *		char **env		- Environment variables that we will store in
 *							t_data struct.
 */
void	init_data(t_data **data, char **env)
{
	*data = malloc(sizeof(t_data));
	malloc_protection(*data, NULL);
	(*data)->env = str_array_dup(env);
	malloc_protection((*data)->env, *data);
	(*data)->path = NULL;
	(*data)->pids = NULL;
	(*data)->last_exit_status = 0;
	(*data)->tokens = NULL;
	(*data)->split_info = NULL;
	(*data)->section_id = 0;
	(*data)->sections = NULL;
	(*data)->pipes = NULL;
	(*data)->heredoc_eof_line = 1;
	(*data)->prompt_init = NULL;
	(*data)->prompt = NULL;
	(*data)->std_in = -1;
	(*data)->std_out = -1;
	(*data)->is_child = 0;
	(*data)->wait_process = 0;
	(*data)->accept_inner = 0;
	(*data)->std_in = dup(STDIN_FILENO);
	(*data)->std_out = dup(STDOUT_FILENO);
}

/**
 *	Function Name: main
 *
 *	Description:
 *
 *		The entry point of the program. This function is called when the program
 *		starts.
 *		It processes command-line arguments and environment variables passed to
 *		the program.
 *		The program will not accept arguments, only the executable name.
 *
 *	Parameters:
 *
 *		int	argc 	-	The number of command-line arguments passed to the
 *							program, including the executable name.
 *		char **argv	-	An array of strings representing the command-line
 *							arguments. The first element is the executable name.
 *		char **env	-	An array of strings representing the environment
 *							variables. Each string is of the form "KEY=VALUE".
 *
 * Return Value:
 *
 *    int - Returns an integer value to the operating system.
 *			Returns 0 if successful execution, or non-zero value if error.
 */
int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
		print_error_exit(NO_ARGS_REQUIRED, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	data = NULL;
	init_data(&data, env);
	read_prompt(data);
	free_data(data);
	exit(0);
}
