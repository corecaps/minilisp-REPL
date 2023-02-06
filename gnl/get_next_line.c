/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:48:55 by jgarcia           #+#    #+#             */
/*   Updated: 2022/06/23 11:03:52 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* read a line ( meaning until \n is encountered ) in the file pointed by fd
 * and return a heap allocated string containing the line,
 * any left characters are kept in the chained list pointed by head,
 * in case of error, or when the EOF is reached NULL is returned */

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	char			*result;
	size_t			size;

	result = NULL;
	if (((fd < 0) || (read(fd, &result, 0) < 0)) != 0)
		return (NULL);
	head = read_and_save(fd, head);
	if (head == NULL)
		return (NULL);
	size = list_len(head);
	result = malloc (sizeof(char) * (size + 2));
	if (result)
		result = extract_line(head, size, result);
	if (result == NULL)
		return (NULL);
	head = list_clean(head, 0, 0);
	if (result[0] == '\0')
	{
		list_free(head);
		free (result);
		head = NULL;
		return (NULL);
	}
	return (result);
}

/* Read in the file pointed by fd until it reaches \n or EOF
 * return a pointer to the head of list where data are saved
 * in case of error return NULL */

t_list	*read_and_save(int fd, t_list *head)
{
	long int	size;
	char		*buffer;

	size = 1;
	while ((find_new_line(head) != 0) && size != 0)
	{
		buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return (NULL);
		size = read(fd, buffer, BUFFER_SIZE);
		if ((head == NULL && size == 0) || size < 0)
		{
			free (buffer);
			return (NULL);
		}
		buffer[size] = '\0';
		head = add_node(head, buffer, size);
		free(buffer);
	}
	return (head);
}

/* copy string from linked list content pointed by head
 * until \n or \0 encountered and return a heap allocated
 * string containing the line
 * return NULL in case of error */

char	*extract_line(t_list *head, size_t size, char *result)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (head)
	{
		i = 0;
		while (head->content[i] && j <= size)
		{
			result[j++] = head->content[i++];
			if (result[j - 1] == '\n')
			{
				result[j] = '\0';
				return (result);
			}
		}
		head = head->next;
	}
	if (j > 0)
	{
		result[j] = '\0';
		return (result);
	}
	result[0] = '\0';
	return (result);
}

/* Get remaining characters after \n from linked list pointed by head
 * copy them in a new linked list pointed by new_node
 * free the old linked list pointed by head
 * return the head of the new list or NULL in case of error */

t_list	*list_clean(t_list *head, size_t i, size_t j)
{
	size_t	size;
	t_list	*new_head;
	t_list	*last_node;

	new_head = malloc(sizeof(t_list));
	if (head == NULL || new_head == NULL)
		return (NULL);
	last_node = list_last(head);
	while (last_node->content[i] && last_node->content[i] != '\n')
		i ++;
	if (last_node->content[i] == '\n')
		i ++;
	size = 0;
	while (last_node->content[i + size])
		size ++;
	new_head->next = NULL;
	new_head->content = malloc(sizeof(char) * (size + 1));
	if (new_head->content == NULL)
		return (NULL);
	j = 0;
	while (last_node->content && last_node->content[i] && j < size)
		new_head->content[j++] = last_node->content[i++];
	new_head->content[size] = '\0';
	list_free(head);
	return (new_head);
}
