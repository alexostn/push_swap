#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
	int value;
	struct s_node *next;
	struct s_node *prev;
} t_node;

t_node *find_closest_smaller(t_node *head, int a)
{
	t_node *current = head;
	t_node *closest = NULL;

	while (current != NULL)
	{
		if (current->value < a && (closest == NULL || current->value > closest->value))
		{
			closest = current;
		}
		current = current->next;
	}
	return closest;
}

// Function to create a new node
t_node *create_node(int value)
{
	t_node *new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node)
	{
		new_node->value = value;
		new_node->next = NULL;
		new_node->prev = NULL;
	}
	return new_node;
}

int main()
{
	// Example of creating a doubly linked list
	t_node *head = create_node(2);
	head->next = create_node(5);
	head->next->prev = head;
	head->next->next = create_node(8);
	head->next->next->prev = head->next;
	head->next->next->next = create_node(12);
	head->next->next->next->prev = head->next->next;

	int a = 10;
	t_node *closest = find_closest_smaller(head, a);

	if (closest)
		printf("The largest number less than %d is: %d\n", a, closest->value);
	else
		printf("There is no number less than %d\n", a);

	// Freeing memory
	while (head)
	{
		t_node *temp = head;
		head = head->next;
		free(temp);
	}

	return 0;
}
