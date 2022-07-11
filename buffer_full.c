#incldue "main.h

/**
 * buffer_full - check if buffer is full and print if it is
 * @buffer: character buffer for printing
 * @pos: position in the buffer
 * @n_printed: number of printable characters
 */
void buffer_full(char *buffer, int *pos, int *n_printed)
{
	int chars_to_print, i;

	if (*pos == BUFFER_SIZE - 1)
	{
		chars_to_print = get_printable_length(buffer);
		print(buffer, chars_to_print);
		*n_printed += chars_to_print;
		*pos = 0;

		for (i = 0; i < BUFFER_SIZE; i++)
			buffer[i] = '\0';
	}
}
