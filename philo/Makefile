# Variables
HEADER = -I include
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
NAME = philo

#Exec Arguments
EXEC_ARG = 4 500 200 200 4

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -pthread -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) -pthread $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

run: $(NAME)
	@./$(NAME) $(EXEC_ARG)

rerun: re run

val: $(NAME)
	valgrind --tool=helgrind ./$(NAME) $(EXEC_ARG)

.PHONY: all clean fclean re