/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:34:21 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/23 17:44:01 by igarcia2         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>

# define MALLOC_ERROR "Error allocating memory"
# define INVALID_VAR_NAME "Error: Invalid variable name"
# define BRACKET_FORMAT_ERROR "Error: Brackets not closed correctly"
# define INVALID_CHARS_ERROR "Error: There are characters not accepted (; \\)"
# define QUOTE_FORMAT_ERROR	"Error: Incorrect quoting mark format"
# define NO_ARGS_REQUIRED "Error: No args required"
# define UNEXPECTED_TOKEN "Syntax error near unexpected token"
# define PIPES_ERROR "Error creating pipes"
# define OPEN_ERROR "Error opening file"
# define CLOSE_ERROR "Error closing file"
# define DUP_ERROR "Error creating fd copy using dup2"
# define FORK_ERROR "Error creating process with fork"

enum	e_token_type
{
	IN_F,
	OUT_F,
	OUT_AP_F,
	HEREDOC,
	WORD,
	SPC,
	PIPE,
	ENV_VAR,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	AND,
	OR,
	AMPER,
	FORB
};

typedef struct s_files
{
	char				*file_name;
	enum e_token_type	file_type;
	int					fd;
	char				*hrdc_file_name;
	struct s_files		*next;
}	t_files;

typedef struct s_section
{
	int					id;
	char				**cmd;
	char				*cmd_path;
	struct s_section	*next;
	enum e_token_type	next_conn;
	struct s_section	*previous;
	struct s_section	*inner;
	enum e_token_type	in_conn;
	struct s_section	*outer;
	enum e_token_type	out_conn;
	int					fd_in;
	int					fd_out;
	t_files				*files;
}	t_section;

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
	char			**env;
	char			**path;
	int				*pids;
	char			*prompt;
	char			*prompt_init;
	t_split			*split_info;
	t_token			*tokens;
	int				section_id;
	t_section		*sections;
	int				*pipes;
	int				heredoc_file_n;
	char			**expand_vars;
	int				std_in;
	int				std_out;
	int				is_child;
	int				last_exit_status;
}	t_data;

//check_syntax
int			check_syntax(t_data *data);
//ft_token_split
void		ft_token_split(char *separators, t_data *data);
//tokenizer
int			tokenizer(t_data *data);
//token_types
void		token_great_less(t_data *data, int *i);
void		token_pipe_or(t_data *data, int *i);
void		token_amper_and(t_data *data, int *i);
void		token_quotes(t_data *data, int *i);
void		token_brackets(t_data *data, int *i);
//check_tokens_syntax
int			check_and_or(t_token *current);
int			check_open_bracket(t_token *current);
int			check_close_bracket(t_token *current);
int			check_pipe(t_token *current);
int			check_first_last_token(t_token *token, int is_first);
//token_lst_utils
void		ft_token_lstclear(t_token **lst);
void		add_new_token(t_data *data, char *str, enum e_token_type type,
				int expand);
//sectionizer
void		sectionizer(t_data *data);
t_section	*new_section(t_section *outer, t_section *previous, t_data *data);
char		**create_command(t_token **first, t_data *data);
//section_token		
void		brack_sect(t_section **curr_sec, t_token **curr_tok, t_data *data);
void		files_sect(t_section **curr_sec, t_token **curr_tok, t_data *data);
void		word_sect(t_section **curr_sec, t_token **curr_tok, t_data *data);
void		conn_sect(t_section **curr_sec, t_token **curr_tok, t_data *data);
//navigate_sections
t_section	*get_next_section(t_section *current, int last_section_id);
t_section	*get_next_pipe_section(t_section *current);
//executor
void		executor(t_data *data);
//heredocs
void		manage_heredocs(t_data *data);
void		remove_heredoc_files(t_section **section);
t_section	*get_next_section(t_section *current, int last_section_id);
//expand_section
void		expand_section(t_section *section, t_data *data);
//manage_fds
int			open_fds(t_section *section);
void		close_section_fds(t_section *section);
//path
void		get_path(t_data *data);
char		*get_cmd_path(char *cmd, t_data *data);
//expand_utils
void		concat_var_value(char **current_str, char *var, t_data *data);
char		*get_var_value(char *var_name, t_data *data);
char		*expand_marks(char *str);
//free_utils
void		clean_prompt_data(t_data *data);
void		free_split(char ***splitted);
void		free_data(t_data *data);
void		free_sections(t_section **sections);
void		free_close_pipes(t_data *data);
//utils
void		print_error_exit(char *msg, t_data *data);
void		print_error(char *msg, char *token);
char		*string_from_char(char c);
char		**add_to_array(char ***current, char *new_value);
//test_utils
void		print_tokens(t_data *data);
void		print_split(char **splitted);
void		print_sections(t_section *section);
void		print_pipe(int fd);
//files_lst_utils
void		ft_files_lstclear(t_files **lst);
void		ft_files_add(t_files **lst, t_files *new);
t_files		*ft_files_new(char *file_name, enum e_token_type type);

#endif
