/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:29:54 by jgarcia           #+#    #+#             */
/*   Updated: 2023/02/06 00:29:57 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilisp.h"


t_lval lval_num(long x) {
	t_lval v;
	v.type = LVAL_NUM;
	v.num = x;
	return v;
}

t_lval lval_err(int x) {
	t_lval v;
	v.type = LVAL_ERR;
	v.err = x;
	return v;
}

void lval_print(t_lval v)
{
	switch (v.type)
	{
		case LVAL_NUM: printf("%li", v.num); break;
		case LVAL_ERR:
			if (v.err == LERR_DIV_ZERO) { printf("Error: Division By Zero!"); }
			if (v.err == LERR_BAD_NUM) { printf("Error: Invalid Number!"); }
			if (v.err == LERR_BAD_OP) { printf("Error: Invalid Operator!"); }
			if (v.err == LERR_OVERFLOW) { printf("Error: Overflow!"); }
			break;
	}
}

void lval_println(t_lval v)
{
	lval_print(v);
	putchar('\n');
}

t_lval 	eval_op(t_lval x, char* op, t_lval y) {
	if (x.type == LVAL_ERR) { return x; }
	if (y.type == LVAL_ERR) { return y; }

	if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
	if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
	if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
	if (strcmp(op, "/") == 0) {
		if (y.num == 0)
			return lval_err(LERR_DIV_ZERO);
		else
			return lval_num(x.num / y.num);
	}
	if (strcmp(op, "%") == 0) {
		if (y.num == 0)
			return lval_err(LERR_DIV_ZERO);
		else
			return lval_num(x.num % y.num);
	}
	if (strcmp(op, "^") == 0) {
		long res = 1;
		for (int i=0;i < y.num;i++)
		{
			if (res > LONG_MAX / x.num)
				return lval_err(LERR_OVERFLOW);
			res = res * x.num;
		}
		return lval_num(res);
	}
	return lval_err(LERR_BAD_OP);
}

t_lval 	eval(mpc_ast_t* t) {

	/* If tagged as number return it directly. */
	if (strstr(t->tag, "number")) {
		errno = 0;
		long x = strtol(t->contents, NULL, 10);
		if (errno != ERANGE)
			return lval_num(x);
		else
			return lval_err(LERR_BAD_NUM);
	}

	/* The operator is always second child. */
	char* op = t->children[1]->contents;

	/* We store the third child in `x` */
	t_lval x = eval(t->children[2]);

	/* Iterate the remaining children and combining. */
	int i = 3;
	while (strstr(t->children[i]->tag, "expr")) {
		x = eval_op(x, op, eval(t->children[i]));
		i++;
	}

	return x;
}