/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:31:40 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/02 16:38:50 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	t_section	*curr_sec;

	if (section->fd_in != -1)
		dup2(section->fd_in, STDIN_FILENO);
	else if (section->outer && section->out_conn == PIPE)
	{
		curr_sec = section->outer;
		while (curr_sec->outer)
			curr_sec = curr_sec->outer;
		dup_pipe(curr_sec, 0, data);
	}
	else if (section->previous && section->previous->next_conn == PIPE)
	{
		dup2(data->pipes[(section->id - 1) * 2], STDIN_FILENO);
		close(data->pipes[(section->id - 1) * 2]);
	}
}

void	set_stdout(t_section *section, t_data *data)
{
	t_section	*curr_sec;

	if (section->fd_out != -1)
		dup2(section->fd_out, STDOUT_FILENO);
	else if (section->outer && !section->next
		&& section->id != data->section_id - 1)
	{
		curr_sec = section->outer;
		while (curr_sec->outer && !curr_sec->next && curr_sec->fd_out == -1)
			curr_sec = curr_sec->outer;
		if (curr_sec->fd_out != -1)
			dup2(curr_sec->fd_out, STDOUT_FILENO);
		else
			dup_pipe(curr_sec, 1, data);
	}
	else if (get_next_section(section, data->section_id - 1)
		&& get_next_section(section, data->section_id - 1)->previous->next_conn
		== PIPE)
	{
		curr_sec = get_next_section(section, data->section_id - 1);
		dup2(data->pipes[((curr_sec->id -1) * 2) + 1], STDOUT_FILENO);
		close(data->pipes[((curr_sec->id -1) * 2) + 1]);
	}
}

void	set_stdin_stdout(t_section *section, t_data *data)
{
	set_stdin(section, data);
	set_stdout(section, data);
	close_section_fds(section);
}
