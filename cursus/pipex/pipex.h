/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:39:16 by igarcia2          #+#    #+#             */
/*   Updated: 2024/05/14 18:47:49 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stddef.h>

typedef struct s_cmd
{
	char	**cmd_flags;
	char	*path;
	int		first;
	int		last;
}		t_cmd;

typedef struct s_pipex
{
	char	*in_file;
	char	*out_file;
	char	**env;
	char	**path;
	char	*limiter;
	int		is_heredoc;
	int		cmd_num;
	int		*pipes;
	t_cmd	*cmds;
}		t_pipex;

void	init_data(t_pipex *data, int argc, char **argv, char **env);
void	init_data_heredoc(t_pipex *data, int argc, char **argv, char **env);
void	free_data(t_pipex *data, char *error);
void	error_exit(char *error);
void	free_close_pipes(t_pipex *data);
void	read_heredoc(t_pipex *data);

#endif
