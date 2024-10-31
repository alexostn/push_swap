#include "push_swap.h"

// Checks if the list is sorted
int is_list_sorted(t_node *head)
{
	t_node *current = head;

	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0); // Not in order
		current = current->next;
	}
	return (1); // Order maintained
}

// Moves the top element from list A to B
void push_to_b(t_node **head_a, t_node **tail_a, t_node **head_b, t_node **tail_b)
{
	(void)tail_a; // Ignoring the parameter
	if (*head_a == NULL)
		return; // If list A is empty, do nothing

	t_node *node_to_move = *head_a;
	*head_a = node_to_move->next; 
	if (*head_a)
		(*head_a)->prev = NULL;

	if (*head_b == NULL) // If B is empty
	{
		*head_b = node_to_move; 
		*tail_b = node_to_move;
		node_to_move->next = NULL;
		node_to_move->prev = NULL;
	}
	else // If B is not empty
	{
		(*tail_b)->next = node_to_move; 
		node_to_move->prev = *tail_b;
		node_to_move->next = NULL;
		*tail_b = node_to_move; 
	}
}
