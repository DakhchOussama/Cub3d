/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 22:39:46 by mouarsas          #+#    #+#             */
/*   Updated: 2022/12/24 18:32:51 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char	*dst, const char *src, size_t size)
{
	size_t	i;
	size_t	compt;

	compt = 0;
	while (src[compt] != '\0')
	{
		++compt;
	}
	if (size == 0)
		return (compt);
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (compt);
}
