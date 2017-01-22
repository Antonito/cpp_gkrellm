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
			-I./src/modules/process/	\
			-I./src/http/			\
			-I./src/threads/		\
			-I./src/graphic/		\
			-I./src/graphic/ncurses/	\
			-I./src/graphic/module/		\
			-I./src/graphic/module/network	\
			-I./src/graphic/module/network/sfml	\
			-I./src/graphic/sfml		\
			-I./src/graphic/module/system

DEBUG=			no

MODE=

LOCAL_COMP_FLAGS=	-pipe

LOCAL_LINK_FLAGS=	-pthread -lncurses -lsfml-graphics -lsfml-window -lsfml-system

LOCAL_DEBUG_FLAGS=
