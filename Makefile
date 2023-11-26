##############################################################################
#
# Directories
#
INC		:= include
SRC		:= src
BIN		:= bin

##############################################################################
#
# Tools
#
MKDIR		:= mkdir -p
CPP		:= g++
AR		:= ar -rc
LD		:= g++
CP		:= cp
RM		:= rm -f
RMR		:= rm -fr

CPPFLAGS	:= -c -Wall -Wno-class-memaccess -Og -fpermissive
#CPPFLAGS	+= -g
CPPFLAGS	+= -D_DEBUG
#CPPFLAGS	+= -D_DEBUG_DHCP

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
LIBCPPIP_OBJS	:=		\
	$(BIN)/arp.o		\
	$(BIN)/arp_dump.o	\
	$(BIN)/arp_receive.o	\
	$(BIN)/arptab.o		\
	$(BIN)/arptab_entry.o	\
	$(BIN)/bufpool.o	\
	$(BIN)/bufq.o		\
	$(BIN)/cppip.o		\
	$(BIN)/cppip_dump.o	\
	$(BIN)/eth.o		\
	$(BIN)/eth_dump.o	\
	$(BIN)/eth_receive.o	\
	$(BIN)/eth_send.o	\
	$(BIN)/icmp.o		\
	$(BIN)/icmp_dump.o	\
	$(BIN)/icmpv6.o		\
	$(BIN)/ieee802_2.o	\
	$(BIN)/ipproto_dump.o	\
	$(BIN)/ipv4.o		\
	$(BIN)/ipv4_dump.o	\
	$(BIN)/ipv6.o		\
	$(BIN)/ipv6_dump.o	\
	$(BIN)/ports.o		\
	$(BIN)/sockets.o	\
	$(BIN)/stats.o		\
	$(BIN)/udp.o		\
	$(BIN)/udp_dump.o	\
	$(BIN)/udp_receive.o	\
	$(BIN)/udptab.o

DHCP_OBJS	:=		\
	$(BIN)/dhcp.o		\
	$(BIN)/dhcp_dump.o

CLI_OBJS	:=		\
	$(BIN)/bufq_test.o	\
	$(BIN)/byteq.o		\
	$(BIN)/byteq_test.o	\
	$(BIN)/capture.o	\
	$(BIN)/cli.o		\
	$(BIN)/main.o		\
	$(BIN)/nextarg.o


##############################################################################
#
# Library file
#
LIBCPPIP	:= $(BIN)/libcppip.a
LIBDHCP		:= $(BIN)/libdhcp.a
LIBS		:= $(LIBDHCP) $(LIBCPPIP) -lpcap -lpthread -lreadline

##############################################################################
#
# Executable file
#
EXE		:= cppip

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

all: $(DHCP_OBJS) $(LIBCPPIP_OBJS) $(CLI_OBJS)
	@printf "Archiving ${CYAN}$(LIBCPPIP)${NC}\r\n"
	@$(AR) $(LIBCPPIP) $(LIBCPPIP_OBJS)
	@printf "Archiving ${CYAN}$(LIBDHCP)${NC}\r\n"
	@$(AR) $(LIBDHCP) $(DHCP_OBJS)
	@printf "Linking ${CYAN}$(EXE)${NC}\r\n"
	$(LD) -o $(EXE) $(CLI_OBJS) $(LIBS)

# C++ source file compilation
$(BIN)/%.o: $(SRC)/*/%.cpp
	@$(MKDIR) $(BIN)
	@printf "Compiling ${CYAN}$<${NC}\r\n"
	@$(CPP) $(CPPFLAGS) -I$(INC) -o $@ $<

clean:
	@$(RM) $(EXE)
	@$(RM) $(LIBCPPIP)
	@$(RM) $(LIBDHCP)
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
	@printf "\r\n"
	@for f in $(LIBCPPIP_OBJS); do printf "${CYAN}$$f${NC}\r\n"; done
	@printf "\r\n"
	@for f in $(DHCP_OBJS); do printf "${CYAN}$$f${NC}\r\n"; done
	@printf "\r\n"
	@for f in $(CLI_OBJS); do printf "${CYAN}$$f${NC}\r\n"; done
