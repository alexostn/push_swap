int is_duplicate(t_node *head, int value)
{
	t_node *current = head;
	while (current != NULL) // While the end of the list has not been reached
	{
		if (current->value == value) // If the current value matches the new value
			return 1; // Duplicate found
		current = current->next; // Move to the next node
	}
	return 0; // No duplicates found
}
