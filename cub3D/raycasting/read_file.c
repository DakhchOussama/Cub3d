#include "main.h"

char	*red_line(int fd)
{
	char	*buff;
	char	*line;
	int		n;

	buff = (char *)malloc(sizeof(char) + 2);
	while (1)
	{
		n = read(fd, buff, 1);
		if (n == 0)
		{
			free(buff);
			return (line);
		}
		buff[1] = 0;
		if (buff[0] == '\n')
		{
			line = ft_strjoin(line, buff);
			free(buff);
			return (line);
		}
		line = ft_strjoin(line, buff);
	}
	free(buff);
	return (line);
}

char	*read_file(int fd)
{
	char			*buf;
	static char		*res;
	int				n;

	buf = (char *)malloc(sizeof(char) + 2);
	if (!buf)
		return (NULL);
	if (res == NULL)
		res = ft_strdup("");
	n = 1;
	while (n != 0)
	{
		n = read(fd, buf, 1);
		if (n == -1)
		{
			free(buf);
			free(res);
			return (NULL);
		}
		buf[n] = '\0';
		res = ft_strjoin(res, buf);
	}
	free(buf);
	return (res);
}
