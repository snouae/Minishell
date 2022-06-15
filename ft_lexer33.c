#include "minishell.h"

int search_token(char token)
{
    if (token ==  ' ')
        return white_space;
    else if (token == '\n')
        return new_lin;
    else if (token == '\t')
        return (tab);
    else if ( token == '|')
        return (pipe_token);
    else if (token == '>')
        return (redirect_out);
    else if (token ==  '<')
        return (redirect_in);
    else if (token == '$')
        return (dollar);
    else if (token == '\'')
        return (single_quo);
    else if (token == '\"')
        return (double_quo);
    else if (token == '\0')
        return (char_null);
    else
        return (-1);
}

void deleteList(t_list** head_ref)
{
   t_list *current = *head_ref;
   t_list *next;
  
   while (current) 
   {
       next = current->next;
       free(current);
       current = next;
   }
   *head_ref = NULL;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

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

void ft_lexer(char *line , char **env)
{
    int i;
    t_list *head , *tmp, *next;
    int start;

    start = 0;
    i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int d = 0;
    head = NULL;
    while (line[i])
    {
        if (search_token(line[i]) == -1 || (search_token(line[i]) == dollar && search_token(line[i + 1]) == dollar))
        {
            start = i;
            if(search_token(line[i]) == dollar && search_token(line[i + 1]) == dollar)
            {
                i = i + 2;
                i--;
                ft_lstadd_back(&head, ft_add(line, start, i, -1));
            }
            else if(search_token(line[i]) != dollar)
            {
                while (search_token(line[i]) == -1)
                    i++;
            i--;
            ft_lstadd_back(&head, ft_add(line, start, i, -1));
            }
        
         
        }
        // else if (search_token(line[i]) == white_space)
        // {
        //     start = i;
        //     while (search_token(line[i]) == white_space)
        //         i++;
        //     i--;
        // }
        else if (search_token(line[i]) == new_lin)
        {
            start = i;
            while (search_token(line[i]) == new_lin)
                i++;
            i--;
       ft_lstadd_back(&head, ft_add(line, start, i, new_lin));
        }
         else if (search_token(line[i]) == pipe_token)
        {
            start = i;
            while (search_token(line[i]) ==pipe_token)
                i++;     
            i--;
         ft_lstadd_back(&head, ft_add(line, start, i, pipe_token));
        }
         else if (search_token(line[i]) == redirect_out)
        {
            start = i;
            while (search_token(line[i]) == redirect_out)
                i++;
            while (search_token(line[i]) == ' ')
                i++;
            while (search_token(line[i]) == -1)
                i++;
            i--;
             ft_lstadd_back(&head, ft_add(line, start, i, redirect_out));
        }
         else if (search_token(line[i]) == redirect_in)
        {
            start = i;
            while (search_token(line[i]) == redirect_in)
                i++;
            while (search_token(line[i]) == ' ')
                i++;
            while (search_token(line[i]) == -1)
                i++;
            i--;
             ft_lstadd_back(&head, ft_add(line, start, i, redirect_in));
        }
         else if (search_token(line[i]) == double_quo)
        {
            start = i;
            // while (search_token(line[i]) == double_quo)
            //     i++;
            // i--;
            k = i + 1;
            l = i + 1;
            int test = 0;
            while (search_token(line[l]))
            {
                if (search_token(line[l]) == double_quo)
                {
                    test = 1; 
                    break ;
                }
                l++;
            }
        if (test == 1)
        {
            while (search_token(line[k]))
            {
                if (search_token(line[k]) == double_quo)
                {
                    i = k;
                    break ;
                }
                k++;
            }
        }
             ft_lstadd_back(&head, ft_add(line, start , i, double_quo));  
        }
         else if (search_token(line[i]) == dollar)
        {
            start = i;
            while (search_token(line[i]) == dollar)
                i++;
            while (search_token(line[i]) == -1)
                i++;  
            i--;
             ft_lstadd_back(&head, ft_add(line, start, i, dollar));
        }
         else if (search_token(line[i]) == single_quo)
        {
            start = i;
            while (search_token(line[i]) == single_quo)
                i++;
            i--;
            k = i + 1;
            l = i + 1;
            int test = 0;
            while (search_token(line[l]))
            {
                if (search_token(line[l]) == single_quo)
                {
                    test = 1; 
                    break ;
                }
                l++;
            }
        if (test == 1)
        {
            while (search_token(line[k]))
            {
                if (search_token(line[k]) == single_quo)
                {
                    i = k;
                    break ;
                }
                k++;
            }
        }
            ft_lstadd_back(&head, ft_add(line, start, i, single_quo));
        }
         else if (search_token(line[i]) == char_null)
        {
            start = i;
            while (search_token(line[i]) == char_null)
                i++;
            i--;
            ft_lstadd_back(&head, ft_add(line, start, i, char_null));
        }
   
        i++;
    }
    //serach_dollar(&head, env);
    tmp = head;
    while(tmp != NULL)
    {
        printf("the list : %s -------> type : %d \n", tmp->str, tmp->type);
        tmp = tmp->next;
    }
    ft_check(&head,line);
    // tmp = head;
    // int test = 1;
    //  while (tmp != NULL) 
    // {
    //    if (tmp->type == -1 && test)
    //    {
    //         if (!find_commande(tmp->str, env))
    //         {
    //             printf("Minishell: command not found: %s", tmp->str);
    //             exit(0);
    //         }
    //      test = 0;
    //    }
    //    else if (tmp->type == 124 && !test)
    //      test = 1;
    //  next = tmp->next; 
    //  tmp = next;
    // }
    
    ft_parser(&head,line,env);
   //deleteList(&head);
    //head = NULL;
   // head = NULL;
}