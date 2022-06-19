#include "../../includes/minishell.h"

// char	*ft_strstr(char *str, char *to_find)
// {
// 	int	i;
// 	int	j;

// 	if (*to_find == '\0')
// 		return (str);
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == *to_find)
// 		{
// 			j = 0;
// 			while (str[i + j] == to_find[j] && to_find[j])
// 				j++;
// 			if (to_find[j] == '\0')
// 				return (&str[i]);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }


// char *find_commande(char *cmd, char **envp)
// {
//     int     i;
// 	int		j;
//     char    **paths;
//     char	*part_path;
//     char	*path;
// 	char	**split;
//     i = 0;
// 	split = ft_split(cmd, '/');
// 	while (split[j])
// 		j++;
// 	cmd = split[j - 1];
//     while (!ft_strstr(envp[i], "PATH"))
//         i++;
//     paths = ft_split(envp[i] + 5, ':');
//     i = 0;
//     while (paths[i])
// 	{
//         part_path = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(part_path, cmd);
//         if (access(path, F_OK) == 0)
// 			return (path);
//         i++;
//     }
//     return (NULL);
// }