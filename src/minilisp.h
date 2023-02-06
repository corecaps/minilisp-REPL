/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilisp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:09:49 by jgarcia           #+#    #+#             */
/*   Updated: 2023/02/05 23:09:53 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILISP_REPL_MINILISP_H
# define MINILISP_REPL_MINILISP_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "mpc.h"
# include "../gnl/get_next_line.h"

/* evaluation */
long	eval_op(long x, char* op, long y);
long	eval(mpc_ast_t* t);
#endif //MINILISP_REPL_MINILISP_H