/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:52:59 by snouae            #+#    #+#             */
/*   Updated: 2022/05/27 14:53:08 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void	ft_lstadd_back1(t_redirection **lst, t_redirection *new)
{
	t_redirection	*list;

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

char *remove_double_quote(char *str, char **env)
{
   char *new = NULL;
   int leng;
   int i;
   int j;
   int here = 0;
   int start;
   char *dlr;
   char *tmp;

   i = 0;
   j = 1;
   leng = ft_strlen(str);
   tmp = (char *)malloc(sizeof(char) * 2);
   tmp[1] = '\0';
   while (j < leng - 1)
   {
       if(str[j] == dollar)
      {
         start = j;
         j++;
         while (str[j] != double_quo && str[j] != ' ' && str[j] && str[j] !=  dollar && search_token(str[j]) == -1)
            j++;
         j--;
         dlr = fill_array(str,start,j);
         dlr = expander(dlr,env);
         new = ft_strjoin(new,dlr);
      }
      else
      {
         tmp[0] = str[j];
         new = ft_strjoin(new,tmp);
      }
      j++;
   }

   return (new);
}

char *remove_single_quote(char *str)
{
   char *new;
   int leng;
   int i;

   i = 0;
   leng = ft_strlen(str);
   new = (char *)malloc(sizeof(char) * (leng - 2));

   while (i < leng - 2)
   {
      new[i] = str[i + 1];
      i++;
   }
   return (new);
}

t_redirection *fill_riderect(char *str, t_list *next, char **env)
{
   t_redirection *new;
   int test;
   char *sr;
   int i;
   i = 1;

   while(str[i] == tab)
      i++;
   test = 0;
   new = (t_redirection *)malloc(sizeof(t_redirection));
   if(next)
   {
      if(next->str[0] == dollar)
      {
         next->str = expander(next->str, env);
         new->file = ft_strjoin(ft_strdup(str + i), next->str);
         //printf("the new is %s\n",new->file);
         test = 1;
      }
      else if (next->str[0] == double_quo)
      {    
         next->str = remove_double_quote(next->str, env);
         new->file = ft_strjoin(ft_strdup(str + i),next->str);
         test = 1;
      }
      else if (next->str[0] == single_quo)
      {
         next->str = remove_single_quote(next->str);
         new->file = ft_strjoin(ft_strdup(str + i), next->str);
         test = 1;
      }
   }
   if(!test)
      new->file = ft_strdup(str + i);
   if(str[0] == '<' && str[1] == '<')
      new->type = HEREDOC;
   else if(str[0] == '>' && str[1] == '>')
      new->type = APPEND;
   else if (str[0] == '<')
      new->type = IN;
   else if (str[0] == '>')
      new->type = OUT;
   new->next = NULL;
   return (new);
}
void ft_parser(t_list** head, char *line , char **env)
{
   t_list *current = *head;
   t_list *next, *tmp;
   t_list *testl;
   t_command *cmd;
   t_redirection  *head1; 
   int      c;
   int      outf;
   int      inf;
   int      i;
   int      j;
   int     k;

   c = 1;
   k = 0;
   i = 0;
   j = 0;
   inf = 0;
   outf = 0;
   while (current != NULL) 
   {
       if (current->type == 124)
         c++;
         next = current->next; 
         current = next;
   }
   current = *head;
   cmd = (t_command *)malloc(sizeof(t_command) * (c + 1));
   while (i < c)
   {
      j = 0;
   tmp = current;
    while (current != NULL) 
    {
       if (current->type != 124)
       {
          if(current->type != redirect_in || current->type != redirect_out)
          {
            next = current->next; 
            current = next;
            j++;
          }
          else
          {
            next = current->next; 
            current = next;
          }
       }
       else
       {
         next = current->next; 
         current = next;
          break ;
       }
    }
   if (j)
   {
      k = 0;
      cmd[i].num_of_args = j;
      cmd[i].envp = (char **)malloc(sizeof(char *) * (j + 1));
      cmd[i].redirect = NULL;
      while (tmp != NULL)
      {
         if (tmp->type != 124)
         {
         if(tmp->type != redirect_in && tmp->type != redirect_out && tmp->type != double_quo && tmp->type != dollar)
          {
            cmd[i].envp[k] = tmp->str;
            next = tmp->next; 
            tmp = next;
            k++;
            }
         else if (tmp->type == double_quo)
         {
            cmd[i].envp[k] = remove_double_quote(tmp->str, env);
            next = tmp->next; 
            tmp = next;
            k++;
         }
         else if (tmp->type == dollar)
         {
           // printf("hellllllo\n");
           // printf("dsddf %s\n",tmp->str);
           if(tmp->str)
               cmd[i].envp[k] = expander(tmp->str, env);
            next = tmp->next; 
            tmp = next;
            k++;
         }
          else
          {
            cmd[i].envp[k] = NULL;
            ft_lstadd_back1(&cmd[i].redirect, fill_riderect(tmp->str, tmp->next, env));
            next = tmp->next;
            tmp = next;
          }
         }
         else
         {
            cmd[i].envp[k] = 0;
            break ;
         }
      }
      cmd[i].envp[k] = 0;
    }
    i++;
   }

   //  tmp = *head;
   //  int test = 1;
   //  i = 0;
   //   while (tmp != NULL) 
   //  {
   //     if (tmp->type == -1 && test)
   //     {
   //        cmd[i].executable = tmp->str;
   //       test = 0;
   //     }
   //     else if (tmp->type == 124)
   //     {
   //       test = 1;
   //       i++;
   //     }
   //   next = tmp->next; 
   //   tmp = next;
   //  }
   i = 0;
   j = 0;
   while (i < c)
   {
      j = 0;
      printf("\nthe caommande number %d\n",i + 1);
      while(cmd[i].envp[j])
      {
         printf("%s ",cmd[i].envp[j]);
         j++;
      }
      head1 = cmd[i].redirect;
      printf("\n list of redirections\n");
      while(head1 != NULL)
      {
         printf("%s ------------> type : %d \n",head1->file, head1->type);
         head1 = head1->next;
      }
      //printf("\n the executable is : %s\n",cmd[i].executable);
      i++;
   }
   open_files(cmd);
      // char *str1 = expander(cmd[0].envp[1], env);
      // if (str1)
      //    printf("the content is %s\n",str1);
      // else
      //    printf("\n");
}
