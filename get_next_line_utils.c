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

	if (!s1)
		return (NULL);
	i = 0;
	p = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!p)	
		return (0);
	while (i < ft_strlen(s1) + 1)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
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
			return (p);
		}
		else
			i++;
	}
	if (cc == '\0')
		return ((char *)s + i);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
