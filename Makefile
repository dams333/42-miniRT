NAME		=	miniRT

SRCS		=	main.c \
				$(addprefix parser/, \
					parser.c \
					parse_c_a.c \
					parse_l_cy.c \
					parse_sp_pl.c \
					parse_util.c \
					parse_util2.c \
					generate_list.c \
				) \
				$(addprefix geometric/, \
					point.c \
					vector.c \
				) \
				$(addprefix render/, \
					events.c \
					mlx_utils.c \
					render.c \
				) \
				$(addprefix interactions/, \
					interactions_manager.c \
					move.c \
				)


_OBJS		=	${SRCS:.c=.o}
OBJS		=	$(addprefix build/, $(_OBJS))
OBJS_DEPEND	=	${OBJS:.o=.d}

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -O3
INCLUDE		=	-I includes/ -I libs/minilibx-linux/
LIBS		=	libs/libft/libft.a libs/minilibx-linux/libmlx.a
EXT_LIBS	=	-lm -lX11 -lXext

all		:	$(NAME)

build/%.o	:	srcs/%.c
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CC) ${CFLAGS} -MMD -MF $(@:.o=.d) ${INCLUDE} -c $< -o $@

$(NAME)	:	$(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(EXT_LIBS) -o $(NAME)

$(LIBS)	:	FORCE
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib);\
		make -C $$(dirname $$lib);\
	done

FORCE	:

clean	:	
	rm -Rf build/

cleanlibs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) clean;\
		make -C $$(dirname $$lib) clean;\
	done

cleanall	:	clean cleanlibs


fclean	:	clean
	rm -f ${NAME}

fcleanlibs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) fclean;\
		make -C $$(dirname $$lib) fclean;\
	done

fcleanall	:	fclean fcleanlibs


re		:	fclean ${NAME}

relibs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) re;\
		make -C $$(dirname $$lib) re;\
	done

reall	: relibs re

-include $(OBJS_DEPEND)

.PHONY	:	all clean cleanlibs cleanall fclean fcleanlibs fcleanall re relibs reall libs
