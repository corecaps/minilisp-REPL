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

void grammar_def(const mpc_parser_t *Number, const mpc_parser_t *Operator,
				 const mpc_parser_t *Expr, const mpc_parser_t *Lispy)
{
	mpca_lang(MPCA_LANG_DEFAULT,
			  "                                                     \
      number   : /-?[0-9]+/ ;                             \
      operator : '+' | '-' | '*' | '/' | '%' | '^' ;            \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      lispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
			  Number, Operator, Expr, Lispy);
}


int file_eval(char *const *argv, char *line, int fd, const mpc_parser_t *Number,
			  const mpc_parser_t *Operator, const mpc_parser_t *Expr,
			  mpc_parser_t *Lispy)
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
		if (mpc_parse("<stdin>", line, Lispy, &r))
		{
			printf("Expr\t-> %s", line);
			t_lval result = eval(r.output);
			printf(">\tresult: ");
			lval_print(result);
			printf("\t<\n");
			mpc_ast_delete(r.output);
		}else {
			/* Otherwise print and delete the Error */
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		free(line);
		line = get_next_line(fd);
	}
	mpc_cleanup(4, Number, Operator, Expr, Lispy);
	printf("\n>\tMinilisp REPL Bye!\t<\n");
	return (0);
}

int	main(int argc, char **argv)
{
	char	*line = NULL;
	int		fd = 0;

	mpc_parser_t* Number   = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr     = mpc_new("expr");
	mpc_parser_t* Lispy    = mpc_new("lispy");

	grammar_def(Number, Operator, Expr, Lispy);
	if (argc == 2)
		return (file_eval(argv, line, fd, Number, Operator, Expr, Lispy));
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
			t_lval result = eval(r.output);
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
	mpc_cleanup(4, Number, Operator, Expr, Lispy);
	printf("\n>\tMinilisp REPL Bye!\t<\n");
	return (0);
}