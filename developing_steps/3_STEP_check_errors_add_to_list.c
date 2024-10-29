#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

typedef struct s_node
{
	int value;
	struct s_node *next;
	struct s_node *prev;
} t_node;

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!*s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_within_int_range(char *arg)
{
	long value = strtol(arg, NULL, 10);
	return (value >= INT_MIN && value <= INT_MAX);
}

int	is_numeric_argument(char *arg)
{
	int j = 0;

	if (arg == NULL || arg[0] == '\0') // Ensure the string is not empty
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}

	while (arg[j] == ' ' || (arg[j] >= 9 && arg[j] <= 13
