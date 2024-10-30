#include <stdlib.h>
#include <stdio.h>

typedef struct s_node
{
    int value;
    struct s_node *next;
    struct s_node *prev;
} t_node;

void print_list(t_node *head)
{
    t_node *current = head;
    while (current != NULL)
    {
        printf("%d\n", current->value); // Print the current node value
        current = current->next; // Move to the next node
    }
}

void reverse_list(t_node **head_a)
{
    t_node *current = *head_a;
    t_node *temp = NULL;

    while (current != NULL)
    {
        temp = current->prev; // Save the previous node
        current->prev = current->next; // Reverse the next pointer
        current->next = temp; // Reverse the prev pointer
        current = current->prev; // Move to the next node (which was previous in the original list)
    }

    if (temp != NULL)
        *head_a = temp->prev; // Set the new head to the last processed node
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

void free_list(t_node *head)
{
    t_node *current = head;
    while (current != NULL)
    {
        t_node *next_node = current->next; // Save the next node
        free(current); // Free the current node
        current = next_node; // Move to the next node
    }
}

int main()
{
    // Creating a simple list with three nodes: 1 -> 2 -> 3
    t_node *head = create_node(1);
    t_node *second = create_node(2);
    t_node *third = create_node(3);

    // Linking the nodes
    head->next = second;
    second->prev = head;
    second->next = third;
    third->prev = second;

    // Printing the original list
    printf("Original List:\n");
    print_list(head);

    // Reversing the list
    reverse_list(&head);

    // Printing the reversed list
    printf("Reversed List:\n");
    print_list(head);

    // Free allocated memory
    free_list(head);

    return 0;
}
/*
VISUALISATION BASED ON THIS EXAMPLE:
0) head_a -> [1] <-> [2] <-> [3] -> NULL
1) [1] -> NULL	[2] <-> [3] -> NULL
2) [1] <-> [2] -> NULL	[3] -> NULL
3) [1] <-> [2] <-> [3] -> NULL
if (temp != NULL) — this condition is true because temp points to Node 2.
*head_a = temp->prev; — we set the new head to the last processed node, which is now Node 3.
4) head_a -> [3] <-> [2] <-> [1] -> NULL
*/
