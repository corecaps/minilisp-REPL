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

t_lval	*lval_read_num(mpc_ast_t* t) {
	errno = 0;
	long x = strtol(t->contents, NULL, 10);
	return errno != ERANGE ?
		   lval_num(x) : lval_err("invalid number");
}
t_lval*	lval_read(mpc_ast_t* t) {

	/* If Symbol or Number return conversion to that type */
	if (strstr(t->tag, "number")) { return lval_read_num(t); }
	if (strstr(t->tag, "symbol")) { return lval_sym(t->contents); }

	/* If root (>) or sexpr then create empty list */
	t_lval *x = NULL;
	if (strcmp(t->tag, ">") == 0) { x = lval_sexpr(); }
	if (strstr(t->tag, "sexpr"))  { x = lval_sexpr(); }

	/* Fill this list with any valid expression contained within */
	for (int i = 0; i < t->children_num; i++) {
		if (strcmp(t->children[i]->contents, "(") == 0) { continue; }
		if (strcmp(t->children[i]->contents, ")") == 0) { continue; }
		if (strcmp(t->children[i]->tag,  "regex") == 0) { continue; }
		x = lval_add(x, lval_read(t->children[i]));
	}

	return x;
}

void lval_expr_print(t_lval* v, char open, char close) {
	putchar(open);
	for (int i = 0; i < v->count; i++) {

		/* Print Value contained within */
		lval_print(v->cell[i]);

		/* Don't print trailing space if last element */
		if (i != (v->count-1)) {
			putchar(' ');
		}
	}
	putchar(close);
}

void lval_print(t_lval* v) {
	switch (v->type) {
		case LVAL_NUM:   printf("%li", v->num); break;
		case LVAL_ERR:   printf("Error: %s", v->err); break;
		case LVAL_SYM:   printf("%s", v->sym); break;
		case LVAL_SEXPR: lval_expr_print(v, '(', ')'); break;
	}
}

void lval_println(t_lval* v) {
	lval_print(v);
	putchar('\n');
}

t_lval	*builtin_op(t_lval* a, char* op) {

	/* Ensure all arguments are numbers */
	for (int i = 0; i < a->count; i++) {
		if (a->cell[i]->type != LVAL_NUM) {
			lval_del(a);
			return lval_err("Cannot operate on non-number!");
		}
	}

	/* Pop the first element */
	t_lval	*x = lval_pop(a, 0);

	/* If no arguments and sub then perform unary negation */
	if ((strcmp(op, "-") == 0) && a->count == 0) {
		x->num = -x->num;
	}

	/* While there are still elements remaining */
	while (a->count > 0) {

		/* Pop the next element */
		t_lval	*y = lval_pop(a, 0);

		if (strcmp(op, "+") == 0) { x->num += y->num; }
		if (strcmp(op, "-") == 0) { x->num -= y->num; }
		if (strcmp(op, "*") == 0) { x->num *= y->num; }
		if (strcmp(op, "/") == 0) {
			if (y->num == 0) {
				lval_del(x);
				lval_del(y);
				x = lval_err("Division By Zero!\n"); break;
			}
			x->num /= y->num;
		}
		if (strcmp(op, "%") == 0) {
			if (y->num == 0)
			{
				lval_del(x);
				lval_del(y);
				x = lval_err("Division By Zero!\n");
			}
			else
				x->num = x->num % y->num;
		}
		if (strcmp(op, "^") == 0) {
			long res = 1;
			for (int i=0;i < y->num;i++)
			{
				if (res > LONG_MAX / x->num)
					return lval_err("Integer overflow!\n");
				res = res * x->num;
			}
			x = lval_num(res);
		}
		lval_del(y);
	}
	lval_del(a);
	return x;
}

t_lval	*lval_eval_sexpr(t_lval *v) {
	/* Evaluate Children */
	for (int i = 0; i < v->count; i++) {
		v->cell[i] = lval_eval(v->cell[i]);
	}

	/* Error Checking */
	for (int i = 0; i < v->count; i++) {
		if (v->cell[i]->type == LVAL_ERR) { return lval_take(v, i); }
	}

	/* Empty Expression */
	if (v->count == 0) { return v; }

	/* Single Expression */
	if (v->count == 1) { return lval_take(v, 0); }

	/* Ensure First Element is Symbol */
	t_lval	*f = lval_pop(v, 0);
	if (f->type != LVAL_SYM) {
		lval_del(f); lval_del(v);
		return lval_err("S-expression Does not start with symbol!");
	}

	/* Call builtin with operator */
	t_lval	*result = builtin_op(v, f->sym);
	lval_del(f);
	return result;
}

t_lval	*lval_eval(t_lval *v) {
	/* Evaluate Sexpressions */
	if (v->type == LVAL_SEXPR) { return lval_eval_sexpr(v); }
	/* All other lval types remain the same */
	return v;
}

t_lval	*lval_pop(t_lval *v, int i) {
	/* Find the item at "i" */
	t_lval	*x = v->cell[i];

	/* Shift memory after the item at "i" over the top */
	memmove(&v->cell[i], &v->cell[i+1],
			sizeof(t_lval*) * (v->count-i-1));

	/* Decrease the count of items in the list */
	v->count--;

	/* Reallocate the memory used */
	v->cell = realloc(v->cell, sizeof(t_lval*) * v->count);
	return x;
}

t_lval	*lval_take(t_lval *v, int i) {
	t_lval	*x = lval_pop(v, i);
	lval_del(v);
	return x;
}