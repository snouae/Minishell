#include "minishell.h"

int check_double_quote(char *str)
{
    int i;
    int c;

    c = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == double_quo)
            c++;
    i++;
    }
    if (c != 2)
        return (0);
    return (1);
}

int check_quote(char *str)
{
    int i;
    int c;

    c = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == single_quo)
            c++;
    i++;
    }
    if (c != 2)
        return (0);
    return (1);
}

int check_pipe(char *str, int j, t_list** head, t_list *n)
{
    int i;
    int c;
    t_list *current = *head;
    t_list *next;

    c = 0;
    i = 0;
    while (current->next != NULL)
    {
        next = current->next; 
        current = next;
    }
    if (!j || current->type == pipe_token || n->type == pipe_token)
        return (0);
    while (str[i])
    {
        if (str[i] == pipe_token)
            c++;
    i++;
    }
    if (c != 1)
        return (0);
    return (1);
}

void ft_check(t_list** head, char *line)
{
   t_list *current = *head;
   t_list *next, *tmp;
   int c = 0;
    while (current != NULL) 
   {
       if (current->type == double_quo)
       {
           if (!check_double_quote(current->str))
                {
                    printf("Minishell: syntax error");
                    exit (1);
                }
       }
        else if (current->type == single_quo)
       {
           if (!check_quote(current->str))
                {
                    printf("Minishell: syntax error");
                    exit (1);
                }
       }
        else if (current->type == pipe_token)
       {
           if (!check_pipe(current->str, c, head, current->next))
                {
                    printf("Minishell: syntax error");
                    exit (1);
                }
       }
        next = current->next; 
        current = next;
        c++;
   }
}
