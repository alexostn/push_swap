#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

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

// Parsing functions
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(const char *s, int fd);
int	ft_isdigit(int c);
int	is_within_int_range(char *arg);
int	is_numeric_argument(char *arg);
int	ft_atoi(const char *str);
char *ft_strcpy(char *s1, char *s2, int ammount);
t_node *create_node(int value);
void add_value_to_list(t_node **head_a, t_node **tail_a, int value);
void ft_split_and_convert(char *str, t_node **head_a, t_node **tail_a);
void free_list(t_node *head_a);

// Sorting functions
int is_list_sorted(t_node *head);
void push_to_b(t_node **head_a, t_node **tail_a, t_node **head_b, t_node **tail_b);

#endif
