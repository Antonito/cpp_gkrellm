# Makefile dependencies directory
MK_DIR=		./mk/
MK_COMMON_DIR= 	./../mk/

include $(MK_COMMON_DIR)colors.mk $(MK_DIR)local_defs.mk $(MK_COMMON_DIR)defs.mk

# Project's files
VPATH=		./src/:./src/JSON/:./src/log/:./src/network/:./src/threads/:./src/modules/:./src/modules/cpu/:./src/modules/network/:./src/modules/system

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
		CPU.cpp			\
		Network.cpp		\
		System.cpp

SRC=		$(JSON_FILES) $(LOG_SRC) $(LOG_SRC) $(NETWORK_SRC)	\
		$(THREAD_SRC) $(MODULE_SRC)

# Rules
include $(MK_COMMON_DIR)rules.mk
