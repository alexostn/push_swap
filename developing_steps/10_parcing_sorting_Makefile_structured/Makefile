# The name of the final executable file
NAME = push_swap

# The compiler to be used
CC = gcc

# Compiler flags to enable warnings and treat them as errors
CFLAGS = -Wall -Wextra -Werror

# Source files that are part of the project
SRC = src/parsing.c src/sorting.c src/main.c

# Object files generated from the source files
# The syntax $(SRC:.c=.o) replaces the .c extension with .o for each file in SRC
OBJ = $(SRC:.c=.o)

# Directory containing header files
INCLUDE = include

# Default target to build the project
all: $(NAME)

# Rule to create the final executable
# This rule specifies that the target $(NAME) depends on $(OBJ)
$(NAME): $(OBJ)
	# The command to link object files and create the final executable
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

# Pattern rule to compile .c files into .o files
# This rule specifies that for each .o file, it should be generated from the corresponding .c file
%.o: %.c
	# The command to compile the source file into an object file
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@
	# -I $(INCLUDE) adds the include directory to the search path for header files
	# -c flag tells the compiler to compile the source file into an object file only
	# $< represents the first prerequisite (the source file)
	# $@ represents the target (the object file)

# Target to clean up object files
clean:
	# Remove all object files
	rm -f $(OBJ)

# Target to perform a full cleanup, removing both object files and the executable
fclean: clean
	# Remove the final executable
	rm -f $(NAME)

# Target to recompile everything from scratch
re: fclean all

# Declare that these targets are not actual files
.PHONY: all clean fclean re
