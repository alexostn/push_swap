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

	while (arg[j] == ' ' || (arg[j] >= 9 && arg[j] <= 13)) // Skip initial whitespace
		j++;

	if (arg[j] == '-' || arg[j] == '+') // Check for a sign
	{
		if (arg[j + 1] == '\0' || arg[j + 1] == ' ' || (arg[j + 1] >= 9 && arg[j + 1] <= 13)) // Ensure sign is not alone
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		j++;
	}

	if (arg[j] == '\0' || !ft_isdigit(arg[j])) // Ensure that there are digits after the sign
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}

	while (arg[j] != '\0')
	{
		if (arg[j] == ' ' || (arg[j] >= 9 && arg[j] <= 13)) // Skip internal whitespace
		{
			j++;
			continue;
		}
		if (!ft_isdigit(arg[j])) // Check for non-digit characters
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		j++;
	}
	// Range check
	if (!is_within_int_range(arg))
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	return (1);
}


int	ft_atoi(const char *str)
{
	int  result = 0;
	int  sign = 1;

	while (*str <= 32) // Skip tabs in ASCII
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+') // Only processed once, hence 'if'
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str++ - 48;
	}
	return (result * sign);
}

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

// Add words to the general list
void add_value_to_list(t_node **head, t_node **tail, int value)
{
	t_node *new_node = create_node(value);
	if (!new_node)
	{
		// Handle memory allocation failure
		return;
	}
    
	// If the list is empty, initialize it
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		// Attach the new node to the list
		(*tail)->next = new_node;
		new_node->prev = *tail;
		*tail = new_node;
	}
}

void ft_split_and_convert(char *str, t_node **head, t_node **tail)
{
	int i = 0;
	int w_begin = 0;

	while (str[i])
	{
		// Skip leading spaces
		while (str[i] <= 32 && str[i] != '\0') 
			i++;

		if (str[i] == '\0') // Exit if the end of the string is reached after skipping spaces
			break;

		w_begin = i;
		while (str[i] > 32 && str[i] != '\0') // Find the end of the word
			i++;

		if (i > w_begin)
		{
			int len = i - w_begin;
			char *word = (char *)malloc(sizeof(char) * (len + 1));
			if (word)
			{
				ft_strcpy(word, &str[w_begin], len);
				if (is_numeric_argument(word)) // Check if the argument is a valid number
				{
					int value = ft_atoi(word); // Convert the string to an integer
					add_value_to_list(head, tail, value); // Add the integer to the list
				}
				free(word); // Free memory allocated for word
			}
		}
	}
}

void free_list(t_node *head)
{
	t_node *current = head;
	while (current)
	{
		t_node *next = current->next;
		free(current); // Free the node
		current = next;
	}
}

int main(int ac, char **av)
{
	if (ac > 1)
	{
		t_node *head = NULL;
		t_node *tail = NULL;
		for (int i = 1; i < ac; i++) // Iterate over arguments
		{
			ft_split_and_convert(av[i], &head, &tail); // Use the new function to process arguments
		}

		// Iterate over the combined list and print each value
		t_node *current = head;
		int index = 1;
		while (current)
		{
			printf("Node %d: %d\n", index++, current->value); // Print the integer value
			current = current->next;
		}

		// Free memory allocated for the combined list
		free_list(head);
	}
	return (0);
}
