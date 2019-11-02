NAME = 42sh

###############################
####### GLOBAL VARIABLE #######
###############################
include Makefile_cfg_var

###############################
######## CREATE FOLDER ########
####### C FILE BY FOLDER ######
###############################
include Makefile_cfg_folder

###############################
######### ADD PREFIX ##########
###### ALL SRC/OBJ FILE #######
###############################
include Makefile_cfg_prefix

all: $(NAME)

$(NAME): $(LIBFTDIR)/$(LIB) $(OBJSDIR) $(OBJS)
	@$(CC) $(LDFLAGS) -I$(HEADERLIB) -I$(INCLUDES) $(OBJS) -o ../$(NAME)
	@echo ""

include Makefile_cfg_obj

$(LIBFTDIR)/$(LIB):
	@make -C $(LIBFTDIR)/

clean:
	@echo "${RED}Cleaning $(NAME)${RESET} [${GREEN}✔${RESET}]"
	@/bin/rm -rf $(OBJSDIR);
	@make clean -C $(LIBFTDIR)

fclean: clean
	@echo "${RED}Purge $(NAME)${RESET} [${GREEN}✔${RESET}]"
	@/bin/rm -f ../$(NAME)
	@make fclean -C $(LIBFTDIR)
	@rm -rf ../$(NAME).dSYM

re: fclean all

.PHONY: all, clean, fclean, re, $(LIBD)

.SUFFIXES: .c .o
