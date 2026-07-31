NAME		:= codexion

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -pthread
CPPFLAGS	:= -Iincludes

SRC_DIR		:= src
OBJ_DIR		:= obj

SRCS		:=	main.c \
				parser/parse_args.c \
				parser/parse_numbers.c \
				parser/parse_validation.c \
				init/init_engine.c \
				init/init_dongles.c \
				init/init_coders.c \
				init/cleanup.c \
				heap/heap_init.c \
				heap/heap_priority.c \
				heap/heap_push.c \
				heap/heap_pop.c \
				simulation/run_simulation.c \
				simulation/coder_routine.c \
				simulation/simulation_state.c \
				simulation/simulation_time.c \
				simulation/monitor.c \
				utils/utils.c \
				utils/logging.c \

OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/codexion.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re