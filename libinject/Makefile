SRCS = copy_into_mem.c inject_payload.c call_mmap.c call_payload.c
OBJS = $(SRCS:.c=.o)

NAME = libinject.a

CC = gcc
CFLAGS = -Werror -Wall -Werror

all: $(NAME)

debug: CFLAGS += -g
debug: re

$(NAME): $(OBJS)
	ar rcs $@ $^

clean:
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(NAME) $(EXAMPLES)
	
re: fclean all
