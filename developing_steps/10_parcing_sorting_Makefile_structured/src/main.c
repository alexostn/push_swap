#include "push_swap.h"

void print_list(t_node *head, const char *list_name)
{
	t_node *current = head;
	int index = 1;

	ft_putstr_fd(list_name, 1);
	ft_putstr_fd(":\n", 1);
	while (current)
	{
		printf("Node %d: %d\n", index++, current->value);
		current = current->next;
	}
	ft_putstr_fd("\n", 1);
}

int main(int ac, char **av)
{
	if (ac > 1)
	{
		t_node *head_a = NULL;
		t_node *tail_a = NULL;
		t_node *head_b = NULL;
		t_node *tail_b = NULL;

		for (int i = 1; i < ac; i++)
		{
			ft_split_and_convert(av[i], &head_a, &tail_a);
		}

		if (is_list_sorted(head_a))
		{
			ft_putstr_fd("List is already sorted\n", 1); // Delete this line after!!!
			free_list(head_a);
			return (0);
		}

		// Example call: moving the top element from list A to B
		push_to_b(&head_a, &tail_a, &head_b, &tail_b);

		// Print lists A and B after the operation
		print_list(head_a, "List A");
		print_list(head_b, "List B");

		free_list(head_a);
		free_list(head_b);
	}
	return (0);
}
