# Compiler and flags
CC      = cc -g -fsanitize=address

CFLAGS  = -Wall -Wextra -Werror 
# LIBS    = -lreadline

# Source and object files
NAME    = philo
SRCS    =  ./pars.c  ./init.c 
		
			
OBJS    = $(SRCS:.c=.o)

# Build target
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and binary
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all
s : all clean
.PHONY: all clean fclean re
