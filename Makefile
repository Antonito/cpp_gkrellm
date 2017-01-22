# Makefile dependencies directory
MK_DIR=		./mk/

include $(MK_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_DIR)defs.mk

# Project's files
VPATH=		./src/:./src/JSON/:./src/log/:./src/http/		\
		:./src/threads/:./src/modules/:./src/modules/cpu/	\
		:./src/modules/network/:./src/modules/system/		\
		:./src/modules/disk/:./src/modules/ram/			\
		:./src/graphic:./src/graphic/ncurses			\
		:./src/graphic/module:./src/graphic/module/network/	\
		:./src/graphic/module/network/ncurses			\
		:./src/modules/process/:./src/graphic/sfml		\
		:./src/graphic/module/network/sfml

SRC_FILES=	main.cpp		\
		MainManager.cpp

JSON_SRC=	JSONArray.cpp		\
		JSONException.cpp	\
		JSONObject.cpp		\
		JSONSource.cpp		\
		JSONString.cpp

LOG_SRC=	Logger.cpp

HTTP_SRC=	HTTPServer.cpp		\
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
		RAM.cpp			\
		Process.cpp

GRAPHIC_SRC=	AFrame.cpp		\
		AWindow.cpp		\
		GraphicException.cpp	\

NCURSES_SRC=	Frame.cpp		\
		Window.cpp		\
		NcTextArea.cpp

GRAPHIC_MODULE_SRC=	AModule.cpp	\
			ANcModule.cpp	\
			ASfModule.cpp

GFX_NETWORK=	NcNetwork.cpp	\
		SfNetwork.cpp

SFML_SRC=	SfWindow.cpp	\
		SfFrame.cpp



SRC=		$(SRC_FILES) $(JSON_FILES) $(LOG_SRC) $(HTTP_SRC)	\
		$(THREAD_SRC) $(MODULE_SRC) $(GRAPHIC_SRC)	\
		$(NCURSES_SRC) $(GRAPHIC_MODULE_SRC) $(GFX_NETWORK) \
		$(SFML_SRC)

# Rules
include $(MK_DIR)rules.mk
