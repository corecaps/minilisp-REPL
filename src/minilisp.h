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
# include <limits.h>

typedef struct s_lval{
	int type;
	long num;
	int err;
} t_lval;
enum { LVAL_NUM, LVAL_ERR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM, LERR_OVERFLOW };
/* evaluation */
t_lval 	eval_op(t_lval x, char* op, t_lval y);
t_lval 	eval(mpc_ast_t* t);
void	lval_print(t_lval v);
#endif //MINILISP_REPL_MINILISP_H