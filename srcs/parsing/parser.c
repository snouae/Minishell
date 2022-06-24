/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:52:59 by snouae            #+#    #+#             */
/*   Updated: 2022/06/24 20:35:01 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		len(long nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char *str;
	long	n;
	int		i;

	n = nb;
	i = len(n);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

void	ft_lstadd_back1(t_redirection **lst, t_redirection *new)
{
	t_redirection	*list;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	list = *lst;
	while (list->next)
		list = list->next;
	list->next = new;
}

int	cherche_symbol(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

char	*check_dollar(int *j, char *str, char *new, char **env)
{
	int		start;
	char	*dlr;
	char	*expndr;

	start = *j;
	(*j)++;
	if (str[*j] <= '9' && str[*j] >= '0')
	{
		dlr = fill_array(str, start, *j);
		expndr = expander(dlr, env);
		new = ft_strjoin_n(new, expndr);
	}
	else
	{
		while (str[*j] != '\"' && str[*j] != ' ' && str[*j] != tab && str[*j]
			&& str[*j] != dollar && search_token(str[*j]) == -1
			&& !cherche_symbol(str[*j], "\t!$%'()*+,-./:;<=>?@[]^`{|}~"))
			(*j)++;
		(*j)--;
		dlr = fill_array(str, start, *j);
		expndr = expander(dlr, env);
		new = ft_strjoin_n(new, expndr);
	}
	return (new);
}

char	*remove_double_quote(char *str, char **env)
{
	char	*new;
	int		leng;
	int		j;
	int		start;
	char	*tmp;

	j = 0;
	new = NULL;
	leng = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	while (++j < leng - 1)
	{
		if (str[j] == dollar
			&& !cherche_symbol(str[j + 1], "\t!$%'() *\"+,-./:;<=>?@[]^`{|}~"))
			new = check_dollar(&j, str, new, env);
		else
		{
			tmp[0] = str[j];
			new = ft_strjoin_n(new, tmp);
		}
	}
	free(tmp);
	free(str);
	return (new);
}

char	*remove_single_quote(char *str)
{
	char	*new;
	char	*tmp;
	int		leng;
	int		i;

	i = 1;
	new = NULL;
	leng = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	while (i < leng - 1)
	{
		tmp[0] = str[i];
		new = ft_strjoin_n(new, tmp);
		i++;
	}
	free(tmp);
	free(str);
	return (new);
}

int	skip_redirect(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '>' || str[i] == '<')
		i = 2;
	while (cherche_symbol(str[i], " \t\n\v\f\r"))
		i++;
	return (i);
}

char	*join_dollar(t_list **tmp, int *test, char **env, char *str)
{
	char	*new;
	
	(*tmp)->next->str = ft_strdup_n(expander((*tmp)->next->str, env));
	new = ft_strjoin_n(ft_strdup(str), (*tmp)->next->str);
	(*tmp) = (*tmp)->next;
	*test = 1;
	return (new);
}

char	*check(char *str, char **env, t_list **tmp, int *test)
{
	char	*new;

	new = NULL;
	if ((*tmp)->next)
	{
		if ((*tmp)->next->str[0] == dollar)
			new = join_dollar(tmp, test, env, str);
		else if ((*tmp)->next->str[0] == double_quo)
		{
			(*tmp)->next->str = remove_double_quote((*tmp)->next->str, env);
			new = ft_strjoin_n(ft_strdup_n(str), (*tmp)->next->str);
			(*tmp) = (*tmp)->next;
			*test = 1;
		}
		else if ((*tmp)->next->str[0] == single_quo)
		{
			(*tmp)->next->str = remove_single_quote((*tmp)->next->str);
			new = ft_strjoin_n(ft_strdup_n(str), (*tmp)->next->str);
			(*tmp) = (*tmp)->next;
			*test = 1;
		}
	}
	return (new);
}

t_redirection	*fill_riderect(char *str, t_list **tmp, char **env)
{
	t_redirection	*new;
	int				test;
	int				i;

	test = 0;
	i = skip_redirect(str);
	new = (t_redirection *)malloc(sizeof(t_redirection));
	new->file = check(str + i, env, tmp, &test);
	if (!test)
		new->file = ft_strdup_n(str + i);
	if (str[0] == '<' && str[1] == '<')
		new->type = HEREDOC;
	else if (str[0] == '>' && str[1] == '>')
		new->type = APPEND;
	else if (str[0] == '<')
		new->type = IN;
	else if (str[0] == '>')
		new->type = OUT;
	new->next = NULL;
	return (new);
}

int	count_commads(t_list **head)
{
	int		c;
	t_list	*current;

	c = 1;
	current = *head;
	while (current != NULL)
	{
		if (current->type == 124)
			c++;
		current = current->next;
	}
	return (c);
}

t_list	*ft_count_args(t_list *current, int *count)
{
	*count = 0;
	while (current != NULL)
	{
		if (current->type != 124)
		{
			current = current->next;
			(*count)++;
		}
		else
		{
			current = current->next;
			break ;
		}
	}
	return (current);
}

void	ft_handler_dollar(t_list **tmp, t_command *cmd, char **env, char **join)
{
	char	*tmps1;
	char	*tmps;
	int		t;

	tmps1 = NULL;
	t = 0;
	if ((*tmp)->next)
		t = 1;
	if (((*tmp)->str && (*tmp)->str[1] != '\0' && (*tmp)->str[1] != '0' && (*tmp)->str[1] != '?')
		|| (t && (*tmp)->next->type == double_quo))
	{
		tmps = (*tmp)->str;
		tmps1 = expander(ft_strdup(tmps), env);
		if (tmps1)
			*join = ft_strjoin_n(*join, tmps1);
	}
	else if ((*tmp)->str[1] == '\0' && t && (*tmp)->next->type != double_quo)
		*join = ft_strjoin_n(*join, (*tmp)->str);
	else if ((*tmp)->str[1] == '?')
		*join = ft_strjoin_n(*join, ft_itoa(g_status));
	else if ((*tmp)->str[1] == '0')
		*join = ft_strjoin_n(*join, "minishell");
}

int	fill_arg(t_list **tmp, t_command *cmd, int *j, char **env, char **join)
{
	if ((*tmp)->type == -1 && !cherche_symbol((*tmp)->str[0], " \t\n\v\f\r"))
		*join = ft_strjoin_n(*join, (*tmp)->str);
	else if ((*tmp)->type == single_quo)
	{
		(*tmp)->str = remove_single_quote((*tmp)->str);
		*join = ft_strjoin_n(*join, (*tmp)->str);
	}
	else if ((*tmp)->type == double_quo)
	{
		(*tmp)->str = remove_double_quote((*tmp)->str, env);
		*join = ft_strjoin_n(*join, (*tmp)->str);
	}
	else if ((*tmp)->type == dollar)
		ft_handler_dollar(tmp, cmd, env, join);
	else if ((*tmp)->type == redirect_in || (*tmp)->type == redirect_out)
		ft_lstadd_back1(&cmd->redirect, fill_riderect((*tmp)->str, tmp, env));
	else if ((cherche_symbol((*tmp)->str[0], " \t\n\v\f\r")
			|| (*tmp)->type == char_null) && *join)
	{
		cmd->cmd[(*j)++] = *join;
		*join = NULL;
		return (1);
	}
	return (0);
}

void	fill_cmd(t_command *cmd, char **env, int nbr_args, t_list *tmp)
{
	int		j;
	t_list	*next;
	char	*join;

	j = 0;
	join = NULL;
	cmd->cmd = (char **)malloc(sizeof(char *) * (nbr_args + 1));
	cmd->redirect = NULL;
	while (tmp != NULL)
	{
		if (tmp->type != 124)
		{
			if (fill_arg(&tmp, cmd, &j, env, &join))
				join = NULL;
		}
		else
		{
			cmd->cmd[j++] = join;
			join = NULL;
			break ;
		}
		tmp = tmp->next;
	}
	free (join);
	cmd->cmd[j] = 0;
}

void	affich(int nbr_cmds, t_command *cmd)
{
	int				i;
	int				j;
	t_redirection	*head1;

	i = 0;
	j = 0;
	while (i < nbr_cmds)
	{
		j = 0;
		printf("\nthe caommande number %d\n", i + 1);
		while (cmd[i].cmd[j])
		{
			printf("%s ", cmd[i].cmd[j]);
			j++;
		}
		head1 = cmd[i].redirect;
		printf("\nlist of redirections\n");
		while (head1 != NULL)
		{
			printf("%s ------------> type : %d \n", head1->file, head1->type);
			head1 = head1->next;
		}
		i++;
	}
}

void	deleteredir(t_redirection **head_ref)
{
	t_redirection	*current;
	t_redirection	*next;

	current = *head_ref;
	while (current)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

void	free_all(t_command *cmd)
{
	int			i;
	int			j;
	t_command	*ptr;
	int			nbr;

	i = 0;
	nbr = cmd[0].num_cmds;
	while (i < nbr)
	{
		j = 0;
		while (cmd[i].cmd[j])
		{
			free(cmd[i].cmd[j]);
			j++;
		}
		if (cmd[i].redirect)
			deleteredir(&cmd[i].redirect);
		free(cmd[i].cmd);
		i++;
	}
	free(cmd);
}

t_command	*ft_parser(t_list **head, char *line, char **env)
{
	t_list		*current;
	t_list		*tmp;
	t_command	*cmd;
	int			i;
	int			nbr_args;

	i = -1;
	nbr_args = 0;
	current = *head;
	cmd = (t_command *)malloc(sizeof(t_command) * count_commads(head));
	while (++i < count_commads(head))
	{
		cmd[i].num_cmds = count_commads(head);
		tmp = current;
		current = ft_count_args(current, &nbr_args);
		if (nbr_args)
			fill_cmd(cmd + i, env, nbr_args, tmp);
	}
	//printf("the count command %d\n",)
	//affich(count_commads(head),cmd);
	return (cmd);
}
