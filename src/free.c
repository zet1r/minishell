#include "../inc/minishell.h"

void	free_token(t_sh *f)
{
	t_token *node;
	t_token	*tmp;

	node = f->token;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp->token_str);
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	f->token = NULL;
}

void	free_cmd(t_sh *sh)
{
	t_cmd	*node;
	t_cmd	*tmp;

	node = sh->cmd;
	while(node != NULL)
	{
		tmp = node;
		node = node->next;
		if (tmp->full_cmd)
			mtr_free(tmp->full_cmd);
		if (tmp->path)
			free(tmp->path);
		tmp->path = NULL;
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	sh->cmd = NULL;
}

void	free_all(t_sh *sh)
{
	if (!sh)
		return ;
	free_token(sh);
	free_cmd(sh);
	mtr_free(sh->envp);
	if (sh->parser)
		free(sh->parser);
	sh->parser = NULL;
	sh = NULL;
}
