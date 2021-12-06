#include "hls.h"

char *get_filename(char *d_name, char *directory_name)
{
	int i,j;
	size_t l1 = strlen(d_name);
	size_t l2 = strlen(directory_name);

	char *filename = malloc((l1 + l2) * sizeof(char));
	memset(filename, '0', l1+l2);
	for (i = 0; directory_name[i]; i++)
	{
		filename[i] = directory_name[i];
	}
	if (filename[i - 1] != '/')
	{
		filename[i] = '/';
		i++;
	}
	for (j = 0; d_name[j]; j++)
	{
		filename[i] = d_name[j];
		i++;
	}
	return (filename);
}

/**
 * open_directory - handle opening current directory
 * when no file or directory is provided
 * do not add hidden files if not asked for
 * @options: string contains the options
 * @directory_name: name of the directory to process
 * Return: 0 for sucess or errors
 */
size_t	open_directory(char *options, char *directory_name)
{
	DIR *dir;
	struct dirent *read;
	list_f *head = NULL;
	char *r;
	int include_hidden_files = 0;
	int almost_all = 0;
	char *filename;
	(void)filename;
	/* check if user asked for hidden files */
	r = _strchr(options, 'a');
	if (r != NULL)
		include_hidden_files = 1;
	r = _strchr(options, 'A');
	if (r != NULL)
		almost_all = 1;
	/* read the first file or directory and add to linked list */
	dir = opendir(directory_name);
	if (dir == NULL)
	{
		handle_error(directory_name);
		return (2);
	}
	read = readdir(dir);
	while ((read = readdir(dir)) != NULL)
	{
		printf("file is : %s\n", read->d_name);
		// filename = get_filename(read->d_name, directory_name);
		/* printf("filename is: %s\n", filename); */
		if (include_hidden_files)
			add_standard(&head, read->d_name, options);
		else if (almost_all)
		{
			if (strcmp(read->d_name, ".") && strcmp(read->d_name, ".."))
			{
				add_standard(&head, read->d_name, options);
			}
		}
		else
		{
			if (*read->d_name != '.')
				add_standard(&head, read->d_name, options);
		}
	}
	print_files(head, options);
	free_list(head);
	closedir(dir);
	return (0);
}
/**
 * parse_arguments - extract files and options from argv
 * @argv: arguments
 * Return: 0 for sucess or errors
 */
arguments *parse_arguments(char **argv)
{
	size_t i = 1;
	size_t option_counter = 0;
	size_t files_counter = 0;
	size_t j;
	char *arg_option;

	arguments *arguments_parsed = malloc(sizeof(arguments));

	arguments_parsed->options = malloc(sizeof(BUFSIZE));
	arguments_parsed->files_direcs = malloc(sizeof(char *) * BUFSIZE);

	while (*(argv + i))
	{
		/* case if the argument is an option */
		if (*(argv + i)[0] == '-')
		{
			arg_option = *(argv + i);
			for (j = 1; arg_option[j]; j++)
			{
				/* add check if the option is available or not */
				/* add check if the option is already added or not */
				arguments_parsed->options[option_counter] = arg_option[j];
				option_counter++;
			}
		}
		/* argument is considered a file or directory */
		else
		{
			arguments_parsed->files_direcs[files_counter] = *(argv + i);
			files_counter++;
		}
		i++;
	}
	arguments_parsed->files_direcs[files_counter] = '\0';
	arguments_parsed->options[option_counter] = '\0';
	return (arguments_parsed);
}

/**
 * main - entry point of the ls program
 * @argc: number of arguments
 * @argv: pointer to array of strings
 *
 * Return: 0 on success, 1 or 2 for errors
 */
int main(int argc, char **argv)
{
	size_t status = 0;
	size_t new_status = 0;
	arguments *arguments_parsed;

	(void)argc;
	/* extract options, files and directories name */
	arguments_parsed = parse_arguments(argv);
	/* if no directory is specified open the current directory */
	if (arguments_parsed->files_direcs[0] == NULL)
	{
		new_status = open_directory(arguments_parsed->options, ".");
		free_arguments(arguments_parsed);
		if (new_status > status)
			status = new_status;
		return (status);
	}
	/* list with arguments */
	new_status = _list(arguments_parsed->files_direcs,
						arguments_parsed->options);
	if (new_status > status)
		status = new_status;
	free_arguments(arguments_parsed);
	return (status);
}
