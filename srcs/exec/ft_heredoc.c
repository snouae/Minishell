/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:24:31 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/22 19:02:46 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int delimiter_check(char *line, char *eof)
{
    int delim_len;
    
    delim_len = ft_strlen(line);
    if (!ft_strncmp(eof, line, delim_len) && line)
            return (0);
    return (1);
}

char *dollar_herdoc(char *str)
{
    char	*tmps1;
	char	*tmps;
    char    *join;

	tmps1 = NULL;
    join = NULL;
	if ((str && str[1] != '\0'))
	{
   // puts("her");
		tmps = str;
		tmps1 = expander(ft_strdup(tmps), g_env);
		if (tmps1)
			join = ft_strjoin_n(join, tmps1);
	}
	else if (str[1] == '\0')
		join = ft_strjoin_n(join, str);
    //printf("%s\n",join);
    return (join);
}

int    ft_heredoc(t_command *data, int index, char *eof)
{
    char    *line;
    int     rtn_value;
    int     pipe_heredoc[2];

    rtn_value = dup(STDOUT_FILENO);
    if (pipe(pipe_heredoc) != 0)
        return (0);
    if (data[index].redirect->next == NULL)
    {
        while (1)
        {
            line = readline("> ");
            if (line != NULL && !delimiter_check(line, eof))
                break;
            if (line == NULL)
                break;
            if (line[0] == '$')
                line = dollar_herdoc(line);
            write(pipe_heredoc[1], line, ft_strlen(line));
            write(pipe_heredoc[1], "\n", 1);
            free(line);
        }
        free(line);
        dup2(pipe_heredoc[0], STDIN_FILENO);
        close(pipe_heredoc[0]);
        close(pipe_heredoc[1]);
    }
    // else 
    //     rtn_value = multiple_heredoc();
    return (0);
}