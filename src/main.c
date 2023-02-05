/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:09:58 by jgarcia           #+#    #+#             */
/*   Updated: 2023/02/05 23:10:00 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilisp.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minilisp> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		printf("line: %s\n", line);
		free(line);
	}
	return (0);
}