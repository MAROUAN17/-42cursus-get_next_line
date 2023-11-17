#include "get_next_line.h"


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*p;

	i = 0;
	p = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!p)
		return (0);
	while (i < ft_strlen(s1) + 1)
	{
		p[i] = s1[i];
		i++;
	}
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	z;
	char	*str1;
	char	*str2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	z = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	while (i < ft_strlen(s1))
		p[i++] = str1[z++];
	z = 0;
	while (i < ft_strlen(s1) + ft_strlen(s2))
		p[i++] = str2[z++];
	p[i] = '\0';
	return (p);
}

size_t	ft_strlcpy(char *dst, const char *src, 
			size_t dstsize)
{
	size_t	i;
	char	*dest;
	char	*sr;

	i = 0;
	dest = (char *)dst;
	sr = (char *)src;
	while (i < dstsize - 1 && sr[i] && dstsize != 0)
	{
		dest[i] = sr[i];
		i++;
	}
	if (dstsize != 0)
		dest[i] = '\0';
	i = 0;
	while (sr[i])
		i++;
	return (i);
}
