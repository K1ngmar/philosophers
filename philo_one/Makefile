# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ikole <ikole@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/15 16:36:12 by ikole         #+#    #+#                  #
#    Updated: 2020/12/05 15:25:18 by ikole         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo_one

SRC		= philo_one.c init.c helpers.c phil_stuff.c time.c destruction.c error.c

FLAGS	= -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

re: fclean all

clean:

fclean:
	@ rm -rf $(NAME)
