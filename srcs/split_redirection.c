/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:11:59 by psaulnie          #+#    #+#             */
/*   Updated: 2022/04/05 10:18:49 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_list_char	*insert_new_link(t_index var, char *cmd,
		t_list_char **start)
{
	char		*str;
	t_list_char	*new_link;

	str = ft_stridup(cmd, var.i, var.j);
	if (!str)
	{
		lstclear_char(start, free);
		exit_error_msg("Malloc error");
	}
	new_link = lstnew_char(str);
	if (!new_link)
	{
		free(str);
		lstclear_char(start, free);
		exit_error_msg("Malloc error");
	}
	return (new_link);
}

static t_index	skipper(t_index var, char *cmd)
{
	while (cmd[var.i] && (cmd[var.i] != '<' && cmd[var.i] != '>'
			&& var.quotes % 2 == 0))
	{
		if (cmd[var.i] == '\'' && (var.quotes == '0'))
			var.quote = '\'';
		if (cmd[var.i] == '"' && (var.quotes == '0'))
			var.quote = '"';
		if (cmd[var.i] == var.quotes)
			var.quotes++;
		if (var.quotes == 2)
		{
			var.quote = '0';
			var.quotes = 0;
		}
		var.i++;
	}
	var.j = var.i;
	while (cmd[var.j] && !ft_iswhitespace(cmd[var.j]))
		var.j++;
	return (var);
}

static char	*splitter(t_list_char **start, char *cmd, t_list_char **command)
{
	t_index		var;
	t_list_char	*new_link;

	var.i = 0;
	var.quote = '0';
	var.quotes = 0;
	var = skipper(var, cmd);
	if (cmd[var.j])
		var.j++;
	if (cmd[var.j])
		while (cmd[var.j] && !ft_iswhitespace(cmd[var.j]))
			var.j++;
	if (var.j != var.i && var.i != 0 && var.j != (int)ft_strlen(cmd) - 1)
	{
		new_link = insert_new_link(var, cmd, start);
		new_link->next = (*command)->next;
		(*command)->next = new_link;
		cmd = ft_strcut(cmd, var.i, var.j);
		if (!cmd)
		{
			lstclear_char(start, free);
			exit_error_msg("Malloc error");
		}
	}
	return (cmd);
}

void	split_redirection(t_list_char **cmd)
{
	t_list_char	*start;

	start = *cmd;
	while (*cmd != NULL)
	{
		(*cmd)->content = splitter(&start, (*cmd)->content, cmd);
		(*cmd) = (*cmd)->next;
	}
	*cmd = start;
}
