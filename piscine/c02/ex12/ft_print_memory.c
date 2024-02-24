/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:28:48 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/25 18:15:49 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	transform_char_to_hexa(char c, int i);
void	print_address(const void *p);
void	print_spaces(unsigned int i, char *pchar);

void	write_string(char *pchar)
{
	int	i;

	i = 0;
	while (i++ < 16)
	{
		if (*pchar < 32 || *pchar >= 127)
			write(1, ".", 1);
		else
			write(1, pchar, 1);
		pchar++;
	}
}

void	*ft_print_memory(void	*addr, unsigned int size)
{
	unsigned int	i;
	char			*pchar;

	i = 0;
	pchar = addr;
	if (size == 0)
		return (addr);
	print_address(pchar);
	while (*pchar != '\0' && size-- != 0)
	{
		transform_char_to_hexa(*pchar++, ++i);
		if (i % 16 == 0)
		{
			pchar -= 16;
			write_string(pchar);
			pchar += 16;
			i = 0;
			write(1, "\n", 1);
			print_address(pchar);
		}
	}
	print_spaces(i, pchar);
	return (addr);
}

void	print_spaces(unsigned int i, char *pchar)
{
	int	spaces_to_print;	

	write(1, "00", 2);
	spaces_to_print = (16 - i) * 2 + (16 - i) / 2 - 2;
	if (i % 2 == 0)
		spaces_to_print--;
	while (spaces_to_print >= 0)
	{
		write(1, " ", 1);
		spaces_to_print--;
	}
	pchar -= i;
	while (*pchar != '\0' && i-- != 0)
	{
		if (*pchar < 32)
			write(1, ".", 1);
		else
			write(1, pchar, 1);
		pchar++;
	}
	write(1, ".\n", 2);
}

void	print_address(const void *p)
{
	static char			*table;
	unsigned long		value;
	char				buffer[sizeof(void*) * 2];
	unsigned int		idx;
	int					digit;

	idx = 0;
	table = &"0123456789abcdef"[0];
	value = (unsigned long)p;
	while (value)
	{
		digit = value % 16;
		buffer[idx] = table[digit];
		idx++;
		value /= 16;
	}
	while (idx < sizeof(buffer))
		buffer[idx++] = '0';
	idx = sizeof(buffer) - 1;
	while (idx > 0)
		write(1, buffer + idx--, 1);
	write(1, buffer + 0, 1);
	write(1, ": ", 2);
}

void	transform_char_to_hexa(char c, int i)
{
	char	first_hexa;
	char	second_hexa;

	first_hexa = (c / 16) + '0';
	second_hexa = (c % 16);
	if (second_hexa > 9)
		second_hexa += 87;
	else
		second_hexa += '0';
	write(1, &first_hexa, 1);
	write(1, &second_hexa, 1);
	c++;
	if (i % 2 == 0)
		write(1, " ", 1);
}
