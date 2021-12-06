#include "hls.h"

/**
 * _list - list files and directories
 * @files: list of files to treat
 * @options: string containing the options
 * Return: 0 for sucess or errors
 */
size_t _list(char **files, char *options)
{
	struct stat file_info;
	size_t i = 0;
	size_t ret = 0;
	list_f *head = NULL;
	int err;

	while (*(files + i) != NULL)
	{
		err = lstat(*(files + i), &file_info);
		if (err != 0)
		{
			handle_error(*(files + i));
			return (2);
		}
		/* check if file exists */
		switch (file_info.st_mode & __S_IFMT)
		{
			case __S_IFREG:
				add_standard(&head, *(files + i), options);
				break;
			case __S_IFDIR:
				ret = open_directory(options, *(files + i));
				break;
		}
		i++;
	}
	if (head != NULL)
	{
		print_files(head, options);
		free_list(head);
	}
	return (ret);
}

void print_permessions(list_f *head)
{
	printf( (S_ISDIR(head->file_stat.st_mode)) ? "d" : "-");
    printf( (head->file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (head->file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (head->file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (head->file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (head->file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (head->file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (head->file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf( (head->file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (head->file_stat.st_mode & S_IXOTH) ? "x" : "-");
	printf(" ");
}

void print_user_group(list_f *head)
{
	struct passwd *pw;
	struct group *gr;

	pw = getpwuid(head->file_stat.st_uid);
	gr = getgrgid(head->file_stat.st_gid);

	printf("%s %s\t", pw->pw_name, gr->gr_name);
}

void print_last_modification(list_f *head)
{

	char *time = ctime(&head->file_stat.st_mtime);
	if (strlen(time) >= 16)
	{
		/* skip first bytes */
		time += 4;
		/* remove the \n */
		time[12] = 0;
	}
	printf("%s ", time);
}

/**
 * print_files - printf files and directories from singly linked list
 *
 * @head: head of the linked list
 * @options: string containing the options
 * Return: void
 */
void print_files(list_f *head, char *options)
{
	char *r;
	int one_file_perline = 0;
	int all_file_metadata = 0;

	r = _strchr(options, '1');
	if (r != NULL)
		one_file_perline = 1;
	r = _strchr(options, 'l');
	if (r != NULL)
		all_file_metadata = 1;
	while (head)
	{
		if (all_file_metadata)
		{
			print_permessions(head);
			printf("%ld ", head->file_stat.st_nlink);
			print_user_group(head);
			printf("%ld\t", head->file_stat.st_size);
			print_last_modification(head);
		}
		printf("%s", head->filename);
		if (one_file_perline || all_file_metadata)
			printf("\n");
		else
			printf("  ");
		head = head->next_file_node;
	}
	if (!(one_file_perline || all_file_metadata))
		printf("\n");
}
/**
 * add_standard - add file_node to linked list
 *
 * @head: head of the linked list
 * @file_name: name of the file to add
 * Return: new node to the linked list
 */
list_f *add_standard(list_f **head, char *file_name, char *options)
{
	/* current node points to head of linked list */
	char *r;
	int err;
	list_f *current_node = *head;
	list_f *new_file_node = malloc(sizeof(list_f));

	if (new_file_node == NULL)
	{
		fprintf(stderr, "allocation error \n");
		free_list(*head);
		exit(2);
	}
	new_file_node->filename = _strdup(file_name);
	new_file_node->next_file_node = NULL;
	r = _strchr(options, 'l');
	if (r != NULL)
	{
		err = lstat(file_name, &new_file_node->file_stat);
		if (err != 0)
		{
			handle_error(file_name);
			exit(2);
		}
	}
	/* if head is the last node */
	if (*head == NULL)
	{
		*head = new_file_node;
	}
	else
	{
		/* move the current node to last node of linked list */
		while (current_node->next_file_node != NULL)
		{
			current_node = current_node->next_file_node;
		}
	current_node->next_file_node = new_file_node;
	}
	return (new_file_node);
}
