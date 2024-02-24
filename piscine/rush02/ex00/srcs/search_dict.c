/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_dict.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:28:13 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/05 20:34:19 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int		ft_strcomp(char *s1, char *s2);
char	*ft_strstr(char *dict, char *to_find);

//Funcion que escribe el valor en palabras del numero
void	write_value(char *line)
{
	int	i;
	int	next_space;
	int	value_reached;

	value_reached = 0;
	next_space = 0;
	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == ':' && value_reached == 0)
			value_reached = 1;
		else if (line[i] == ' ' && next_space == 1 && value_reached == 1)
		{
			write(1, " ", 1);
			next_space = 0;
		}
		else if (value_reached == 1 && !(line[i] <= 32 || line[i] >= 127))
		{
			write(1, &line[i], 1);
			next_space = 1;
		}
		i++;
	}
}

//Funcion que lee el dict file y lo guarda en un char *
void	create_dict(char *dic, char *dict_file)
{
	int		file;
	int		i;
	char	temp;

	i = 0;
	file = open(dict_file, O_RDONLY);
	if (file == -1)
	{
		write(1, "Dict Error\n", 11);
		return ;
	}
	while (read(file, &temp, 1) == 1)
	{
		if (temp != '\n' && (temp <= 31 || temp >= 127))
		{
			write(1, "Dict Error\n", 11);
			return ;
		}
		dic[i++] = temp;
	}
	dic[i] = '\0';
	close(file);
}

//Funcion que busca en la copia del dict la linea correspondiente segun el num.
void	search_number(char *dic, char *nbrs)
{
	char	*to_find;
	int		i;
	int		j;

	i = 0;
	while (nbrs[i] != '\0')
	{
		while (nbrs[i] != ' ')
			i++;
		to_find = (char *) malloc(i + 1 * sizeof(char));
		j = 0;
		while (j < i)
		{
			to_find[j] = nbrs[j];
			j++;
		}
		to_find[j] = '\0';
		write_value(ft_strstr(dic, to_find));
		free(to_find);
		nbrs += i + 1;
		if (*nbrs != '\0')
			write(1, " ", 1);
		i = 0;
	}
	free(dic);
}

//Funcion que devuelve el tamany del file dict a copiar.
int	get_dict_size(char *dict_file)
{
	int		file;
	int		size;
	char	temp;

	file = open(dict_file, O_RDONLY);
	if (file == -1)
	{
		write(1, "Dict Error\n", 11);
		return (0);
	}
	size = 0;
	while (read(file, &temp, 1) == 1)
	{
		size++;
	}
	close(file);
	return (size);
}

//Funcion que copia el dict recibido por parametro
void	search_dict(char *dict_file, char *nbrs)
{
	int		i;
	char	*dic;

	i = get_dict_size(dict_file);
	dic = (char *) malloc((i + 1) * sizeof(char));
	if (dic == NULL || i == 0)
	{
		write(1, "Dict Error\n", 11);
		return ;
	}
	create_dict(dic, dict_file);
	search_number(dic, nbrs);
	write(1, "\n", 1);
}
