int is_list_sorted(t_node *head)
{
	t_node *current = head;

	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0); // out of sequence
		current = current->next;
	}
	return (1); // order is maintained
}
