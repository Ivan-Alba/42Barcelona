/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:34:21 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/25 16:52:21 by igarcia2         ###   ########.fr       */
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

enum	e_token_type
{
	WORD,
	PIPE,
	ENV_VAR,
	LESS,
	GREAT,
	LESSLESS,
	GREATGREAT,
	AND,
	OR
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*str;
	void				*next;
}	t_token;

typedef struct s_split
{
	char	**splitted_prompt;
	int		words;
	int		len;
	int		word_idx;
}	t_split;

typedef struct s_data
{
	char	**env;
	char	*prompt;
	char	*prompt_init;
	t_split	*split_info;
	t_token	*tokens;
}	t_data;

void	print_error_exit(char *msg, t_data *data);
void	free_split(char **splitted);
void	print_split(char **splitted);
void	ft_token_split(char *separators, t_data *data);
void	free_data(t_data *data);

#endif
