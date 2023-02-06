/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:09:50 by jgarcia           #+#    #+#             */
/*   Updated: 2022/06/14 15:46:38 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* search for the last node of the linked head
 * pointed by head
 * return a pointer to the last node of the linked list
 * return NULL in case of error */

t_list	*list_last(t_list *head)
{
	if (head != NULL)
	{
		while (head && head->next)
			head = head->next;
	}
	return (head);
}

/* Search the linked list pointed by head for
 * \n return 0 if found, 1 if not */

size_t	find_new_line(t_list *head)
{
	t_list	*last;
	size_t	pos;

	if (head == NULL)
		return (1);
	last = list_last(head);
	pos = 0;
	if (last == NULL || last->content == NULL)
	{
		return (1);
	}
	while (last->content[pos] && pos < BUFFER_SIZE)
	{
		if (last->content[pos] == '\n')
			return (0);
		pos ++;
	}
	return (1);
}

/*  free all the nodes of the list pointed by head */

void	list_free(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		free (head->content);
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

/* Add a new node to the chained list pointed by head, which content is buffer
 * return the correct head to list */

t_list	*add_node(t_list *head, const char *buffer, size_t size)
{
	t_list	*last_node;
	t_list	*new_node;
	size_t	pos;

	new_node = malloc (sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (size + 1));
	if (new_node->content == NULL )
		return (NULL);
	pos = 0;
	while (buffer[pos] && pos < size)
	{
		new_node->content[pos] = buffer[pos];
		pos ++;
	}
	new_node->content[pos] = '\0';
	if (head == NULL)
		return (new_node);
	last_node = list_last(head);
	last_node->next = new_node;
	return (head);
}

size_t	list_len(t_list *head)
{
	size_t	size;
	size_t	pos;

	size = 0;
	if (head && head->content)
	{
		while (head)
		{
			pos = 0;
			while (head->content[pos] != '\0')
			{
				pos++;
				if (head->content[pos] == '\n')
					return (size + pos);
			}
			size += pos;
			head = head->next;
		}
	}
	return (size);
}
