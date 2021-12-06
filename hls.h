#ifndef LS_HEADER
#define LS_HEADER

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


#define BUFSIZE 200

/**
 * struct list_files - singly linked list
 * @filename: name of the file
 * @next_file_node: pointer to the next node
 *
 * Description: singly linked list the holds all the files
 */
typedef struct list_files
{
	char *filename;
	struct stat file_stat;
	struct list_files *next_file_node;
} list_f;

/**
 * struct arguments_structure - definition
 * @options: - example (-l, -r ...)
 * @files_direcs: passed files and directories
 *
 * Description: holds specified options, files and directories
 */
typedef struct arguments_structure
{
	char *options;
	char **files_direcs;
} arguments;

size_t open_directory(char *options, char *directory_name);
list_f *add_standard(list_f **head, char *file_name, char *options);
size_t _list(char **files, char *options);
void print_files(list_f *head, char *options);
void print_permessions(list_f *head);
void print_last_modification(list_f *head);


/* memeory related functions */
void free_list(list_f *head);
void free_arguments(arguments *arguments_parsed);

/* error related functions */
void handle_error(char *name);

/* custom functions */
char *_strdup(char *duplicate);
char *_strchr(char *s, char c);

#endif
