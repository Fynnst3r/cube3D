NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

CFILES = 	ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
			ft_memchr.c ft_memcmp.c ft_strdup.c ft_substr.c ft_strjoin.c \
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_strtrim.c ft_itoa.c ft_split.c \
			ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
			ft_lstmap_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c ft_printf.c helper_functions.c

OBJ_DIR = obj
OFILES = $(CFILES:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

$(OBJ_DIR)/%.o: %.c | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

create_dirs:
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re create_dirs