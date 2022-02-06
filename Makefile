##############################################################################
#
# Directories
#
INC		:= include
SRC		:= src
BIN		:= build

#
# Tools
#
MKDIR		:= mkdir -p
CC		:= g++
LD		:= g++
CP		:= cp
RM		:= rm -fr

##############################################################################
#
# Tool options
#
CFLAGS		:= -c -Wall -Og
CFLAGS		+= -D_DEBUG

INDENT_RULES := -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -psl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1

MAX_DEPTH	:= 1

##############################################################################
#
# CPP file sets
#
CPP_SRCS	:= $(shell find $(SRC)/ -maxdepth $(MAX_DEPTH) -type f -regex ".*\.cpp")
CPP_FILES	:= $(sort $(notdir $(CPP_SRCS)))

##############################################################################
#
# Object files
#
OBJS		:= $(foreach f,$(CPP_FILES),$(addprefix $(BIN)/,$(subst .cpp,.o,$(f))))
OBJS		:= $(sort $(OBJS))

##############################################################################
#
# Executable file
#
EXECUTABLE	:= cppip

##############################################################################
#
# Rules
#
LIBS		:= -lpcap
all: $(OBJS)
	$(LD) -o $(EXECUTABLE) $(OBJS) $(LIBS)

#
# Execute using QEMU emulator
#
run: all
	qemu-system-x86_64 -m size=4 -nographic -no-reboot -drive format=raw,file=$(BIN)/iso.img

clean:
	rm -f $(EXECUTABLE)
	$(RM) $(BIN)

#
# Indent pass of the include and src directories
#
indent: clean
	cd $(INC);clang-format -i *.h
	cd $(SRC);clang-format -i *.cpp

wc: clean
	wc -l $(INC)/*.h $(SRC)/*.cpp

debug:
	@for f in $(CPP_SRCS); do echo $$f; done
	@echo
	@for f in $(OBJS); do echo $$f; done

#
# C++ source file compilation
#
$(BIN)/%.o: $(SRC)/%.cpp
	@$(MKDIR) $(BIN)
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<
