/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:05 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/21 19:15:10 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//(TEST) Prints the contents of the token list received by parameter
void	print_tokens(t_data *data)
{
	t_token	*current_token;

	printf("-------- PRINT TOKENS --------\n");
	current_token = data->tokens;
	while (current_token)
	{
		printf("%s - Type:%d\n", current_token->str, current_token->type);
		current_token = current_token->next;
	}
	printf("--------- END TOKENS ---------\n\n");
}

//(TEST) Receives a char** as a parameter and prints its content by console
void	print_split(char **splitted)
{
	int	i;

	i = 0;
	if (splitted)
	{
		while (splitted[i])
		{
			ft_printf("[%d]: %s\n", i, splitted[i]);
			i++;
		}
	}
}

//(TEST) Prints the content of each node of a list of type t_section
void	print_sections(t_section *section)
{
	t_files	*curr_file;

	if (!section)
		return ;
	printf("######### SECTION %d #########\nCMD: \n", section->id);
	print_split(section->cmd);
	printf("FILES: \n");
	curr_file = section->files;
	while (curr_file)
	{
		printf("%s type: %d\n", curr_file->file_name, curr_file->file_type);
		curr_file = curr_file->next;
	}
	if (section->outer)
		printf("outer section: %d - conn_type: %d\n",
			section->outer->id, section->out_conn);
	if (section->inner)
		printf("inner section: %d - conn_type: %d\n",
			section->inner->id, section->in_conn);
	if (section->next)
		printf("next section: %d - conn_type: %d\n",
			section->next->id, section->next_conn);
	print_sections(section->inner);
	print_sections(section->next);
}

//(TEST) Prints the content of a pipe
void	print_pipe(int fd)
{
	int		bytes_read;
	char	buffer[1024];

	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read >= 0)
	{
		buffer[bytes_read] = '\0';
		write(STDOUT_FILENO, buffer, bytes_read);
	}
}
