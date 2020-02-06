# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/13 15:06:40 by gbianco           #+#    #+#              #
#    Updated: 2020/02/06 09:18:53 by lucmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
OBJD = compiled/
SANI = -g
FLAGS = -Wall -Wextra -Werror $(SANI)

SRC = ft_atoi.c\
	  ft_atol.c\
	  ft_atoi_base.c\
	  ft_atof.c\
	  ft_power.c\
	  ft_bzero.c\
	  ft_concat_params.c\
	  ft_count_words.c\
	  ft_count_dig_words.c\
	  ft_cube_root.c\
	  ft_degtorad.c\
	  ft_int_buffer.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_isascii.c\
	  ft_isdigit.c\
	  ft_isprint.c\
	  ft_iscapital.c\
	  ft_itoa.c\
	  ft_itoa_base.c\
	  ft_ltoa.c\
	  ft_ftoa.c\
	  ft_lstadd.c\
	  ft_lstcount.c\
	  ft_lstdel.c\
	  ft_lstdelone.c\
	  ft_lstiter.c\
	  ft_lstmap.c\
	  ft_lstnew.c\
	  ft_memalloc.c\
	  ft_memccpy.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memdel.c\
	  ft_memmove.c\
	  ft_memset.c\
	  ft_fmax.c\
	  ft_fmin.c\
	  ft_frange.c\
	  ft_fswap.c\
	  ft_putchar.c\
	  ft_putchar_fd.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_putnbr.c\
	  ft_putnbr_fd.c\
	  ft_putstr.c\
	  ft_putstr_fd.c\
	  ft_radtodeg.c\
	  ft_secmemalloc.c\
	  ft_strcat.c\
	  ft_strchr.c\
	  ft_strclr.c\
	  ft_strcmp.c\
	  ft_strcpy.c\
	  ft_strdel.c\
	  ft_strarraydel.c\
	  ft_strarraydeln.c\
	  ft_strdup.c\
	  ft_strequ.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strjoin.c\
	  ft_strlcat.c\
	  ft_strlen.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strncat.c\
	  ft_strncmp.c\
	  ft_strncpy.c\
	  ft_strnequ.c\
	  ft_strnew.c\
	  ft_strnstr.c\
	  ft_strrchr.c\
	  ft_strrev.c\
	  ft_strsplit.c\
	  ft_strstr.c\
	  ft_strinstr.c\
	  ft_strinstr_unlimited.c\
	  ft_strsub.c\
	  ft_strtrim.c\
	  ft_tolower.c\
	  ft_toupper.c\
	  ft_isnumber.c\
	  ft_ishex.c\
	  get_next_line.c\
	  ft_strnjoin.c\
	  ft_strjoinf.c\
	  ft_putstrn.c\
	  ft_straddc.c\
	  ft_stradd_at.c\
	  ft_stradd_bf.c\
	  ft_ftoa_true_god.c\
	  ft_abs.c\
	  ft_ultoa.c

PPTH = ./printf/
SRC += ft_printf.c error.c parser.c bool.c peacemaker.c\
	   hex.c print.c get_csp.c get_iuo.c get_x.c print_int.c print_hf.c\
	   print_ptr.c get_f.c init.c

# Colors
CLRR = \033[0;31m
CLRG = \033[0;32m
CLRC = \033[0;36m
CLRW = \033[0m
LIBC = $(CLRC)[LIBFT]$(CLRW)

OBJS = $(addprefix $(OBJD), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJD) $(OBJS)
	@printf	"$(LIBC)%-50s [$(CLRR)%s$(CLRW)]" "Libft compiled" "✘"	
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf	"\r$(LIBC)$(CLRG)%-50s$(CLRW) [$(CLRG)%s$(CLRW)]\n" "Libft compiled" "✔"

$(OBJD): 
	@mkdir -p $(OBJD)
	@printf "$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "Repository: $@ created" "✔"

$(OBJD)%.o: %.c libft.h
	@printf	"$(LIBC)%-50s [$(CLRR)%s$(CLRW)]" "Object: $@ compiled" "✘"	
	@gcc $(FLAGS) -c $< -o $@
	@printf	"\r$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "Object: $@ compiled" "✔" 

$(OBJD)%.o: $(PPTH)%.c libft.h
	@printf	"$(LIBC)%-50s [$(CLRR)%s$(CLRW)]" "Object: $@ compiled" "✘"	
	@gcc $(FLAGS) -c $< -o $@
	@printf	"\r$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "Object: $@ compiled" "✔" 

.PHONY: clean fclean re
.NOTPARALLEL : $(OBJS)

clean:
	@rm -rf $(OBJD)
	@printf	"$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "Objects removed" "∙"	

fclean: clean
	@rm -f $(NAME)
	@printf	"$(LIBC)%-50s [$(CLRG)%s$(CLRW)]\n" "File: $(NAME) removed" "∙"	

re: fclean all
