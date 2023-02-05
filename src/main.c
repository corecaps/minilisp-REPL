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
	while (1)
	{
		line = readline("minilisp> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		printf("line: %s\n", line);
		mpc_result_t r;
		if (mpc_parse("<stdin>", line, Lispy, &r)) {
			/* On success print and delete the AST */
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
		} else {
			/* Otherwise print and delete the Error */
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		free(line);
	}
	return (0);
}