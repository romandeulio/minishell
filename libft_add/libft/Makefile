# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/24 20:32:04 by rodeulio          #+#    #+#              #
#    Updated: 2025/04/11 14:01:21 by rodeulio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 🛠️ Compiler and options
CC         = cc
CFLAGS     = -Wall -Wextra -Werror
AR         = ar rcs
RM         = rm -f

# 📌 Library name
NAME       = libft.a

# 📜 Source files
SRCS       = srcs/ft_isalnum.c srcs/ft_isprint.c srcs/ft_memcmp.c srcs/ft_putchar_fd.c srcs/ft_split.c \
             srcs/ft_strlcat.c srcs/ft_strncmp.c srcs/ft_substr.c srcs/ft_atoi.c srcs/ft_isalpha.c \
             srcs/ft_itoa.c srcs/ft_memcpy.c srcs/ft_putendl_fd.c srcs/ft_strchr.c srcs/ft_strlcpy.c \
             srcs/ft_strnstr.c srcs/ft_tolower.c srcs/ft_bzero.c srcs/ft_isascii.c \
             srcs/ft_memmove.c srcs/ft_putnbr_fd.c srcs/ft_strdup.c srcs/ft_strlen.c srcs/ft_strrchr.c \
             srcs/ft_toupper.c srcs/ft_calloc.c srcs/ft_isdigit.c srcs/ft_memchr.c srcs/ft_memset.c \
             srcs/ft_putstr_fd.c srcs/ft_strjoin.c srcs/ft_strmapi.c srcs/ft_strtrim.c srcs/ft_striteri.c

BONUS_SRCS = srcs/ft_lstadd_front_bonus.c srcs/ft_lstnew_bonus.c srcs/ft_lstsize_bonus.c \
             srcs/ft_lstlast_bonus.c srcs/ft_lstadd_back_bonus.c srcs/ft_lstdelone_bonus.c \
             srcs/ft_lstclear_bonus.c srcs/ft_lstiter_bonus.c srcs/ft_lstmap_bonus.c

# 🔨 Generate object files
OBJS       = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

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

# 🔹 Bonus
bonus: $(NAME) $(BONUS_OBJS)
	@$(AR) $(NAME) $(BONUS_OBJS)

# 🧹 Clean object files
clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)

# 🗑️ Full cleanup
fclean: clean
	@$(RM) $(NAME)

# 🔄 Recompile from scratch
re: fclean all

# 📌 Rules to prevent `make` from treating these as targets
.PHONY: all clean fclean re bonus