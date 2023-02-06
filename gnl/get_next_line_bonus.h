/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:49:50 by jgarcia           #+#    #+#             */
/*   Updated: 2022/06/20 11:15:42 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*read_and_save(int fd, t_list *head);
t_list	*add_node(t_list *head, const char *buffer, size_t size);
t_list	*list_last(t_list *head);
size_t	list_len(t_list *head);
void	list_free(t_list *head);
size_t	find_new_line(t_list *head);
char	*extract_line(t_list *head, size_t size, char *result);
t_list	*list_clean(t_list *head, size_t i, size_t j);

#endif
