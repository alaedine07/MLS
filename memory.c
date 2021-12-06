#include "hls.h"

/**
 * free_list - free linked list
 * @head: head of linked list
 * Return: nothing
 */
void free_list(list_f *head)
{
	while (head)
	{
		list_f *aux = head;

		head = head->next_file_node;
		free(aux->filename);
		free(aux);
	}
}
/**
 * free_arguments - free arguments strcuture
 * @arguments_parsed: parsed arguments
 * Return: nothing
 */
void free_arguments(arguments *arguments_parsed)
{
	free(arguments_parsed->options);
	free(arguments_parsed->files_direcs);
	free(arguments_parsed);
}
