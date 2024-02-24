/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbusquet <gbusquet@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:02:11 by gbusquet          #+#    #+#             */
/*   Updated: 2023/11/05 22:24:59 by gbusquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		cifras(unsigned int n);
char	*ft_putnbr(int nb);
int		print_centenas(char *output, unsigned int base, unsigned int n, int i);

void	malloc_write(char *output, int number)
{
	int		i;
	char	*nc;
	int		j;

	i = 0;
	j = 0;
	while (output[i] != '\0')
		i++;
	nc = ft_putnbr(number);
	while (nc[j] != '\0')
	{
		output[i] = nc[j];
		i++;
		j++;
	}
	output[i++] = ' ';
	output[i] = '\0';
}

int	centenas(unsigned int numero, unsigned int base, int i, char *output)
{
	unsigned int	cifra;

	if (numero < 20 && numero != 0 && base < 1000)
	{
		malloc_write(output, numero);
		i--;
	}
	else if (((numero > 0 && numero <= 99)
			|| (numero % 10 == 0 && numero <= 99)) && numero != 0)
	{
		cifra = numero / base;
		cifra = cifra * base;
		malloc_write(output, cifra);
		numero = numero % base;
		if (!(numero % 10 == 0 && numero <= 99))
			centenas(numero, base, i, output);
	}
	else
		i = print_centenas(output, base, numero, i);
	return (i);
}

int	kilos(unsigned int numero, unsigned int base, int i, char *output)
{
	if (i <= 6 && i > 3 && numero >= 1000)
	{
		i -= 3;
		centenas(numero / 1000, base / 1000, i, output);
		malloc_write(output, 1000);
	}
	base = 100;
	if (numero % 1000 < 100)
		base /= 10;
	centenas(numero % 1000, base, i, output);
	return (i);
}

int	milions(unsigned int numero, unsigned int base, int i, char *output)
{
	if (i <= 9 && i > 6 && numero >= 1000000)
	{
		i -= 3;
		centenas(numero / 1000000, base / 1000000, i, output);
		malloc_write(output, 1000000);
	}
	base = 100000;
	if (numero % 1000000 < 100000)
		base /= 10;
	kilos(numero % 1000000, base, i, output);
	return (i);
}

int	bilions(unsigned int numero, unsigned int base, int i, char *output)
{
	if (i <= 12 && i > 9)
	{
		i -= 1;
		centenas(numero / 1000000000, base / 1000000000, i, output);
		malloc_write(output, 1000000000);
	}
	base = 100000000;
	if (numero % 1000000000 < 100000000)
		base /= 10;
	milions(numero % 1000000000, base, i, output);
	return (i);
}
