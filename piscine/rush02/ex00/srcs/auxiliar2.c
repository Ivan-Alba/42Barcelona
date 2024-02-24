/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:58:35 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/05 21:59:00 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

//Funcion que convierte un char a un int
unsigned int	ft_atoi(char *str)
{
	int	i;
	int	signe;
	int	resultat;

	signe = 1;
	i = 0;
	resultat = 0;
	while (str[i] <= ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + (str[i] - 48);
		i++;
	}
	return (signe * resultat);
}

int	is_max_number(char *str, char *aux, int i, int j)
{
	unsigned int	atoi;

	while (str[i] != '\0')
		i++;
	if (i > 10)
		return (1);
	if (i == 10)
	{
		if (str[0] > '4')
			return (1);
		else if (str[0] == '4')
		{
			while (j < 9)
			{
				aux[j] = str[j + 1];
				j++;
			}
			aux[j] = '\0';
			atoi = ft_atoi(aux);
			free(aux);
			if (atoi > 294967295)
				return (1);
		}
	}
	return (0);
}

int	check_max_num(char *str)
{
	char			*aux;
	int				i;
	int				j;

	i = 0;
	j = 0;
	aux = (char *) malloc(10 * sizeof(char));
	return (is_max_number(str, aux, i, j));
}

//Funcion que nos dice si el char passado es un numero entero
int	es_entero(char *str)
{
	int	es_entero;
	int	i;

	es_entero = 0;
	i = 0;
	while (str[i] != '\0' && es_entero == 0)
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			es_entero = 1;
	}
	return (es_entero);
}

//Funcion que devuelve el numero de cifras de un numero
int	cifras(unsigned int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
