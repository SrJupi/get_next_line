#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char	*get_next_line(int fd);

int main (int argc, char **argv)
{
	(void) argc;
	(void) argv;
	
	int		f;
	char	*result;

	f = open("test.txt", O_RDONLY);
	if (f <= 0)
		return (0);
	result = get_next_line(f);
	if (result == NULL)
		return (0);
	printf("1 - %s\n", result);
	free(result);
	result = get_next_line(f);
	if (result == NULL)
		return (0);
	printf("2 - %s\n", result);
	free(result);
	result = get_next_line(f);
	if (result == NULL)
		return (0);
	printf("3 - %s\n", result);
	free(result);
}