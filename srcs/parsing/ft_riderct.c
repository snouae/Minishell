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
                {
                    head->fd = open(head->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
                }
                else if (head->type == APPEND)
                    head->fd = open(head->file, O_WRONLY | O_APPEND | O_CREAT, 0664);
                // if (redirect->type == HEREDOC)
                //     fd = ft_heredoc() HEREDOC FUNCTION WITH INT TYPE, fd = ft_heredoc(...)
                if (head->fd < 0)
                {
                    //printf("minishell: ");
                    perror("minishell: ");
                }
                head = head->next;
            }
        }
        i++;
    }
}