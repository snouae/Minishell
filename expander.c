#include "minishell.h"

char *fill_array(char *line, int start, int end)
{
    char    *str;
    int     i;
    int     j;
    
    i = 0;
    j = start;
    end++;
    str =  (char *)malloc(sizeof(char) * (end - start) + 1);
    while (j < end)
    {
        str[i] = line[j];
        i++;
        j++;
    }
    str[i] = '\0';
	return (str);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	if (*to_find == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && i < n)
	{
		if (str[i] == *to_find)
		{
			j = 0;
			while (str[i + j] == to_find[j] && i + j < n
				&& str[i + j] && to_find[j])
				j++;
			if (to_find[j] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}

char *expander(char *var, char **envp)
{
    int i;
    char *content;
    int leng;

    i = 0;
    leng = 0;
    leng = ft_strlen(var);
    if(leng == 1 && var[0] == '$')
        return (NULL);
    var[leng] = '=';
    var[leng + 1] = '\0';
    while (envp[i] && !ft_strnstr(envp[i], var + 1, ft_strlen(var)))
        i++;
    if(envp[i] && ft_strnstr(envp[i], var + 1, ft_strlen(var)))
    {
        content = envp[i] + ft_strlen(var + 1);
        return (content);
    }
    return (NULL);
}