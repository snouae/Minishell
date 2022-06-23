/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:24:31 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/23 11:20:59 by snouae           ###   ########.fr       */
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

char *handl_herdoc(char *str)
{
    char	*new;
	int		leng;
	int		j;
	int		start;
	char	*tmp;

	j = -1;
	new = NULL;
	leng = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[1] = '\0';
	while (++j < leng)
	{
		if (str[j] == dollar
			&& !cherche_symbol(str[j + 1], "\t!$%'() *\"+,-./:;<=>?@[]^`{|}~"))
			new = check_dollar(&j, str, new, g_env);
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

int    ft_heredoc(t_command *data, int index, char *eof)
{
    char    *line;
    int     rtn_value;
    int     pipe_heredoc[2];

    rtn_value = dup(STDOUT_FILENO);
    if (pipe(pipe_heredoc) != 0)
        return (0);
    //if (data[index].redirect->next == NULL)
   // {
        while (1)
        {
            line = readline("> ");
            if (!line || !delimiter_check(line, eof))
                break;
            if (line_empty(line))
            {
                free(line);
                continue;
            }
            if (ft_strlen(line))
            {
                line = handl_herdoc(line);
                write(pipe_heredoc[1], line, ft_strlen(line));
                write(pipe_heredoc[1], "\n", 1);
            }
            //dup2(pipe_heredoc[0], STDIN_FILENO);
            //close(pipe_heredoc[0]);
            //close(pipe_heredoc[1]);
            free(line);
         }
    //}
    // else 
    //     rtn_value = multiple_heredoc();
    return (0);
}