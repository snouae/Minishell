// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_heredoc.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/22 15:24:31 by aoumad            #+#    #+#             */
// /*   Updated: 2022/06/22 17:00:37 by aoumad           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"

/*int delimiter_check(char *line, char *eof)
{
    int delim_len;
    
    delim_len = ft_strlen(line);
    if (!ft_strncmp(eof, line, delim_len) && line)
            return (0);
    return (1);
*/

char *handl_herdoc(char *str)
{
    char    *new;
    int        leng;
    int        j;
    int        start;
    char    *tmp;

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


/*int  multiple_heredoc(t_command *data, int i, int rtn_value)
{
    t_redirection   *head;
    char            *line;
    int             pipe_heredoc[2];
    
    head = data[i].redirect;
    if (pipe(pipe_heredoc));
        return (1)
}*/

int    ft_heredoc(t_command *data, int index, char *eof)
{
    char    *line;
    int     rtn_value;
    int     pipe_heredoc[2];

    if (pipe(pipe_heredoc) != 0)
        return (rtn_value);
    rtn_value = pipe_heredoc[0];
    line  = ft_strdup("");
    while (ft_strcmp(eof, line))
    {
        
        line = readline("> ");
        if (line == NULL)
            break;
        if (!ft_strcmp(eof, line))
            break;
        if (line_empty(line))
        {
            free(line);
            write(pipe_heredoc[1], "\n", 1);
            continue;
        }
        if (ft_strlen(line))
        {
            line = handl_herdoc(line);
            write(pipe_heredoc[1], line, ft_strlen(line));
            write(pipe_heredoc[1], "\n", 1);
        }
        // close(pipe_heredoc[0]);
        free(line);
    }    //else 
    close(pipe_heredoc[1]);
    //   rtn_value = multiple_heredoc(data, index, rtn_value);
    return (rtn_value);
}