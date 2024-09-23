/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:34:21 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/23 13:37:24 by igarcia2         ###   ########.fr       */
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
# include <dirent.h>
# include <signal.h>

# define MALLOC_ERROR "Error allocating memory"
# define INVALID_VAR_NAME "Error: Invalid variable name"
# define BRACKET_FORMAT_ERROR "Error: Brackets not closed correctly"
# define INVALID_CHARS_ERROR "Error: There are characters not accepted (; \\)"
# define QUOTE_FORMAT_ERROR	"Error: Incorrect quoting mark format"
# define NO_ARGS_REQUIRED "Error: No args required"
# define UNEXPECTED_TOKEN "Syntax error near unexpected token "
# define PIPES_ERROR "Error creating pipes"
# define OPEN_ERROR "Error opening file"
# define CLOSE_ERROR "Error closing file"
# define DUP_ERROR "Error creating fd copy using dup2"
# define FORK_ERROR "Error creating process with fork"
# define MAX_HEREDOCS_ERROR "maximum here-document count exceeded"
# define HEREDOC_EOF_1 "warning: here-document at line "
# define HEREDOC_EOF_2 " delimited by end-of-file (wanted '"
# define HEREDOC_EOF_3 "')"
# define AMBIGUOUS_ERROR "ambiguous redirect"

# define PROGRAM_NAME "minishell:"
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

extern int	g_signal_received;

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
	int					hrdc_expand;
	int					ambiguous_redirect;
	char				*name_before_exp;
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
	char				**env;
	char				**path;
	int					*pids;
	char				*prompt;
	char				*prompt_init;
	t_split				*split_info;
	t_token				*tokens;
	int					section_id;
	t_section			*sections;
	int					*pipes;
	int					heredoc_eof_line;
	int					std_in;
	int					std_out;
	int					is_child;
	int					accept_inner;
	int					wait_process;
	int					last_exit_status;
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
void		add_new_token(t_data *data, char *str, enum e_token_type type);

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
t_section	*get_outer_fdin_section(t_section *current);
t_section	*get_outer_fdout_section(t_section *current);

//execute_controller
void		execute_controller(t_data *data);

//process_run
int			create_process(t_section **section, t_data *data, int is_subshell);
void		wait_for_process_ending(t_section *last_section, t_data *data);

//process_dup
void		set_stdin_stdout(t_section *section, t_data *data);

//heredocs
int			manage_heredocs(t_data *data);

//expand_section
void		expand_section(t_section *section, t_data *data);
char		*expand_env_vars(char *str, int is_heredoc, t_data *data);
char		*get_var_value(char **var_name, t_data *data, int is_quotes);
char		*expand_var(char *str, char **str_exp, int *i, t_data *data);

//expand_types
void		no_quote_exp(char *str, char **str_exp, int *i, t_data *data);
void		double_quote_exp(char *str, char **str_exp, int *i, t_data *data);
void		single_quote_exp(char *str, char **str_exp, int *i, t_data *data);

//expand_utils
void		word_splitting(char ***cmd, int *idx, t_data *data);
void		files_expansion(t_files *curr_file, t_data *data);
char		*mark_quotes(char *exp_value, t_data *data);

//manage_fds
int			open_fds(t_section *section);
void		close_section_fds(t_section *section);

//path
void		get_path(t_data *data);
char		*get_cmd_path(char *cmd, t_data *data);

//wildcard
void		manage_wildcard(t_section *section, t_data *data);

//wildcard_utils
int			file_match(char *filename, char *pattern, int *i, int *j);
int			can_expand_wildcar(char *cmd);
void		remove_quotes(char **str, t_data *data);
void		add_to_cmd(char ***cmd, int *i, char ***matches, t_data *data);

//free_data
void		clean_prompt_data(t_data *data);
void		free_data(t_data *data);
void		free_sections(t_section **sections);
void		free_close_pipes(t_data *data);
void		remove_heredoc_files(t_section *section, int last_section_id);

//print_error.c
void		print_error_exit(char *msg, t_data *data);
void		print_error(char *msg, char *token);
void		print_perror(char *msg);
void		print_ambiguous_error(char *str);

//str_utils

char		*str_from_char(char c);
char		**add_to_array(char ***current, char *new_value);
char		*concat_char_to_str(char *str, char c, t_data *data);
char		**str_array_dup(char **origin);
void		free_split(char ***splitted);

//utils
void		malloc_protection(void *ptr, t_data *data);
void		free_if_exists(void *ptr);

//test_utils
void		print_tokens(t_data *data);
void		print_split(char **splitted);
void		print_sections(t_section *section);
void		print_pipe(int fd);

//files_lst_utils
void		ft_files_lstclear(t_files **lst);
void		ft_files_add(t_files **lst, t_files *new);
t_files		*ft_files_new(char *file_name, enum e_token_type type);

//signals
void		setup_signal_handler(void (*handler)(int));
void		handle_signal(int signal);
void		handle_signal_prompt(int signal);

//check_builtins
int			is_builtin(char *command);
void		builtin_setup(t_section *section, char **cmd, t_data *data);
//builtins
int			ft_echo(char **cmd);
int			ft_env(char **cmd, t_data *data);
int			ft_pwd(char **cmd, t_data *data);
int			ft_unset(char **cmd, t_data *data);
int			ft_export(char **cmd, t_data *data);
int			ft_cd(char **cmd, t_data *data);
int			ft_exit(char **cmd, t_data *data);
//cd_utils
void		change_dir_my_env(char *old_pwd, char *pwd, t_data *data);
void		set_oldpwd(t_data *data);
int			swap_dir(char **cmd, t_data *data);
int			expand_cd(char *cmd, t_data *data);
char		*my_getenv(char *env, t_data *data);
//export_utils
void		dup_sort_list(char **list_vars, t_data *data, int *num_vars);
void		export_var(t_data *data, char *new_var, int var_in_env,
				int operator_type);
int			valid_varname(char *str);
int			print_export_vars(t_data *data);
int			check_if_exist(char *var, t_data *data);
//export_join_utils
void		prepare_join(t_data *data, char *join_var, int var_in_env);
void		remove_plus(char *str);
//unset_utils
int			is_flag(char *str);
void		remove_var(char **env, int *num_env);
//print_error_builtins
int			print_error_not_set(void);
int			print_error_many_args_exit(int *exit_code);
int			print_error_num_arg(int *exit_code, char *cmd);
int			print_error_no_file(char *cmd);
int			print_error_many_args_exit(int *exit_code);
int			print_error_many_args(void);
int			print_error_oldpwd(void);
int			print_error_permission(char *dir_name);

#endif
