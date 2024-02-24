/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_check_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:27:53 by rcortes-          #+#    #+#             */
/*   Updated: 2023/10/29 20:38:13 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_size_string(char *string)
{
	int	i;
	int	argcounter;

	i = 0;
	argcounter = 0;
	while (string[i] != '\0')
	{
		if (string[i] >= '0' && string[i] <= '9')
			argcounter++;
		i++;
	}
	return (argcounter);
}

void	store_values(char *arguv[], int size, char elmapa[11][11])
{
	int	i;

	i = 0;
	while (i < size * 4)
	{
		if (i < size)
			elmapa[i + 1][0] = arguv[1][i * 2] - '0';
		else if (i < (size * 2))
			elmapa[i % size + 1][size + 1] = arguv[1][i * 2] - '0';
		else if (i < (size * 3))
			elmapa[0][i % size + 1] = arguv[1][i * 2] - '0';
		else if (i < (size * 4))
			elmapa[size + 1][i % size + 1] = arguv[1][i * 2] - '0';
		i++;
	}
}

int	num_limit(char *arguv[], int size)
{
	int	i;
	int	one_count;
	int	size_count;
	int	num;

	i = 0;
	while (i < size * 4)
	{
		num = arguv[1][i * 2] - '0';
		if (i % size == 0)
		{
			size_count = 0;
			one_count = 0;
		}
		if (num < 1 || num > size)
			return (0);
		if (num == 1)
			one_count++;
		if (num == size)
			size_count++;
		if (size_count > 1 || one_count > 1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_args(int argc, char *argv[], char elmapa[11][11])
{
	int	size;
	int	count;

	count = 0;
	if (argc != 2)
		return (0);
	size = ft_size_string(argv[1]) / 4;
	if (ft_size_string(argv[1]) % 4 != 0)
		return (0);
	if (size < 4 || size > 9)
		return (0);
	while (argv[1][count] != '\0')
	{
		if (count % 2 == 0 && !(argv[1][count] >= '1'
			&& argv[1][count] <= size + '0'))
			return (0);
		if (count % 2 == 1 && !(argv[1][count] == ' '))
			return (0);
		count++;
	}
	if (num_limit(argv, size) == 0)
		return (0);
	store_values(argv, size, elmapa);
	return (size);
}
