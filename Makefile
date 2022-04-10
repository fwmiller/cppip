##############################################################################
#
# Directories
#
INC		:= include
SRC		:= src
BIN		:= build

##############################################################################
#
# Tools
#
MKDIR		:= mkdir -p
CPP		:= g++
LD		:= g++
CP		:= cp
RM		:= rm -f
RMR		:= rm -fr

CPPFLAGS	:= -c -Wall -Og -fpermissive
#CPPFLAGS	+= -g
CPPFLAGS	+= -D_DEBUG

LIBS		:= -lpcap -lpthread -lreadline

INDENT_RULES := -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -psl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1

MAX_DEPTH	:= 2

##############################################################################
#
# CPP file sets
#
CPP_SRCS	:= $(shell find $(SRC) -maxdepth $(MAX_DEPTH) -name *.cpp -type f)
CPP_FILES	:= $(sort $(notdir $(CPP_SRCS)))

##############################################################################
#
# Object files
#
OBJS		:= $(foreach f,$(CPP_FILES),$(addprefix $(BIN)/,$(subst .cpp,.o,$(f))))

##############################################################################
#
# Executable file
#
EXECUTABLE	:= cppip

##############################################################################
#
# Rules
#

NC		:= \033[0m
BLACK		:= \033[0;30m
RED		:= \033[0;31m
GREEN		:= \033[0;32m
YELLOW		:= \033[0;33m
BLUE		:= \033[0;34m
PURPLE		:= \033[0;35m
CYAN		:= \033[0;36m
WHITE		:= \033[0;37m

.PHONY: clean indent wc debug

all: $(OBJS)
	@printf "Linking ${CYAN}$(EXECUTABLE)${NC}\r\n"
	@$(LD) -o $(EXECUTABLE) $(OBJS) $(LIBS)

# C++ source file compilation
$(BIN)/%.o: $(SRC)/%.cpp
	@$(MKDIR) $(BIN)
	@printf "Compiling ${CYAN}$<${NC}\r\n"
	@$(CPP) $(CPPFLAGS) -I$(INC) -o $@ $<

$(BIN)/%.o: $(SRC)/*/%.cpp
	@$(MKDIR) $(BIN)
	@printf "Compiling ${CYAN}$<${NC}\r\n"
	@$(CPP) $(CPPFLAGS) -I$(INC) -o $@ $<

clean:
	@$(RM) $(EXECUTABLE)
	@$(RMR) $(BIN)

# Indent pass of the include and src directories
indent: clean
	@cd $(INC);clang-format -i *.h
	@clang-format -i $(CPP_SRCS)

# Line counts
wc: clean
	@wc -l $(INC)/*.h $(CPP_SRCS)

# Debug
debug:
	@for f in $(CPP_SRCS); do printf "${CYAN}$$f${NC}\r\n"; done
	@printf "\r\n"
	@for f in $(CPP_FILES); do printf "${CYAN}$$f${NC}\r\n"; done
	@printf "\r\n"
	@for f in $(OBJS); do printf "${CYAN}$$f${NC}\r\n"; done
