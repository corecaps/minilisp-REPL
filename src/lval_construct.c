//
// Created by corecaps on 08/02/23.
//

#include "minilisp.h"

t_lval	*lval_add(t_lval* v, t_lval* x) {
	v->count++;
	v->cell = realloc(v->cell, sizeof(t_lval*) * v->count);
	v->cell[v->count-1] = x;
	return v;
}

t_lval *lval_num(long x) {
	t_lval *v = malloc(sizeof(t_lval));
	if (v == NULL)
		return (NULL);
	v->type = LVAL_NUM;
	v->num = x;
	return v;
}

t_lval *lval_err(char *msg) {
	t_lval *v = malloc(sizeof(t_lval));
	if (v == NULL)
		return (NULL);
	v->type = LVAL_ERR;
	v->err = strdup(msg);
	return v;
}
t_lval *lval_sym(char *s) {
	t_lval *v = malloc(sizeof(t_lval));
	if (v == NULL)
		return (NULL);
	v->type = LVAL_SYM;
	v->sym = strdup(s);
	return v;
}

t_lval *lval_sexpr(void) {
	t_lval *v = malloc(sizeof(t_lval));
	if (v == NULL)
		return (NULL);
	v->type = LVAL_SEXPR;
	v->count = 0;
	v->cell = NULL;
	return v;
}

void lval_del(t_lval *v)
{
	switch (v->type)
	{
		case LVAL_NUM: break;
		case LVAL_ERR: free(v->err); break;
		case LVAL_SYM: free(v->sym); break;
		case LVAL_SEXPR:
			for (int i=0;i < v->count;i++)
			{
				lval_del(v->cell[i]);
			}
			free (v->cell);
			break;
	}
	free (v);
}