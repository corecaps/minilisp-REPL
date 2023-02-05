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

	/* Create Some Parsers */
	mpc_parser_t* Number   = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr     = mpc_new("expr");
	mpc_parser_t* Lispy    = mpc_new("lispy");

	/* Define them with the following Language */
	mpca_lang(MPCA_LANG_DEFAULT,
			  "                                                     \
      number   : /-?[0-9]+/ ;                             \
      operator : '+' | '-' | '*' | '/' ;                  \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      lispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
			  Number, Operator, Expr, Lispy);
	printf("\n>\tMiniLisp REPL Welcome\t <\n");
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
		if (mpc_parse("<stdin>", line, Lispy, &r)) {
			/* evaluate the AST and print the result */
			long result = eval(r.output);
			printf(">\tresult: %li\t<\n", result);
			mpc_ast_delete(r.output);
		} else {
			/* Otherwise print and delete the Error */
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		free(line);
	}
	mpc_cleanup(4, Number, Operator, Expr, Lispy);
	printf("\n>\tMinilisp REPL Bye!\t<\n");
	return (0);
}