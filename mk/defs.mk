# Commands definitions
RM=		rm -f
ECHO=		echo -ne
RANLIB=		ar rcs
CP=		cp
CHDIR=		cd
IGNORE=		2> /dev/null ||:

ROOT_DIR:=	$(realpath $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/../)
INSTALL_DIR=	bin/
INSTALL_PATH=	$(ROOT_DIR)/$(INSTALL_DIR)

SANITIZER=	-fsanitize=address			\
		-fsanitize=alignment			\
		-fsanitize=bool				\
		-fsanitize=bounds			\
		-fsanitize=enum				\
		-fsanitize=undefined			\
		-fsanitize=float-cast-overflow		\
		-fsanitize=float-divide-by-zero		\
		-fsanitize=function			\
		-fsanitize=integer-divide-by-zero	\
		-fsanitize=nonnull-attribute		\
		-fsanitize=null				\
		-fsanitize=object-size			\
		-fsanitize=return			\
		-fsanitize=returns-nonnull-attribute	\
		-fsanitize=shift			\
		-fsanitize=signed-integer-overflow	\
		-fsanitize=unreachable			\
		-fsanitize=unsigned-integer-overflow	\
		-fsanitize=vla-bound

# Compilation and link definitions
CXX=		g++
CPP_VER=	c++03

# Debug Infos
ifeq ($(Debug), yes)
CXXFLAGS=	-g -DDEBUG 				\
		$(LOCAL_DEBUG_FLAGS)

LDFLAGS=	-g
ifeq ($(CXX),clang++)
LDFLAGS+=	$(SANITIZER)
endif
else
CXXFLAGS=	-DNDEBUG				\
		-Werror					\
		-fomit-frame-pointer
LDFLAGS=
endif

CXXFLAGS+=	-std=$(CPP_VER) -W -Wall -Wextra	\
		-fstack-protector			\
		$(INC_DIR)				\
		$(LOCAL_COMP_FLAGS)

LDFLAGS+=	$(LOCAL_LINK_FLAGS)
