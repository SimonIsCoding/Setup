# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/24 17:15:43 by simarcha          #+#    #+#              #
#    Updated: 2024/04/20 18:00:01 by simarcha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra
NAME				= 
RM					= rm -rf

#FILES AND PATHS
#HEADER
INCLUDE_DIR			= inc/
INCLUDE_FILES		= get_next_line.h \
					  ft_printf.h
INCLUDE				= $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))

#UTILS - The annexes functions that I used for this project
UTILS_DIR			= utils/
UTILS_FILES			=
UTILS				= $(addprefix $(UTILS_DIR), $(UTILS_FILES))
OBJ_UTILS			= $(UTILS:.c=.o)

#SRCS - Where the main files for this project are located
SRCS_DIR			= srcs/
SRCS_FILES			= 
SRCS				= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJ_SRCS			= $(SRCS:.c=.o)

#LIBFT 
LIBFT_DIR			= utils/ft_printf/libft/
LIBFT_ARCHIVE		= $(addprefix $(LIBFT_DIR), libft.a)

#FT_PRINTF 
FT_PRINTF_DIR		= utils/ft_printf/
FT_PRINTF_ARCHIVE	= $(addprefix $(FT_PRINTF_DIR), libftprintf.a)

#GET_NEXT_LINE 
GNL_DIR				= utils/get_next_line/
GNL_FILES			= get_next_line.c
OBJ_GNL				= $(addprefix $(GNL_DIR), $(GNL_FILES:.c=.o))

#RULES AND COMMANDS
all:				$(LIBFT_ARCHIVE) $(FT_PRINTF_ARCHIVE) $(GNL_DIR) $(NAME)

%.o:				%.c Makefile $(INCLUDE)
					@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJ_UTILS) $(OBJ_SRCS) $(OBJ_GNL) $(LIBFT_ARCHIVE) $(FT_PRINTF_ARCHIVE) Makefile
					$(CC) $(CFLAGS) $(OBJ_UTILS) $(OBJ_SRCS) -L$(LIBFT_DIR) -L$(FT_PRINTF_DIR) -lft -lftprintf\
					$(OBJ_GNL) -o $(NAME)

$(LIBFT_ARCHIVE):
					@$(MAKE) -s -C $(LIBFT_DIR)
					@echo "\033[1;32m\033[1mAll Libft files compiled in $(LIBFT_DIR).\033[0m"

$(FT_PRINTF_ARCHIVE):
					@$(MAKE) -s -C $(FT_PRINTF_DIR)
					@echo "\033[1;32m\033[1mAll ft_printf files compiled in $(FT_PRINTF_DIR).\033[0m"

$(GNL_DIR):			$(OBJ_GNL)
					@echo "\033[1;32m\033[1mAll get_next_line files compiled in $(GNL_DIR).\033[0m"

clean:
				    @echo "\033[1;31m\033[1mDeleting every object files\033[0m" 
					@echo "\033[1mCleaning the object srcs files\033[0m"
					$(RM) $(OBJ_UTILS) $(OBJ_SRCS)
					@echo ""
					@echo "\033[1mCleaning the object libft files\033[0m"
					@$(MAKE) clean -C $(LIBFT_DIR)
					@echo ""
					@echo "\033[1mCleaning the ft_printf object files\033[0m"
					@$(MAKE) clean -C $(FT_PRINTF_DIR)
					@echo ""
					@echo "\033[1mCleaning the get_next_line object files\033[0m"
					$(RM) $(OBJ_GNL)

fclean:				clean
				    @echo "\033[1;31m\033[1mDeleting the executable and archive files\033[0m" 
					$(RM) $(NAME)
					@echo ""
					@echo "\033[1;31m\033[1mCleaning the libft object and archive files\033[0m"
					$(MAKE) fclean -C $(LIBFT_DIR)
					@echo ""
					@echo "\033[1;31m\033[1mCleaning the ft_printf object and archive files\033[0m"
					$(MAKE) fclean -C $(FT_PRINTF_DIR)

re:					fclean all

.PHONY:				all clean fclean re
