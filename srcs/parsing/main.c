/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:18:29 by snouae            #+#    #+#             */
/*   Updated: 2022/06/29 19:30:31 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**rtn_env;
	int		index;

	i = -1;
	index = 0;
	while (envp[++i])
		index++;
	rtn_env = malloc(sizeof(char *) * (index + 1));
	if (!rtn_env)
		ft_error_malloc("minishell", NULL, strerror(ENOMEM));
	i = 0;
	while (i < index)
	{
		rtn_env[i] = ft_strdup(envp[i]);
		i++;
	}
	rtn_env[i] = NULL;
	return (rtn_env);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

int	ft_check(t_list **head, char *line)
{
	t_list	*current;

	current = *head;
	while (current != NULL)
	{
		if (!check_cases(&current))
			return (0);
		current = current->next;
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	int			test;
	t_list		*head;
	char		*buffer;
	t_command	*cmd;

	cmd = NULL;
	(void)ac;
	(void)av;
	g_env = copy_env(envp);
	while (1)
	{
		test = 0;
		st_err = 0;
		rl_catch_signals = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		rl_on_new_line();
		buffer = readline("\033[1mminishell$> \033[m");
		if (!buffer)
			break ;
		if (line_empty(buffer))
		{
			free(buffer);
			continue ;
		}
		if (ft_strlen(buffer))
		{
			add_history (buffer);
			head = ft_lexer(buffer, envp);
			if (!ft_check(&head, buffer))
			{
				printf("minishell: syntax error\n");
				free(buffer);
				deletelist(&head);
				test = 1;
				continue ;
			}
			cmd = ft_parser(&head, buffer, g_env);
			open_files(cmd, cmd[0].num_cmds);
			if (st_err)
				continue ;
			execute_root(cmd, g_env);
		}
		if (!test)
			deletelist(&head);
		free_all(cmd);
		free(buffer);
	}
	ft_free_env(&g_env);
	return (0);
}
