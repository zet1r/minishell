#include "../inc/minishell.h"

void	freeTokens(t_sh *f)
{
	while (f->token->next != NULL)
	{
		printf("free token: %s\n", f->token->token_str);
		f->token = f->token->next;
		free(f->token->prev->token_str);
		f->token->prev->next = NULL;
		free(f->token->prev);
		f->token->prev = NULL;
	}
	printf("free token: %s\n", f->token->token_str);
	free(f->token->token_str);
	free(f->token);
	f->token = NULL;
}