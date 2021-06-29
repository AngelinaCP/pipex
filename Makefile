# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddelena <ddelena@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/19 17:46:16 by ddelena           #+#    #+#              #
#    Updated: 2021/06/30 02:32:43 by ddelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c  ft_split.c ft_strncmp.c  \
			child_process.c process_exec.c ft_strjoin.c \
			get_next_line.c get_next_line_utils.c

SRCS_bonus	=	ft_split.c ft_strjoin.c ft_strncmp.c  \
                main_bonus.c  child_process.c process_exec.c \
                get_next_line.c get_next_line_utils.c

HEAD		=		pipex.h

OBJC    	=       ${SRCS:.c=.o}

OBJCB    	=		${SRCS_bonus:.c=.o}

NAME		=       pipex

NAMEB		=       pipex_bonus

CC      	=       gcc

FLAGS		=		-Wall -Wextra -Werror

RM			=       rm -rf

%.o:%.c 		$(HEAD)
				$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

all:            $(NAME)

$(NAME):        $(OBJC)
				$(CC) $(OBJC)  -o $(NAME)

bonus:			$(NAMEB)

$(NAMEB):		$(OBJCB)
				gcc -c $(SRCS_bonus)
				$(CC) $(OBJCB) -o $(NAMEB)

clean:
				${RM} ${OBJC} ${OBJCB}

fclean:			clean
				${RM} ${NAME} ${NAMEB}

re:				fclean	all

.PHONY:			all clean fclean re bonus
