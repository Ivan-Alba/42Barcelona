/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:31:40 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/03 16:33:35 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	dup_pipe(t_section *section, int is_output, t_data *data)
{
	t_section	*curr_sec;
	int			pipe_idx;

	pipe_idx = -1;
	curr_sec = section;
	if (is_output)
	{
		if (curr_sec->next_conn == PIPE && curr_sec->next->cmd)
			pipe_idx = (((curr_sec->next->id -1) * 2) + 1);
		else if (curr_sec->next_conn == PIPE)
			pipe_idx = (((curr_sec->next->id - 1) * 2) + 1);
		dup2(data->pipes[pipe_idx], STDOUT_FILENO);
		close(data->pipes[pipe_idx]);
	}
	else
	{
		pipe_idx = ((curr_sec->id - 1) * 2);
		dup2(data->pipes[pipe_idx], STDIN_FILENO);
		close(data->pipes[pipe_idx]);
	}
}

void	set_stdin(t_section *section, t_data *data)
{
	if (section->fd_in != -1)
		dup2(section->fd_in, STDIN_FILENO);
	else if (get_outer_fdin_section(section)
		&& get_outer_fdin_section(section)->fd_in != -1)
		dup2(get_outer_fdin_section(section)->fd_in, STDIN_FILENO);
	else if (get_outer_fdin_section(section)
		&& get_outer_fdin_section(section)->previous->next_conn == PIPE)
		dup_pipe(get_outer_fdin_section(section), 0, data);
	else if (section->previous && section->previous->next_conn == PIPE)
	{
		dup2(data->pipes[(section->id - 1) * 2], STDIN_FILENO);
		close(data->pipes[(section->id - 1) * 2]);
	}
}

void	set_stdout(t_section *section, t_data *data)
{
	if (section->fd_out != -1)
		dup2(section->fd_out, STDOUT_FILENO);
	else if (section->next && section->next_conn == PIPE)
		dup_pipe(section, 1, data);
	else if (get_outer_fdout_section(section)
		&& get_outer_fdout_section(section)->fd_out != -1)
		dup2(get_outer_fdout_section(section)->fd_out, STDOUT_FILENO);
	else if (get_outer_fdout_section(section)
		&& get_outer_fdout_section(section)->next_conn == PIPE)
		dup_pipe(get_outer_fdout_section(section), 1, data);
}

void	set_stdin_stdout(t_section *section, t_data *data)
{
	set_stdin(section, data);
	set_stdout(section, data);
	close_section_fds(section);
}
