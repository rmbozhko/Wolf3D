NAME = wolf3d

SRC = main.c ImgDrawing.c raycastingAlgo.c movementHandlers.c surfaceDrawing.c doorsHandler.c audio.c printScreen.c textures.c utils.c
SRCO = $(SRC:.c=.o)

LIBFT = libft/libft.a

FLAGS = -O3 -Wall -Wextra -Werror
GRAPHICS =  -lmlx -framework OpenGL -framework AppKit -framework OpenCl -L./jpeglib -ljpeg
INCLUDES =  -I ./frameworks/SDL2.framework/Versions/A/Headers \
			-I ./frameworks/SDL2_mixer.framework/Versions/A/Headers \
			-F ./frameworks

FRAMEWORKS =  -F ./frameworks \
			  -rpath ./frameworks \
			  -framework SDL2 \
			  -framework SDL2_mixer

all: $(NAME)

$(NAME): $(SRCO)
	@make -C jpeglib/
	make -C libft/
	gcc -o $(NAME) $(SRCO) $(LIBFT) $(FLAGS) $(GRAPHICS) $(FRAMEWORKS)

%.o: %.c
	gcc -c $(FLAGS) $(INCLUDES) -o $@ $<
clean:
	@rm -f *.jpg
	@make clean -C libft/
	@make clean -C jpeglib/
	/bin/rm -f *.o

fclean: clean
	@make clean -C jpeglib
	make fclean -C libft/
	/bin/rm -f $(NAME)

re: fclean all
