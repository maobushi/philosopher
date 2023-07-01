CC = cc
CFLAGS = -Wall -Wextra -Werror 
LIB    = -pthread #-fsanitize=thread
C_NAME = philo
SRCDIR = srcs
OBJDIR = obj
INCDIR = include

C_SRC = srcs/main.c \
	srcs/check_input.c \
	srcs/utils.c

C_OBJ = $(addprefix $(OBJDIR)/,$(notdir $(C_SRC:%.c=%.o)))

all: $(OBJDIR) $(C_NAME)

$(OBJDIR):
	mkdir obj

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -o $(@) -c $(<)

$(C_NAME): $(C_OBJ)
	$(CC) -o $(C_NAME) $(C_OBJ) $(LIB)

clean:
	$(RM)r $(OBJDIR)

fclean: clean
	$(RM) $(C_NAME)

re: fclean all
