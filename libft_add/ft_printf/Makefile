# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 23:40:32 by rodeulio          #+#    #+#              #
#    Updated: 2025/04/11 21:28:56 by rodeulio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 🛠️ Compiler and options
CC         = cc
CFLAGS     = -Wall -Wextra -Werror 
AR         = ar rcs
RM         = rm -f
MAKE       = make --no-print-directory

# 📌 Library name
NAME       = ft_printf.a

# 📜 Source files for printf
SRCS = srcs/ft_printf.c \
	srcs/ft_putnbr_base.c \
	srcs/ft_putnbr_base_u.c \
	srcs/print_p.c \
	srcs/print_c_s.c \

# 🔨 Generate object files
OBJS       = $(SRCS:.c=.o)

# 📂 Include directories
INCLUDES   = -Ilibft -Isrcs

# 🎨 Colors
GREEN      = \033[1;32m
YELLOW     = \033[1;33m
CYAN       = \033[1;36m
RED        = \033[1;31m
RESET      = \033[0m

# 📌 Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# 🔹 Main compilation
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

# 🧹 Clean object files
clean:
	@$(RM) $(OBJS)

# 🗑️ Full cleanup
fclean: clean
	@$(RM) $(NAME)

# 🔄 Recompile from scratch
re: fclean all

# 📌 Rules to prevent make from treating these as targets
.PHONY: all clean fclean re bonus