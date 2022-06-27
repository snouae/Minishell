#include "../../includes/minishell.h"

void open_files(t_command *cmd, int leng)
{
    int i;
    t_redirection *head;

    i = 0;
    while (i < leng)
    {
        if(cmd[i].redirect)
        {
            head = cmd[i].redirect;
            while (head != NULL)
            {
                if (head->type == IN)
                    head->fd = open(head->file, O_RDONLY);
                else if (head->type == OUT)
                    head->fd = open(head->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
                else if (head->type == APPEND)
                    head->fd = open(head->file, O_WRONLY | O_APPEND | O_CREAT, 0664);
                 else if (head->type == HEREDOC)
                    head->fd = ft_heredoc(cmd, i, head->file);
                 if (head->fd < 0 && head->status)
                 {
                    ft_error("minishell","$"," ambiguous redirect\n");
                    break ;
                 }
                else if (head->fd < 0 && !head->status && head->type != HEREDOC)
                {
                    perror("minishell: ");
                    g_status = 1;
                    break ;
                }
                else if (head->fd < 0 && head->type == HEREDOC)
                {
                    st_err = 1;
                    break ;
                }
                head = head->next;
            }
        }
        i++;
    }
}