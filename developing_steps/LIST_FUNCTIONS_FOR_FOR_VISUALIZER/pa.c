#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_node
{
    int value;
    struct s_node *next;
    struct s_node *prev;
} t_node;

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

// Function to add a node to the start of the list
void push_to_list(t_node **head, int value)
{
    t_node *new_node = create_node(value);
    if (new_node)
    {
        new_node->next = *head;
        if (*head)
            (*head)->prev = new_node;
        *head = new_node;
    }
}

// Function sa, which swaps the top two elements and prints "sa\n"
void sa(t_node **a)
{
    if (*a && (*a)->next)
    {
        t_node *first = *a;
        t_node *second = (*a)->next;

        // Swap the first two elements
        first->next = second->next;
        if (second->next)
            second->next->prev = first;
        second->prev = NULL;
        second->next = first;
        first->prev = second;
        *a = second;

        // Print "sa\n" using write
        write(1, "sa\n", 3);
    }
}

// Function to print the list
void print_list(t_node *head)
{
    t_node *current = head;
    while (current)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

// Main function for testing
int main()
{
    // Create list a and add elements to it
    t_node *a = NULL;
    push_to_list(&a, 3);
    push_to_list(&a, 2);
    push_to_list(&a, 1);

    printf("Initial list a: ");
    print_list(a);

    // Apply the sa function to swap the top two elements
    sa(&a);

    printf("List a after sa: ");
    print_list(a);

    // Free memory
    while (a)
    {
        t_node *temp = a;
        a = a->next;
        free(temp);
    }

    return 0;
}
