OBJ_DIR=	./obj/
OBJ_CPP:=	$(SRC:%.cpp=$(OBJ_DIR)%.o)
OBJ:=		$(filter %.o, $(OBJ_CPP))

NAME_EXTENSION=	$(suffix $(NAME))
ifeq ($(MODE),)
MODE=		bin
endif
CALLER=		""

# Messages
OK_GEN:=	$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Generated $(CYAN)"$(NAME)"\n$(CLEAR)"
KO_GEN:=	$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Generated $(CYAN)"$(NAME)"\n$(CLEAR)"
OK_LINK:=	$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Linked $(CYAN)"$(NAME)"\n$(CLEAR)"
KO_LINK:=	$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Linked $(CYAN)"$(NAME)"\n$(CLEAR)"
RM_OBJ:=	$(ECHO) "$(WHITE)[$(YELLOW)RM$(WHITE)] Removed OBJs files [$(MODE)]\n$(CLEAR)"
RM_BIN:=	$(ECHO) "$(WHITE)[$(YELLOW)RM$(WHITE)] Removed $(CYAN)"$(NAME)"\n$(CLEAR)"
INSTALLED:=	$(ECHO) "$(WHITE)[$(PURPLE)CP$(WHITE)] Installed $(CYAN)"$(NAME)"\n$(CLEAR)"
CANT_INSTALL:=  $(ECHO) "$(WHITE)[$(PURPLE)CP$(WHITE)] Cannot install $(CYAN)"$(NAME)"\n$(CLEAR)"
NOT_EXEC:=	$(ECHO) "$(WHITE)[$(PURPLE)CP$(WHITE)] Not an executable, skipping ...\n$(CLEAR)"
UNINSTALLED:=	$(ECHO) "$(WHITE)[$(RED)RM$(WHITE)] Uninstalled $(CYAN)"$(NAME)"\n$(CLEAR)"
NOT_INSTALLED:=	$(ECHO) "$(WHITE)[$(RED)RM$(WHITE)] Not an installed, skipping ...\n$(CLEAR)"
NO_TEST:=	$(ECHO) "$(WHITE)No test available.$(CLEAR)\n"
NO_BENCH:=	$(ECHO) "$(WHITE)No benchmark available.$(CLEAR)\n"

# Rules
$(NAME):	$(OBJ)
		@$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME) && $(OK_LINK) || $(KO_LINK)

$(OBJ_DIR)%.o:	%.cpp
		@$(CXX) $(CXXFLAGS) -c -o $@ $< && \
		$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Compiled "$<"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Compiled "$<"\n$(CLEAR)"

all:		$(NAME)

infos:
		@$(ECHO) "$(CYAN)Compiler:\t\t$(CXX)\n"
		@$(ECHO) "Compilation Flags:\t$(CXXFLAGS)\n"
ifeq ($(NAME_EXTENSION),.a)
		@$(ECHO) "Library Generation:\t$(RANLIB)\n$(CLEAR)"
else
		@$(ECHO) "Link Flags:\t\t$(LDFLAGS)\n$(CLEAR)"
endif

fclean:		CALLER="fclean"
fclean:		clean
		@$(RM) $(NAME)
		@$(RM_BIN)

# We must use bash conditions because Make evaluates conditions at parsing-time.
clean:
		@$(RM) $(OBJ)
		@$(RM_OBJ)

re:		fclean all

run:
		@./$(NAME)

.PHONY: all clean fclean re run
