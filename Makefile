NAME = server
SRCS = ./srcs/*.c
OBJS = ./srcs/*.o
HEADER = ./includes/server.h
FLAGS = -Wall -Wextra -Werror

LIBFT = libft/

RED='\033[1;31m'
BLUE='\033[1;36m'
GREEN='\033[1;32m'
EOC='\033[0m' # End Of Color

INFO = ${BLUE}"[INFO]"${EOC}
REMOVED = ${RED}"removed!"${EOC}
CREATED = ${GREEN}"created!"${EOC}

all: $(NAME)
	
$(NAME): $(SRCS) $(HEADER) lib
	@gcc -pthread $(FLAGS) -o $(NAME) $(SRCS) -lmhash $(HEADER) libft/libft.a
	@echo ${GREEN}"Compiled successfully!"${NC}

debug: $(SRCS) $(HEADER) lib
	@gcc -g $(FLAGS) -o $(NAME) $(SRCS) -lmhash $(HEADER) libft/libft.a
	@echo ${GREEN}"Compiled successfully!"${NC}
	@echo ${GREEN}"Ready to debug!"${NC}

dclean: clean
	@/bin/rm -rf ft_printf.dSYM
	@/bin/rm -f $(NAME)
	@echo ${INFO}"Executable [$(NAME)] "${REMOVED}
	@echo ${INFO}"Debug info "${REMOVED}

lib:
	@make -C $(LIBFT)
	@echo ${INFO}"Library [$(LIBFT)]" ${CREATED}

clean: 
	@/bin/rm -f $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@echo ${INFO}"Executable [$(NAME)] "${REMOVED}
	@echo ${INFO}"Library [$(LIBFT)] "${REMOVED}


re: fclean all
