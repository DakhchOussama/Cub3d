/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:04:17 by mouarsas          #+#    #+#             */
/*   Updated: 2022/11/28 23:02:51 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	unsigned char *arr1;
	unsigned char *arr2;

	i = 0;
	arr1 = (unsigned char *)s1;
	arr2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (arr1[i] && arr2[i] && arr1[i] == arr2[i] && i < n - 1)
		i++;
	return (arr1[i] - arr2[i]);
}
