#include "main.h"

/**
 * btoa - convert an unsigned int to binary string
 * @valist: list with next argument
 * @buffer: character buffer for printing
 * @pos: position in the buffer
 * @n_printed: number of printable characters
 * @spec: specifier flags
 *
 * Return: Always 0
 */
int btoa(va_list valist, char *buffer, int *pos, int *n_printed, char *spec)
{
	int i;
	unsigned int b = va_arg(valist, unsigned int);
	char s[33];

	(void) spec;

	if (!b)
	{
		string_to_buffer("0", buffer, pos, n_printed);
		return (0);
	}

	for (i = 0; i < 33; i++)
		s[i] = '\0';
	i = 0;
	while (b > 0)
	{
		s[i] = (b % 2) + '0';
		b /= 2;
		i++;
	}

	rev_string(s);
	s[i] = '\0';

	string_to_buffer(s, buffer, pos, n_printed);
	return (0);
}
