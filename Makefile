##
## EPITECH PROJECT, 2018
## *
## File description:
## *
##

CFLAGS  	=       -W -Wall -Wextra

CPPFLAGS	+=	-I ./include/

NSRC     	=	nm/main.c	\
			nm/print_data.c	\
			nm/list.c	\
			parser/init_elf.c

OSRC     	=	objdump/main.c	\
			objdump/obj.c	\
			objdump/print.c	\
			parser/init_elf.c

NNAME    	=       my_nm

ONAME    	=      	my_objdump

NOBJ     	=       $(NSRC:.c=.o)

OOBJ     	=       $(OSRC:.c=.o)

CC      	=       gcc

RM      	=       rm -f

all:    nm objdump

nm:	$(NNAME)

objdump:$(ONAME)

clean:
	$(RM) $(NOBJ)
	$(RM) $(OOBJ)

fclean: clean
	$(RM) $(NNAME)
	$(RM) $(ONAME)

$(NNAME):    $(NOBJ)
	$(CC) -o $(NNAME) $(NOBJ)

$(ONAME):    $(OOBJ)
	$(CC) -o $(ONAME) $(OOBJ)

re:     fclean all clean

.PHONY: all nm objdump re clean fclean
