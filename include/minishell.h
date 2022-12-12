/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/12 16:39:49 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

# define SYNTAX_ERR "-minishell: syntax error near unexpected token"

typedef struct s_token {
	char		*token_str;
	char		token_type;
	struct	s_token	*next;
	struct	s_token *prev;
} t_token;

typedef	struct	s_cmd {
	char	**full_cmd; //cmd e args
	char	*path; //cmd PATH; se builtin deixar so nome
	int	in_fd;
	int	out_fd;
	int	err_fd;
	struct s_cmd *next;
	struct s_cmd *prev;
} t_cmd;

typedef struct t_sh {
	t_cmd	*cmds;
	t_token *token;
	char	**envp;
	int	last_pid;
	char	*str;
	int	pos;
	int	wd_begin;
} t_sh;

//sortInput.c
void	sortInput(t_sh *f);
void	lexer(t_sh *f);
void	lexer2(t_sh *f);
void	parser(t_sh *f);

//createWords.c //tokenizes the words
void	createWords(t_sh *f);
void	lexQuote(t_sh *f);
void	lexWdend(t_sh *f);
void	lexOp(t_sh *f);
int	findOperator(char c);

//lexer.c

//lexer_utils.c
void	rmvQuotes(t_sh *f);
int	countPairs(char *s);

//parser.c
int     charArrayLen(char **array);
void    addStrCmd(t_cmd *node, char *s);
void    ddl_append(t_cmd *last);
void	initCmd(t_cmd *node);

//ddl_utils.c
void	append_dll(t_sh *f, t_token **head, char *s);
void	addType_ll(t_sh *f, char type);
void 	append_dll_cmd(t_sh *f, t_cmd **head);
void	printList(t_token *head);
void	printListCmd(t_cmd *head);
void	remove_dll(t_sh *f);

//free.c
void	freeTokens(t_sh *f);

//readline.c
char	*get_str(void);
char	*resolve_str(char	*line);
char	*get_prompt(void);

//signal.c
void sig_handler(int signal);
void handle_sig();

//main.c"
void handle_sig();
void sig_handler(int signal);

#endif
