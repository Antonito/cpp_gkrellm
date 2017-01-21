# Makefile dependencies directory
MK_DIR=		./mk/

include $(MK_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_DIR)defs.mk

# Project's files
VPATH=		./src/:./src/JSON/:./src/log/:./src/network/		\
		:./src/threads/:./src/modules/:./src/modules/cpu/	\
		:./src/modules/network/:./src/modules/system/		\
		:./src/modules/disk/:./src/modules/ram/			\
		:./src/graphic:./src/graphic/ncurses

SRC_FILES=	main.cpp

JSON_SRC=	JSONArray.cpp		\
		JSONException.cpp	\
		JSONObject.cpp		\
		JSONSource.cpp		\
		JSONString.cpp

LOG_SRC=	Logger.cpp

NETWORK_SRC=	HTTPServer.cpp		\
		TCPSocket.cpp

THREAD_SRC=	Mutex.cpp		\
		Semaphore.cpp		\
		Thread.cpp		\
		ThreadPool.cpp

MODULE_SRC=	ModuleManager.cpp	\
		UtilsModule.cpp		\
		CPU.cpp			\
		Network.cpp		\
		System.cpp		\
		Disk.cpp		\
		RAM.cpp

GRAPHIC_SRC=	AFrame.cpp		\
		AWindow.cpp		\
		GraphicException.cpp

NCURSES_SRC=	Frame.cpp		\
		Window.cpp

SRC=		$(SRC_FILES) $(JSON_FILES) $(LOG_SRC) $(NETWORK_SRC)	\
		$(THREAD_SRC) $(MODULE_SRC) $(GRAPHIC_SRC) $(NCURSES_SRC)

# Rules
include $(MK_DIR)rules.mk
