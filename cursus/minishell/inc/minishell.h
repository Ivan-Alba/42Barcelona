/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:34:21 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/20 18:55:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

enum token_type {
    WORD,		// 0
    PIPE,		// 1
    ENV_VAR,	// 2
    LESS,		// 3
   	GREAT,		// 4
   	LESSLESS,	// 5
    GREATGREAT,	// 6
	AND,		// 7
	OR			// 8
};

typedef struct s_token
{
	enum token_type	type;
	char			*str;
	void			*next;
} t_token;

typedef struct s_data
{
	char	**env;
	char	*prompt;
	char	**splitted_prompt;
	t_token	*tokens;
} t_data;


void	print_error_exit(char *msg, t_data *data);
void	free_split(char **splitted);
void	ft_token_split(char *str, char *separators, t_data *data);

#endif
