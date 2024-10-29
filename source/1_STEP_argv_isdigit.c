/*
we receive strings
program checks wich arguments are fullstring digits (1),
which are not (0)
*/  
#include <stdio.h>

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int is_numeric_argument(char *arg)
{
	int j = 0;
	if (arg[0] == '-' || arg[0] == '+') // Check for a sign
		j++;
	while (arg[j] != '\0')
	{
		if (!ft_isdigit(arg[j]))
			return (0); // If at least one character is not a digit, return 0
		j++;
	}
	return (1); // All characters are digits
}

int main(int argc, char *argv[])
{
	int i = 1;
	while (i < argc)
	{
		if (is_numeric_argument(argv[i]))
			printf("Argument %s is a number.\n", argv[i]);
		else
			printf("Argument %s is not a number.\n", argv[i]);
		i++;
	}
	return 0;
}
