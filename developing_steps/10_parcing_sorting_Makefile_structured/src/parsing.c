#include "push_swap.h"

// Returns the length of a string
size_t	ft_strlen(const char *s)
{
	size_t	i = 0;

	while (s[i])
		i++;
	return (i);
}

// Prints a string to the given file descriptor
void	ft_putstr_fd(const char *s, int fd)
{
	if (!*s)
		return ;
	write(fd, s, ft_strlen(s));
}

// Checks if a character is a digit
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// Checks if the value is within the int range
int	is_within_int_range(char *arg)
{
	long value = strtol(arg, NULL, 10);
	return (value >= INT_MIN && value <= INT_MAX);
}

// Checks if the argument is numeric
int	is_numeric_argument(char *arg)
{
	int j = 0;

	if (arg == NULL || arg[0] == '\0')
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}

	while (arg[j] == ' ' || (arg[j] >= 9 && arg[j] <= 13))
		j++;

	if (arg[j] == '-' || arg[j] == '+')
	{
		if (arg[j + 1] == '\0' || arg[j + 1] == ' ' || (arg[j + 1] >= 9 && arg[j + 1] <= 13))
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		j++;
	}

	if (arg[j] == '\0' || !ft_isdigit(arg[j]))
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}

	while (arg[j] != '\0')
	{
		if (arg[j] == ' ' || (arg[j] >= 9 && arg[j] <= 13))
		{
			j++;
			continue;
		}
		if (!ft_isdigit(arg[j]))
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		j++;
	}

	if (!is_within_int_range(arg))
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	return (1);
}

// Converts a string to an integer
int	ft_atoi(const char *str)
{
	int  result = 0;
	int  sign = 1;

	while (*str <= 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str++ - 48;
	}
	return (result * sign);
}

// Copies string s2 to s1, limiting the number of copied characters
char *ft_strcpy(char *s1, char *s2, int ammount)
{
	int i = -1;
	while (++i < ammount && s2[i])
	{
		s1[i] = s2[i];
	}
	s1[i] = '\0';
	return s1;
}

// Creates a new node
t_node *create_node(int value)
{
	t_node *new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return NULL;
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

// Checks for duplicates in the list
int	is_duplicate(t_node *head_a, int value)
{
	while (head_a)
	{
		if (head_a->value == value)
			return (1); // Duplicate found
		head_a = head_a->next;
	}
	return (0); // No duplicates found
}

// Adds a value to the list
void add_value_to_list(t_node **head_a, t_node **tail_a, int value)
{
	if (is_duplicate(*head_a, value))
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}

	t_node *new_node = create_node(value);
	if (!new_node)
		return;

	if (!*head_a)
	{
		*head_a = new_node;
		*tail_a = new_node;
	}
	else
	{
		(*tail_a)->next = new_node;
		new_node->prev = *tail_a;
		*tail_a = new_node;
	}
}

// Splits the string and adds numbers to the list
void ft_split_and_convert(char *str, t_node **head_a, t_node **tail_a)
{
	int i = 0;
	int w_begin = 0;

	while (str[i])
	{
		while (str[i] <= 32 && str[i] != '\0') 
			i++;

		if (str[i] == '\0')
			break;

		w_begin = i;
		while (str[i] > 32 && str[i] != '\0') 
			i++;

		if (i > w_begin)
		{
			int len = i - w_begin;
			char *word = (char *)malloc(sizeof(char) * (len + 1));
			if (word)
			{
				ft_strcpy(word, &str[w_begin], len);
				if (is_numeric_argument(word))
				{
					int value = ft_atoi(word);
					add_value_to_list(head_a, tail_a, value);
				}
				free(word);
			}
		}
	}
}

// Frees the memory allocated for the list
void free_list(t_node *head_a)
{
	t_node *current = head_a;
	while (current)
	{
		t_node *next = current->next;
		free(current);
		current = next;
	}
}
