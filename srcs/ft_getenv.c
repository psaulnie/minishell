/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:53:37 by psaulnie          #+#    #+#             */
/*   Updated: 2022/05/09 10:23:00 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static char	*get_custom_env_var(t_env env, char *name, char *returned_env)
// {
// 	while (env.addon_env != NULL)
// 	{
// 		name = ft_strjoin_gnl(name, "=");
// 		if (!name)
// 			return (NULL);
// 		if (ft_strnstr(env.addon_env->content, name, ft_strlen(name)))
// 		{
// 			returned_env = ft_strdup(ft_strnstr(env.addon_env->content,
// 						name, ft_strlen(name) + 1) + ft_strlen(name) + 1);
// 			if (!returned_env)
// 				return (NULL);
// 			break ;
// 		}
// 		env.addon_env = env.addon_env->next;
// 	}
// 	return (returned_env);
// }

// a retest
char	*ft_getenv(t_env env, char *name)
{
	char	*returned_env;

	// returned_env = get_custom_env_var(env, name, returned_env);
	returned_env = NULL;
	while (env.addon_env != NULL)
	{
		name = ft_strjoin_gnl(name, "=");
		if (!name)
			return (NULL);
		if (ft_strnstr(env.addon_env->content, name, ft_strlen(name)))
		{
			returned_env = ft_strdup(ft_strnstr(env.addon_env->content,
						name, ft_strlen(name) + 1) + ft_strlen(name) + 1);
			if (!returned_env)
				return (NULL);
			break ;
		}
		env.addon_env = env.addon_env->next;
	}
	return (returned_env);
}
