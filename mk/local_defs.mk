# Definitions for Makefile
NAME=			gkrellm

INC_DIR=		-I./src/JSON/			\
			-I./src/log/			\
			-I./src/modules/		\
			-I./src/modules/cpu/		\
			-I./src/modules/network/	\
			-I./src/modules/system/		\
			-I./src/network/		\
			-I./src/threads/

DEBUG=			no

MODE=

LOCAL_COMP_FLAGS=	-pipe

LOCAL_LINK_FLAGS=	-pthread

LOCAL_DEBUG_FLAGS=
