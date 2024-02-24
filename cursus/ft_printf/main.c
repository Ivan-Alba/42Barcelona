/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:30:54 by molasz-a          #+#    #+#             */
/*   Updated: 2024/01/24 14:33:26 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

void	ft_setcolor(int expected, int ft)
{
	if (expected == ft)
		printf("\033[0;32m");
	else
		printf("\033[0;31m");
}

void	ft_resetcolor () {
	printf("\033[0m\n");
}

void	ft_title (char *s) {
	printf("\033[0;33m\n");
	printf("%s", s);
	ft_resetcolor();
}

void	ft_output(int expected, int ft, char *s)
{
	static int	count = 0;

	ft_setcolor(expected, ft);
	printf("(%d) printf:%d ft_printf:%d | %s\n", ++count, expected, ft, s);
	ft_resetcolor();
}

void	ft_print(char *s)
{
	int		expected;
	int		ft;

	expected = printf(s);
	printf("|\n");
	ft = ft_printf(s);
	ft_printf("|\n");
	ft_output(expected, ft, s);
}

void	ft_prints(char *s, char *v)
{
	int	expected;
	int	ft;

	expected = printf(s, v);
	printf("|\n");
	ft = ft_printf(s, v);
	ft_printf("|\n");
	ft_output(expected, ft, s);
}

void	ft_printc(char *s, char c)
{
	int	expected;
	int	ft;

	expected = printf(s, c);
	printf("|\n");
	ft = ft_printf(s, c);
	ft_printf("|\n");
	ft_output(expected, ft, s);
}

void	ft_printi(char *s, long long n)
{
	int	expected;
	int	ft;

	expected = printf(s, n);
	printf("|\n");
	ft = ft_printf(s, n);
	ft_printf("|\n");
	ft_output(expected, ft, s);
}

void	ft_printp(char *s, void *p)
{
	int	expected;
	int	ft;

	expected = printf(s, p);
	printf("|\n");
	ft = ft_printf(s, p);
	ft_printf("|\n");
	ft_output(expected, ft, s);
}

int	main(void)
{
	int	num;

	num = 42;
	ft_title("   >>>   MANDATORY   <<<\n\n");
	ft_print("Hello world!");
 	ft_print("%%");
	ft_print("%%c");

	ft_printc("%c", '$');
	ft_printc("%c", 0);
	ft_printc("a%ca", 'c');

	ft_prints("%s", "Hello world");
	ft_prints("%s", "Hello\0 world");
	ft_prints("STR:%s", "hi");
	ft_prints("%s", "");
	ft_prints("%s", NULL);


	ft_printi("%i", 42);
	ft_printi("%d", -6);
	ft_printi("%d", 2147483647);
	ft_printi("%d", -2147483648);
	ft_printi("%i", 0);
	ft_printi("%u", 42);
	ft_printi("%u", -42);

	ft_printi("%x", 42);
	ft_printi("%X", -42);
	ft_printi("%x", 0);

	ft_printp("%p", &num);
	ft_printp("%p", "");
	ft_printp("%p", NULL);

	ft_title("\n\n\n   >>>   BONUS   <<<\n\n");

	ft_print("%5%");
	ft_print("%-5%");
	ft_print("%-05%");

	ft_printi("%+d", 42);
	ft_printi("%+d", -2);
	ft_printi("% d", 0);
	ft_printi("%5d", 42);
	ft_printi("%5d", 2147483647);
	ft_printi("%-5d", 24);
	ft_printi("%05d", -42);
	ft_printi("%0+5d", 42);
	ft_printi("%0-5d", 0);
	ft_printi("%+5d", 42);
	ft_printi("%0 5d", 42);
	ft_printi("% +5d", 42);
	ft_printi("%.5d", 42);
	ft_printi("%+7.5d", 42);
	ft_printi("%10.5d", 42);
	ft_printi("%10.5d", -42);
	ft_printi("%5.10d", 42);

	ft_printi("%#x", 42);
	ft_printi("%#X", -42);
	ft_printi("%#x", 0);
	ft_printi("%+#x", 42);
	ft_printi("% #x", 42);
	ft_printi("%#5x", 42);
	ft_printi("%#.15x", 42);
	ft_printi("%#20.5x", 42);

	ft_printi("%-#5x", 42);

	ft_printp("%20p", &num);
	ft_printp("%25.20p", &num);

	ft_printc("%5c", 'A');
	ft_printc("%3c", 0);

	ft_prints("%15s", NULL);
	ft_prints("%3s", "hello world");
	ft_prints("%25s", "hello world");
	ft_prints("%-25s", "hello world");
	ft_prints("%5.5s", "hello world");
	ft_prints("%15.5s", "hello world");
	ft_prints("%5.20s", "hello world");
	ft_prints("%5.10s", NULL);
	ft_prints("%5.3s", NULL);
	ft_prints("%5.5s", NULL);

	ft_title("\n\n\n   >>>   EXTRA   <<<\n\n");

	ft_printi("%08.5i", 34);
	ft_printi("%010.5i", -216);
	ft_printi("%08.5i", 0);
	ft_printi("%08.3i", 8375);
	ft_printi("%08.3i", -8473);
	ft_printi("%-8.3i", 8473);
	ft_printi("%.0i", 0);
	ft_printi("%.i", 0);
	ft_printi("%5.0i", 0);
	ft_printi("%5.i", 0);
	ft_printi("%-5.0i", 0);
	ft_printi("%-5.i", 0);
	ft_printi("%08.5d", 34);
	ft_printi("%010.5d", -216);
	ft_printi("%08.5d", 0);
	ft_printi("%08.3d", 8375);
	ft_printi("%08.3d", -8473);
	ft_printi("%.0d", 0);
	ft_printi("%.d", 0);
	ft_printi("%5.0d", 0);
	ft_printi("%5.d", 0);
	ft_printi("%-5.0d", 0);
	ft_printi("%-5.d", 0);

	ft_printp("%-11p", INT_MIN);
	ft_printp("%-12p", INT_MAX);
	ft_printp("%-13p", ULONG_MAX);
	ft_printp("%-14p", -ULONG_MAX);
	ft_printp("%-2p", 0);
	ft_printp("%-1p", 0);

	ft_prints("%.s", "-");
	ft_prints("%.1s", " - ");
	ft_prints("%.2s", "");
	ft_prints("%.3s", "4");
	ft_prints("%.4s", "");
	ft_prints("%.5s", "2 ");

	ft_printi("%.1u", 0);
	ft_printi("%.2u", 1);
	ft_printi("%.1u", 9);
	ft_printi("%.2u", 10);
	ft_printi("%.3u", 11);
	ft_printi("%.4u", 15);
	ft_printi("%.5u", 16);
	ft_printi("%.6u", 17);
	ft_printi("%.3u", 101);
	ft_printi("%.10u", LONG_MAX);
	ft_printi("%.11u", LONG_MIN);
	ft_printi("%.12u", UINT_MAX);
	ft_printi("%.13u", ULONG_MAX);
	ft_printi("%.14u", 9223372036854775807LL);

	ft_printp("%.2x", 1);
	ft_printp("%.2x", 10);
	ft_printp("%.3x", 11);
	ft_printp("%.4x", 15);
	ft_printp("%.5x", 16);
	ft_printp("%.6x", 17);
	ft_printp("%.3x", 101);
	ft_printp("%.9x", INT_MIN);
	ft_printp("%.10x", LONG_MAX);
	ft_printp("%.11x", LONG_MIN);
	ft_printp("%.12x", UINT_MAX);
	ft_printp("%.13x", ULONG_MAX);
	ft_printp("%.14x", 9223372036854775807LL);
	ft_printp("%.2X", 1);
	ft_printp("%.2X", 10);
	ft_printp("%.3X", 11);
	ft_printp("%.4X", 15);
	ft_printp("%.5X", 16);
	ft_printp("%.6X", 17);
	ft_printp("%.3X", 101);
	ft_printp("%.9X", INT_MIN);
	ft_printp("%.10X", LONG_MAX);
	ft_printp("%.11X", LONG_MIN);
	ft_printp("%.12X", UINT_MAX);
	ft_printp("%.13X", ULONG_MAX);
	ft_printp("%.14X", 9223372036854775807LL);
	ft_printi("%8.4d", 424242424);
	ft_printi("%8.4d", -424242424);
	ft_printi("%8.4u", 424242424);
	ft_printp("%1p", &num);
	ft_printp("%1p", &num);
	ft_printp("%1.x", 238);
	ft_printp("%1.X", 0xee);

	ft_printp("%1.X", 0xee);
	ft_printi("%8.52d", -33304973);
	ft_printi("%+3.2d", 415243590);
	ft_printp("%#11.2x", -1157673274);
	ft_printp("%0#40.37x", 922358336);
	return (0);
}
