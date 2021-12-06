#include "hls.h"

/**
 * handle_error - function to handle errno error
 * @name: name of the file or variable
 * Return: message
 */
void handle_error(char *name)
{
	switch (errno)
	{
	case ENOENT:
		fprintf(stderr, "hls: cannot access '%s': ", name);
		perror(NULL);
		break;
	case EACCES:
		fprintf(stderr, "hls: cannot open directory '%s': ", name);
		perror(NULL);
		break;
	}
}
