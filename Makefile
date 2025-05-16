# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rodeulio <rodeulio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 12:12:12 by rodeulio          #+#    #+#              #
#    Updated: 2025/05/16 15:26:33 by rodeulio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJDIR     = objs
# 🛠️ Compiler and options
CC         = cc
CFLAGS     = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS    = -L/opt/homebrew/opt/readline/lib
RM         = rm -f
MAKE       = make --no-print-directory

# 📌 Color variables
GREEN      = \033[1;32m
YELLOW     = \033[1;33m
RED        = \033[1;31m
RESET      = \033[0m

# 📌 Exec and lib name
NAME       = Minishell
LIBFT_LIB  = libft_add/libft++.a
LIBFT_DIR  = libft_add

# 📜 Source files
SRCS = srcs/minishell.c srcs/get_cur_dir.c srcs/exit.c \

# 🔨 Generate object files
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

# 📌 Compile .c to .o
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# 📂 Include directories
INCLUDES = -Ilibft -Ift_printf -Ignl -Isrcs

# 📌 Compile the executable
all: $(NAME) logo

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR) >> /dev/null

$(NAME): $(OBJS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -Llibft_add -lft++ -lreadline -o $(NAME)

# 🧹 Clean object files
clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJDIR)
	@$(MAKE) clean -C $(LIBFT_DIR) >> /dev/null
	@echo "$(YELLOW)🧹 Cleaned Minishell object files.$(RESET)"

# 🗑️ Full cleanup
fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) >> /dev/null
	@echo "$(RED)🗑️  Removed Minishell binary.$(RESET)"

# 🔄 Recompile from scratch
re: fclean all

# 📌 Logo for fun
logo:
	@clear
	@echo "\033[1;35m"
	@echo " __  __ _       _     _          _ _ "
	@echo "|  \/  (_)_ __ (_)___| |__   ___| | |"
	@echo "| |\/| | | '_ \| / __| '_ \ / _ \ | |"
	@echo "| |  | | | | | | \__ \ | | |  __/ | |"
	@echo "|_|  |_|_|_| |_|_|___/_| |_|\___|_|_|"
	@echo "                                     "
	@echo "       rodeulio && nbrecque          "
	@echo "\033[0m"

# 📌 Rules to prevent make from treating these as targets
.PHONY: all clean fclean re logo