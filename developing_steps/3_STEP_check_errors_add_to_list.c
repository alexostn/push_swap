#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h> // Добавлено: для функции write

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

//CHECK INDEPENDANT AV
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

while (*str <= 32)// tabs skip in ASCII
  str++;
if (*str == '-')
  sign = -1;
if (*str == '-' || *str == '+')//only one time, that's why 'if'
  str++;
while (*str >= '0' && *str <= '9')
	{
	result = result * 10 + *str++ - 48;
		// Overflow check
	// if (result * sign > INT_MAX)
	// 	return INT_MAX;
	// if (result * sign < INT_MIN)
	// 	return INT_MIN;
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

// Изменяем ft_split, чтобы добавлять слова в общий список
void add_value_to_list(t_node **head, t_node **tail, int value)
{
    t_node *new_node = create_node(value);
    if (!new_node)
    {
        // Обработка ошибки выделения памяти
        return;
    }
    
    // Если список пуст, инициализируем его
    if (!*head)
    {
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        // Присоединяем новый узел к списку
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
		// Пропускаем пробелы
		while (str[i] <= 32 && str[i] != '\0') 
			i++;

		if (str[i] == '\0') // Если достигли конца строки после пробелов, выходим
			break;

		w_begin = i; // Начало слова
		while (str[i] > 32 && str[i] != '\0') // Находим конец слова
			i++;

		if (i > w_begin) // Если нашли слово
		{
			int len = i - w_begin;
			char *word = (char *)malloc(sizeof(char) * (len + 1));
			if (word)
			{
				ft_strcpy(word, &str[w_begin], len);
				if (is_numeric_argument(word)) // Проверяем, является ли аргумент числом
				{
					int value = ft_atoi(word); // Конвертируем строку в целое число
					add_value_to_list(head, tail, value); // Добавляем целое число в список
				}
				free(word); // Освобождаем память, выделенную для word
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
        free(current); // Освобождение узла
        current = next;
    }
}

int main(int ac, char **av)
{
    if (ac > 1)
    {
        t_node *head = NULL;
        t_node *tail = NULL;
        for (int i = 1; i < ac; i++) // Перебираем аргументы
        {
            ft_split_and_convert(av[i], &head, &tail); // Изменено: используем новую функцию для обработки аргументов
        }

        // Итерация по объединенному списку и печать каждого значения
        t_node *current = head;
        int index = 1;
        while (current)
        {
            printf("Node %d: %d\n", index++, current->value); // Изменено: печатаем целое число
            current = current->next;
        }

        // Освобождение памяти, выделенной для общего списка
        free_list(head);
    }
    return (0);
}
