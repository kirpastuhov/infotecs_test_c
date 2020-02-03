/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpastukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:23:16 by kpastukh          #+#    #+#             */
/*   Updated: 2019/11/18 19:23:20 by kpastukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!(new = (char *)ft_memalloc(len + 1)))
		return (NULL);
	while (i < len && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

