# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbaruls- <gbaruls-@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/06 16:54:00 by gbaruls-          #+#    #+#              #
#    Updated: 2025/02/13 17:14:17 by pamanzan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBS		= include/minishell.h
LIBINC		= include/
LIBFT		= mylibft/libft.a
LIBFTINC	= mylibft/include

SRC_DIR		= src/
OBJ_DIR		= obj/

SRCS_FILES	= $(shell find src -type f -iname "*.c" | sed 's#[.][^.]*$$##')

SRCS 		= $(addsuffix .c, $(SRCS_FILES))
SRCDIRS		= $(shell find src/ -type d)
OBJSDIRS	= $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRCDIRS))
OBJSTEMP	= $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRCS_FILES))
OBJS		= $(addsuffix .o, $(OBJSTEMP))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror 
DFLAGS		= -g -fsanitize=address
AR			= ar rcs
RANLIB		= ranlib
RM			= rm -rf
MKDIR		= mkdir -p

.PHONY:		all clean fclean re info normi libft

all:		libft $(NAME)

$(NAME):	$(LIBFT) $(OBJSDIRS) $(OBJS)
			$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBS) Makefile
			$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

$(OBJSDIRS) :
			$(MKDIR) $(OBJSDIRS)

libft:
			make -C ./mylibft/

clean:
			$(RM) $(OBJS)
			make clean -C ./mylibft/

fclean:		clean
			$(RM) $(OBJSDIRS)
			$(RM) $(NAME)
			make fclean -C ./mylibft/

re:			fclean all

normi:
			@norminette $(SRCS)

info:
			$(info $(SRCS_FILES))

