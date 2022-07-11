#include "main.h"

/**
 * get_sp - get specifier
 * @fmt: format string
 * @i: current position in fmt
 * @current_len: length of specifier
 * @spec: specifier flags
 *
 * Return: specifier
 */
char get_sp(const char *fmt, int i, int *current_len, char *spec)
{
	char sp;

	*current_len = get_specifier_length(fmt + i);
	if (*current_len > BUFFER_SIZE - 1)
		return ('\0');

	_strncpy(spec, fmt + i + 1, *current_len - 1);
	sp = validate_spec(spec);
	spec[*current_len - 2] = '\0';
	return (sp);
}

/**
 * get_sub - write substring into buffer
 * @fmt: format string containing strings and specifiers
 * @i: current position in format string
 * @current_len: length of substring
 * @buf: character buffer for printing
 * @pos: position in the buffer
 * @n_p: number of printable characters
 */
void get_sub(const char *fmt, int i, int *current_len,
	     char *buf, int *pos, int *n_p)
{
	int j;

	*current_len = get_substring_length(fmt + i);
	for (j = 0; j < *current_len; j++)
	{
		buffer_full(buf, pos, n_p);
		buf[(*pos)++] = fmt[i + j];
	}
}

/**
 * get_fmt_string - handle specifier formatting
 * @fmt: format string containing strings and specifiers
 * @_i: current position in format string
 * @vl: list with next argument
 * @current_len: length of specifier format string
 * @buf: character buffer for printing
 * @pos: position in the buffer
 * @n_p: number of printable characters
 *
 * Return: code indicating success (0 or 2), else 1
 */
int get_fmt_string(const char *fmt, int *_i, va_list vl, int *current_len,
		    char *buf, int *pos, int *n_p)
{
	char spec[BUFFER_SIZE], sp;
	int j, i = *_i;

	for (j = 0; j < BUFFER_SIZE; j++)
		spec[j] = '\0';

	j = 1;
	sp = get_sp(fmt, i, current_len, spec);
	if (!sp)
	{
		if (fmt[i + 1])
		{
			while (fmt[i + j] == ' ')
				j++;
			/* % > spaces > \0 */
			if (!fmt[i + j])
			{
				*n_p = -1;
				*_i += j;
				return (0);
			}
			else if (fmt[i + 1] == ' ')
			{
				string_to_buffer("%", buf, pos, n_p);
				if (fmt[i + j] != '%')
					string_to_buffer(" ", buf,
							 pos, n_p);
				*_i += j + (fmt[i + j] == '%');
				return (0);
			}
			string_to_buffer("%", buf, pos, n_p);
		}
		/* "%" */
		else
			*n_p = -1;
		*current_len = 1;
	}
	else if (get_type(sp)(vl, buf, pos, n_p, spec))
		return (1);
	return (2);
}
/**
 * get_el - read the specifier or string starting at position i
 * @fmt: format string containing strings and specifiers
 * @_i: current position in format string
 * @vl: list with next argument
 * @buf: character buffer for printing
 * @pos: position in the buffer
 * @n_p: number of printable characters
 *
 * Return: 0 on success, else 1
 */
int get_el(const char *fmt, int *_i, va_list vl, char *buf, int *pos, int *n_p)
{
	int current_len, i = *_i, fmt_code;

	if (fmt[i] == '%')
	{
		fmt_code = get_fmt_string(fmt, _i, vl, &current_len,
					  buf, pos, n_p);
		if (fmt_code != 2)
			return (fmt_code);
	}
	else
		get_sub(fmt, i, &current_len, buf, pos, n_p);
	*_i += current_len;
	return (0);
}

/**
 * _printf - prints a formatted string
 * @format: format string
 *
 * Return: On success the number of bytes printed.
 * On error, a negative number.
 */
int _printf(const char *format, ...)
{
	int i, pos = 0, n_printed = 0, chars_to_print, get_ok;
	char buffer[BUFFER_SIZE];
	va_list valist;

	if (!format)
		return (-1);

	for (i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = '\0';
	i = 0;

	va_start(valist, format);
	while (format[i] != '\0')
	{
		get_ok = get_el(format, &i, valist, buffer, &pos, &n_printed);
		if (get_ok == 1)
			return (-1);
	}
	va_end(valist);

	chars_to_print = get_printable_length(buffer);
	print(buffer, chars_to_print);
	if (n_printed >= 0)
		n_printed += chars_to_print;
	return (n_printed);
}
