#include "minishell.h"


int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}
void handler(int sig)
{
	if (sig ==  SIGINT)
	{
	    printf("\n");
        rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int line_empty(char *str)
{
	int i = -1;

	while (str[++i])
		if (str[i] != '\t'&& str[i] != '\v' && str[i] != '\f' &&
		str[i] != '\n' && str[i] != ' ' && str[i] != '\r' )
			return (0);
	return (1);
}
int main(int ac, char **av, char **env)
{
	int i;
	t_list *head;

	i = 0;
	(void)ac;
	(void)av;
	while(1)
	{
		
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		char *buffer = readline("Minishell> ");
		if (!buffer)
			return (write(2, "exit\n", 5), 0);
		if (line_empty(buffer))
		{
			free(buffer);
			continue;
		}
		if (!ft_strcmp(buffer, "exit"))
		{
			free (buffer);
			return (write(2, "exit\n", 5), 0);
		}
		if (ft_strlen(buffer))
		{
			add_history (buffer);
			head = ft_lexer(buffer,env);
			if(!ft_check(&head,buffer))
			{
				printf("minishell: syntax error\n");
				continue ;
			}
			ft_parser(&head,buffer,env);
		}

		free(buffer);
    }
    return 0;
}