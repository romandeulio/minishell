# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 15:32:49 by rodeulio          #+#    #+#              #
#    Updated: 2025/04/12 12:19:08 by rodeulio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 🛠️ Compiler and options
CC         = cc
CFLAGS     = -Wall -Wextra -Werror 
AR         = ar rcs
RM         = rm -f
MAKE       = make --no-print-directory

# 📌 Library name
NAME       = libft++.a

# 📂 Include directories
INCLUDES   = -Ilibft -Isrcs -Ift_printf -Ignl

# 🎨 Colors
GREEN      = \033[1;32m
YELLOW     = \033[1;33m
CYAN       = \033[1;36m
RED        = \033[1;31m
RESET      = \033[0m

# 🔹 Main compilation
all: $(NAME)

$(NAME):
	@make bonus -C ./libft/ >> /dev/null
#	@cp libft/libft.a $(NAME)
	@make -C ./ft_printf/ >> /dev/null
#	@cp ft_printf/ft_printf.a $(NAME)
	@make -C ./gnl/ >> /dev/null
#	@cp gnl/gnl.a $(NAME)
	@$(AR) $(NAME) libft/srcs/*.o ft_printf/srcs/*.o gnl/*.o
	@echo "$(GREEN)✅ Libft++ successfully compiled!$(RESET)"

# 🧹 Clean object files
clean:
	@make clean -C ./libft/ >> /dev/null
	@make clean -C ./ft_printf/ >> /dev/null
	@make clean -C ./gnl >> /dev/null
	@$(RM)
	@echo "$(RED)🧹 Object files removed in libft++.$(RESET)"

# 🗑️ Full cleanup
fclean: clean
	@make fclean -C ./libft >> /dev/null
	@make fclean -C ./ft_printf/ >> /dev/null
	@make fclean -C ./gnl >> /dev/null
	@$(RM) $(NAME)
	@echo "$(RED)🗑️  libft++.a removed.$(RESET)"

# 🔄 Recompile from scratch
re: fclean all

# 📌 Rules to prevent make from treating these as targets
.PHONY: all clean fclean re bonus
