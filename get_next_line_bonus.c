#include "get_next_line.h"
#include <unistd.h>
#include <limits.h>

char	*get_next_line(int fd)
{
	static char	perm_buf[OPEN_MAX][BUFFER_SIZE + 1];
	char		*temp_buf;
	int			read_status;
	char		*nl_ptr;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	nl_ptr = ft_strchr(perm_buf[fd], '\n');
	if (nl_ptr)
		return (return_line(perm_buf[fd], nl_ptr, perm_buf[fd], 's'));
	temp_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buf)
		return (free_buf(temp_buf, 'd', 0, 1));
	read_status = read(fd, temp_buf, BUFFER_SIZE);
	temp_buf = ft_strjoin(perm_buf[fd], temp_buf, "sd");
	if (read_status == 0 && !temp_buf[0])
		return (free_buf(temp_buf, 'd', 0, 1));
	nl_ptr = ft_strchr(temp_buf, '\n');
	return (read_further(nl_ptr, fd, perm_buf[fd], temp_buf));
}

char	*read_further(char *nl_ptr, int fd, char *perm_buf, char *buf)
{
	int	read_status;

	while (!nl_ptr)
	{
		read_status = read(fd, perm_buf, BUFFER_SIZE);
		if (read_status == 0)
			return (return_line(buf, nl_ptr, perm_buf, 'd'));
		buf = ft_strjoin(buf, perm_buf, "ds");
		nl_ptr = ft_strchr(buf, '\n');
		if (!buf[0] || read_status == -1)
			return (free_buf(buf, 'd', 0, 1));
	}
	return (return_line(buf, nl_ptr, perm_buf, 'd'));
}

char	*return_line(char *buf, char *nl_ptr, char *perm_space, char mem_type)
{
	char	*line;

	line = ft_substr(buf, nl_ptr);
	if (nl_ptr && *(nl_ptr + 1))
		ft_strlcpy(perm_space, nl_ptr + 1, BUFFER_SIZE + 1);
	else
		free_buf(perm_space, 's', 1, 0);
	if (mem_type == 'd')
		free_buf(buf, 'd', 0, 0);
	return (line);
}

char	*free_buf(char *buf, char mem_type, int reset_buf, int return_null)
{
	int	i;

	i = 0;
	while (buf[i] && reset_buf)
		buf[i++] = '\0';
	if (mem_type == 'd')
		free(buf);
	if (return_null)
		return (NULL);
	return ("");
}