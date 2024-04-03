/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:39:19 by igarcia2          #+#    #+#             */
/*   Updated: 2024/03/22 20:37:16 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Reads map in .txt format and separates it by lines with split
char	**read_map(char	*file)
{
	int		fd;
	char	*content;
	char	*all_content;
	char	**res;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error(FILE_ERROR);
	content = get_next_line(fd);
	all_content = NULL;
	if (!content)
		exit_error(MAP_ERROR);
	while (content)
	{
		all_content = ft_strcat(&all_content, content, ft_strlen(content));
		free(content);
		content = get_next_line(fd);
	}
	res = ft_split(all_content, '\n');
	if (!res)
		exit_error("Split error\n");
	return (res);
}
