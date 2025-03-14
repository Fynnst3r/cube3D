NAME	= cub3d
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code

LIBMLX	= ./MLX42
HEADERS	= -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBMLXA = $(LIBMLX)/build/libmlx42.a

SRCS =  src/main.c\
		src/init/init_ray.c \
		src/hooks/game_loop.c \
		src/hooks/keyhook.c \
		src/textures.c \
		src/error/error.c \
		garbage_collector/garbage_start.c \
		garbage_collector/ft_malloc.c \
		garbage_collector/free.c \

OBJS = $(SRCS:.c=.o)
OBJ_DIR = obj
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
LIBFT = libft/libft.a

B := "\033[0;34m"
G := "\033[0;32m"
Y := "\033[0;33m"
DC := "\033[0;39m"

all: $(LIBMLXA) $(NAME)

$(LIBMLXA): $(LIBMLX)
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBMLX):
	git clone https://github.com/codam-coding-college/MLX42.git
	cmake $(LIBMLX) -B $(LIBMLX)/build
	cmake --build $(LIBMLX)/build -j4 

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) $(LIBFT) -g -o $(NAME)
	@echo $(Y)"cub3D is compiled!"$(DC)

$(LIBFT):
	make -C libft

$(OBJ_DIR)/%.o: %.c | create_dirs
	@cc $(CFLAGS) -c $< -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR)/src \
		$(OBJ_DIR)/src/error \
		$(OBJ_DIR)/src/init \
		$(OBJ_DIR)/src/hooks \
		$(OBJ_DIR)/garbage_collector \

clean:
	rm -f $(OBJS)
	rm -rf $(LIBMLX)/build
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	make -C libft fclean
	@echo $(Y)"\nEverything is properly cleaned!\n"$(DC)

re: fclean all

.PHONY: all clean fclean re create_dirs
