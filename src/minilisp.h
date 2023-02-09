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
	char *err;
	char *sym;
	int count;
	struct s_lval **cell;
} t_lval;

enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR };
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM, LERR_OVERFLOW };
/* constructors */
t_lval	*lval_num(long x);
t_lval	*lval_err(char *msg);
t_lval	*lval_sym(char *s);
t_lval	*lval_sexpr(void);
t_lval	*lval_add(t_lval* v, t_lval* x);
/* destructor */
void	lval_del(t_lval *v);
/* evaluation */
t_lval	*lval_read_num(mpc_ast_t* t);
t_lval	*lval_read(mpc_ast_t* t);
t_lval	*lval_add(t_lval* v, t_lval* x);
t_lval	*lval_eval(t_lval *v);
void	lval_print(t_lval* v);
t_lval	*lval_take(t_lval *v, int i);
t_lval	*lval_pop(t_lval *v, int i);
#endif //MINILISP_REPL_MINILISP_H