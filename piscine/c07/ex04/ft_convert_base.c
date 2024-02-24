/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:35:41 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/09 17:41:45 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_putnbr_base(int nbr, char *base);
int		check_base(char *base);

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	check_value(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

int	check_error(char *base, int len)
{
	int	i;
	int	j;

	i = 0;
	if (len < 2)
		return (0);
	while (i < len)
	{
		j = i + 1;
		if (base[i] == '-' || base[i] == '+' || base[i] == ' '
			|| (base[i] >= 9 && base[i] <= 13))
			return (0);
		while (j < len)
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	base_len;
	int	check;
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	base_len = ft_strlen(base);
	check = check_error(base, base_len);
	if (check != 0 && *str != '\0')
	{
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		while (*str == '-' || *str == '+')
		{
			if (*str == '-')
				sign *= -1;
			str++;
		}
		while (check_value(*str, base) < base_len)
			result = result * base_len + check_value(*str++, base);
	}
	if (sign == -1)
		return (-result);
	return (result);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		nbr_decimal;

	if (!check_base(base_from) || !check_base(base_to))
		return (0);
	nbr_decimal = ft_atoi_base(nbr, base_from);
	return (ft_putnbr_base(nbr_decimal, base_to));
}
