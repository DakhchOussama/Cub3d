#include "main.h"

char	*ft_strdup(const char	*s1)
{
	char	*tab;
	size_t	i;
	size_t	length;

	length = ft_strlen(s1);
	tab = malloc(length + 1 * sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < length)
	{
		tab[i] = s1[i];
		++i;
	}
	tab[i] = '\0';
	return (tab);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*a;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (start >= length)
		return (ft_strdup(""));
	if (len + start > length)
		len = length - start;
	a = malloc(sizeof(char) * len + 1);
	if (a == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < len)
	{
		a[i] = s[start];
		i++;
		start++;
	}
	a[len] = '\0';
	return (a);
}