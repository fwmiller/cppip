##############################################################################
#
# Directories
#
INC		:= include
SRC		:= src
BUILD		:= build

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
CPPFLAGS	+= -D_DEBUG_DHCP
CPPFLAGS	+= -D_DEBUG_DNS

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
	$(BUILD)/arp.o		\
	$(BUILD)/arp_dump.o	\
	$(BUILD)/arp_receive.o	\
	$(BUILD)/arptab.o		\
	$(BUILD)/arptab_entry.o	\
	$(BUILD)/bufpool.o	\
	$(BUILD)/bufq.o		\
	$(BUILD)/cppip.o		\
	$(BUILD)/cppip_dump.o	\
	$(BUILD)/eth.o		\
	$(BUILD)/eth_dump.o	\
	$(BUILD)/eth_receive.o	\
	$(BUILD)/eth_send.o	\
	$(BUILD)/icmp.o		\
	$(BUILD)/icmp_dump.o	\
	$(BUILD)/icmpv6.o		\
	$(BUILD)/ieee802_2.o	\
	$(BUILD)/ipproto_dump.o	\
	$(BUILD)/ipv4.o		\
	$(BUILD)/ipv4_dump.o	\
	$(BUILD)/ipv6.o		\
	$(BUILD)/ipv6_dump.o	\
	$(BUILD)/ports.o		\
	$(BUILD)/sockets.o	\
	$(BUILD)/stats.o		\
	$(BUILD)/udp.o		\
	$(BUILD)/udp_dump.o	\
	$(BUILD)/udp_receive.o	\
	$(BUILD)/udptab.o

DHCP_OBJS	:=		\
	$(BUILD)/dhcp.o		\
	$(BUILD)/dhcp_dump.o

DNS_OBJS	:=		\
	$(BUILD)/dns.o		\

CLI_OBJS	:=		\
	$(BUILD)/bufq_test.o	\
	$(BUILD)/byteq.o		\
	$(BUILD)/byteq_test.o	\
	$(BUILD)/capture.o	\
	$(BUILD)/cli.o		\
	$(BUILD)/main.o		\
	$(BUILD)/nextarg.o


##############################################################################
#
# Library file
#
LIBCPPIP	:= $(BUILD)/libcppip.a
LIBDHCP		:= $(BUILD)/libdhcp.a
LIBDNS		:= $(BUILD)/libdns.a
LIBS		:= $(LIBDNS) $(LIBDHCP) $(LIBCPPIP) -lpcap -lpthread -lreadline

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

all: $(DNS_OBJS) $(DHCP_OBJS) $(LIBCPPIP_OBJS) $(CLI_OBJS)
	@printf "Archiving ${CYAN}$(LIBCPPIP)${NC}\r\n"
	@$(AR) $(LIBCPPIP) $(LIBCPPIP_OBJS)
	@printf "Archiving ${CYAN}$(LIBDHCP)${NC}\r\n"
	@$(AR) $(LIBDHCP) $(DHCP_OBJS)
	@printf "Archiving ${CYAN}$(LIBDNS)${NC}\r\n"
	@$(AR) $(LIBDNS) $(DNS_OBJS)
	@printf "Linking ${CYAN}$(EXE)${NC}\r\n"
	@$(LD) -o $(EXE) $(CLI_OBJS) $(LIBS)

# C++ source file compilation
$(BUILD)/%.o: $(SRC)/*/%.cpp
	@$(MKDIR) $(BUILD)
	@printf "Compiling ${CYAN}$<${NC}\r\n"
	@$(CPP) $(CPPFLAGS) -I$(INC) -o $@ $<

clean:
	@$(RM) $(EXE)
	@$(RM) $(LIBCPPIP)
	@$(RM) $(LIBDHCP)
	@$(RM) $(LIBDNS)
	@$(RMR) $(BUILD)

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
	@for f in $(DNS_OBJS); do printf "${CYAN}$$f${NC}\r\n"; done
	@printf "\r\n"
	@for f in $(CLI_OBJS); do printf "${CYAN}$$f${NC}\r\n"; done
