CC = cc
CFLAGS = -Wall -Wextra -Werror 
C_NAME = philosopher
SRCDIR = srcs
OBJDIR = obj
INCDIR = include

C_SRC = srcs/main.c\
		check_input.c

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
