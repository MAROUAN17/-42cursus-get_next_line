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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (src[i] && i < dstsize - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	if (dstsize < dst_len)
		return (dst_len + i);
	else
		return (dst_len + src_len);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;
	char			*p;

	i = 0;
	cc = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == cc)
		{
			p = (char *)s + i;
			while (s[i])
				i++;
			return (p);
		}
		else
			i++;
	}
	if (cc == '\0')
		return ((char *)s + i);
	return (0);
}
