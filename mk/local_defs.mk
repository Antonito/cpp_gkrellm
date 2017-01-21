# Definitions for Makefile
NAME=			gkrellm

INC_DIR=		-I./src/			\
			-I./src/JSON/			\
			-I./src/log/			\
			-I./src/modules/		\
			-I./src/modules/cpu/		\
			-I./src/modules/network/	\
			-I./src/modules/system/		\
			-I./src/modules/disk/		\
			-I./src/modules/ram/		\
			-I./src/http/			\
			-I./src/threads/		\
			-I./src/graphic/		\
			-I./src/graphic/ncurses/	\
			-I./src/graphic/module/		\
			-I./src/graphic/module/network

DEBUG=			no

MODE=

LOCAL_COMP_FLAGS=	-pipe

LOCAL_LINK_FLAGS=	-pthread -lncurses

LOCAL_DEBUG_FLAGS=
