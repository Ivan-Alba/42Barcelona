/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:59:14 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/05 21:59:39 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

unsigned int	ft_atoi(char *str);
int				check_max_num(char *str);
int				es_entero(char *str);
int				cifras(unsigned int n);
int				bilions(unsigned int numero,
					unsigned int base, int i, char *output);
int				milions(unsigned int numero,
					unsigned int base, int i, char *output);
int				kilos(unsigned int numero, unsigned int base,
					int i, char *output);
int				centenas(unsigned int numero, unsigned int base,
					int i, char *output);
void			search_dict(char *dict_file, char *nbrs);

void	check_group(int n_cifras, unsigned int numero, int base, char *output)
{
	int		i;

	i = n_cifras;
	if (i > 0 && i < 11)
	{
		if (numero == 0)
		{
			output[0] = '0';
			output[1] = ' ';
			output[2] = '\0';
		}
		else
		{
			output[0] = '\0';
			if (base >= 1000000000)
				i = bilions(numero, base, i, output);
			else if (base >= 1000000)
				i = milions(numero, base, i, output);
			else if (base >= 1000)
				i = kilos(numero, base, i, output);
			else if (numero < 1000)
				i = centenas(numero, base, i, output);
			i--;
		}
	}
}

//Funcion que consigue el numero base a partir del numero de sepadores
int	numero_base(unsigned int n)
{
	unsigned int	base;

	base = 1;
	while (n - 1 > 0)
	{
		base *= 10;
		n--;
	}
	return (base);
}

//Funcio que trata los argumentos pasados
void	checker(char *n, char *dict)
{
	unsigned int	numero;
	int				n_cifras;
	int				base;
	char			output[150];

	if (es_entero(n) == 0 && check_max_num(n) == 0)
	{
		numero = ft_atoi(n);
		n_cifras = cifras(numero);
		base = numero_base(n_cifras);
		check_group(n_cifras, numero, base, output);
		search_dict(dict, output);
	}
	else
		write (1, "Error\n", 6);
}

int	main(int ac, char **argv)
{
	if (ac == 2)
		checker(argv[1], "numbers.dict");
	else if (ac == 3)
		checker(argv[2], argv[1]);
	return (0);
}
