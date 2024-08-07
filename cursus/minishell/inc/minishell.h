/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:34:21 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/07 16:22:11 by igarcia2         ###   ########.fr       */
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

# define MALLOC_ERROR "Error allocating memory"
# define INVALID_VAR_NAME "Error: Invalid variable name"
# define BRACKET_FORMAT_ERROR "Error: Brackets not closed correctly"
# define INVALID_CHARS_ERROR "Error: There are characters not accepted (; \\)"
# define QUOTE_FORMAT_ERROR	"Error: Incorrect quoting mark format"
# define NO_ARGS_REQUIRED "Error: No args required"
# define UNEXPECTED_TOKEN "Syntax error near unexpected token"

enum	e_token_type
{
	WORD,
	SPC,
	PIPE,
	ENV_VAR,
	IN_F,
	OUT_F,
	HEREDOC,
	OUT_AP_F,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	AND,
	OR
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*str;
	struct s_token		*next;
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
void	print_error(char *msg, char *token);
int		check_syntax(t_data *data);
void	free_split(char ***splitted);
void	print_split(char **splitted);
void	ft_token_split(char *separators, t_data *data);
void	free_data(t_data *data);
//tokenizer
int		tokenizer(t_data *data);
//token_types
void	token_great_less(t_data *data, int *i);
void	token_pipe_or_and(t_data *data, int *i);
void	token_quotes(t_data *data, int *i);
void	token_word(t_data *data, int *i);
void	token_brackets(t_data *data, int *i);
//check_tokens
int		check_tokens_format(t_data *data);
//token_lst_utils
t_token	*ft_token_last(t_token *lst);
t_token	*ft_token_new(char *str, enum e_token_type type);
void	ft_token_add(t_token **lst, t_token *new);
void	ft_token_lstclear(t_token **lst);
void	print_tokens(t_data *data);
//expand_var
int		expand_var(t_data *data);

#endif
