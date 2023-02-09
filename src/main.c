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

int	main(int argc, char **argv)
{
	char		*line = NULL;
	int			fd = 0;

	mpc_parser_t *Number = mpc_new("number");
	mpc_parser_t *Symbol = mpc_new("symbol");
	mpc_parser_t *Sexpr = mpc_new("sexpr");
	mpc_parser_t *Expr = mpc_new("expr");
	mpc_parser_t *Minilisp = mpc_new("minilisp");
	mpca_lang(MPCA_LANG_DEFAULT,
			  "                                    \
        number      : /-?[0-9]+/ ;                          \
        symbol      : '+' | '-' | '*' | '/' | '%' | '^' ;   \
        sexpr       : '(' <expr>* ')' ;                      \
        expr        : <number> | <symbol> | <sexpr> ;       \
        minilisp    : /^/ <expr>* /$/ ;          \
        ", Number, Symbol, Sexpr, Expr, Minilisp);
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			printf(">\tError: File not found\t<\n");
			return (1);
		}
		printf("\n>\tMiniLisp file eval Welcome\t <\n");
		line = get_next_line(fd);
		while (line)
		{
			mpc_result_t r;
			if (mpc_parse("<stdin>", line, Minilisp, &r))
			{
				printf("Expr\t-> %s", line);
				t_lval *result = lval_eval(r.output);
				printf(">\tresult: ");
				lval_print(result);
				printf("\t<\n");
				mpc_ast_delete(r.output);
			}
			else
			{
				/* Otherwise print and delete the Error */
				mpc_err_print(r.error);
				mpc_err_delete(r.error);
			}
			free(line);
			line = get_next_line(fd);
		}
		mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Minilisp);
		printf("\n>\tMinilisp REPL Bye!\t<\n");
		printf("\n>\tMiniLisp REPL Welcome\t <\n");
	}
	while (1)
	{
		line = readline("MiniLisp\t> ");
		if (!line)
			break ;
		if (strcmp(line, "exit") == 0)
		{
			free (line);
			break ;
		}
		if (*line)
			add_history(line);
		mpc_result_t r;
		if (mpc_parse("<stdin>", line, Minilisp, &r)) {
			/* evaluate the AST and print the result */
			t_lval *result = lval_eval(lval_read(r.output));
			printf(">\tresult: ");
			lval_print(result);
			printf("\t<\n");
			mpc_ast_delete(r.output);
		} else {
			/* Otherwise print and delete the Error */
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		free(line);
	}
	mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Minilisp);
	printf("\n>\tMinilisp REPL Bye!\t<\n");
	return (0);
}