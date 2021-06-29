# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddelena <ddelena@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/19 17:46:16 by ddelena           #+#    #+#              #
#    Updated: 2021/06/30 01:44:01 by ddelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	pipex.c  ft_split.c ft_strncmp.c  \
			child_process.c process_exec.c ft_strjoin.c \
			get_next_line.c get_next_line_utils.c

SRCS_bonus	=	ft_split.c ft_strjoin.c ft_strncmp.c  \
                pipex_bonus.c  child_process.c process_exec.c \
                get_next_line.c get_next_line_utils.c

HEAD	= pipex.h

OBJC    	=       ${SRCS:.c=.o}

OBJCB	= ${SRCS_bonus:.c=.o}

NAME	= pipex

NAME_B 	= pipex_bonus

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror


%.o : %.c   $(HEAD)
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME):	$(HEAD) $(OBJC)
			$(CC) $(OBJC) -o $(NAME)

bonus:			$(NAMEB)

$(NAME_B):		$(OBJCB)
				$(CC) $(OBJCB) -o $(NAME_B)

clean:
		rm -f ${OBJS} ${OBJCB}

fclean:	clean
		rm -f ${NAME} ${NAMEB}


re:		fclean all

.PHONY:	all, clean, fclean, re bonus