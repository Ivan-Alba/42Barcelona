/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:05 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/19 15:19:07 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//(TEST) Prints the contents of the token list received by parameter
void	print_tokens(t_data *data)
{
	t_token	*current_token;

	printf("--------PRINT TOKENS--------\n");
	current_token = data->tokens;
	while (current_token)
	{
		printf("%s - Type:%d\n", current_token->str, current_token->type);
		current_token = current_token->next;
	}
	printf("--------END TOKENS---------\n");
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
	if (!section)
		return ;
	printf("-------SECTION %d--------\nCMD: \n", section->id);
	print_split(section->cmd);
	printf("infiles:\n");
	print_split(section->files[IN_F]);
	printf("outfiles:\n");
	print_split(section->files[OUT_F]);
	printf("outfiles_app:\n");
	print_split(section->files[OUT_AP_F]);
	printf("heredocs:\n");
	print_split(section->files[HEREDOC]);
	if (section->outer)
		printf("outer section: %d - conn_type: %d\n",
			section->outer->id, section->outer_conn_type);
	if (section->inner)
		printf("inner section: %d - conn_type: %d\n",
			section->inner->id, section->inner_conn_type);
	if (section->next)
		printf("next section: %d - conn_type: %d\n",
			section->next->id, section->next_conn_type);
	print_sections(section->inner);
	print_sections(section->next);
}
