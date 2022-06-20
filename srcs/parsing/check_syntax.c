#include "../../includes/minishell.h"

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

int check_pipe(char *str, t_list **current)
{
    int i;
    int c;

    c = 0;
    i = 0;
    (*current) = (*current)->next;
    while (cherche_symbol((*current)->str[0], " \t\n\v\f\r") && (*current) != NULL)
        (*current) = (*current)->next; 
    
    while (str[i])
    {
        if (str[i] == pipe_token)
            c++;
    i++;
    }
    if (c != 1 || (*current)->type == pipe_token || (*current) != NULL)
        return (0);
    return (1);
}

int check_red(char *str, t_list *nx)
{
    int i;
    int c;
    int w;

    i = 0;
    c = 0;
    w = 0;

     while (((str[i] == redirect_in || str[i] == redirect_out)))
     {
         c++;
         i++;
     }
    while (str[i] && cherche_symbol(str[i], " \t\n\v\f\r"))
        i++;
    if ((str[i] == '\0' && nx && (nx->type != dollar 
    && nx->type != double_quo && nx->type != single_quo)) || c > 2 
    || (ft_strlen(str) == c && nx && (nx->type != dollar 
    && nx->type != double_quo && nx->type != single_quo)))
        return (0);
    return (1);
}

int ft_check(t_list** head, char *line)
{
   t_list *current;

   current = *head;
    while (current != NULL) 
   {
        if (current->type == double_quo)
        {
           if (!check_double_quote(current->str))
                return (0);
        }
        else if (current->type == single_quo)
        {
           if (!check_quote(current->str))
                return (0);
        }
        else if (current->type == pipe_token)
        {
           if (!check_pipe(current->str, &current))
                return (0);
        }
        else if ((current->type == redirect_in) || (current->type == redirect_out))
        {
           if (!check_red(current->str, current->next))
                return (0);
        }
        current = current->next; 
   }
   return (1);
}
