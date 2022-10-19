
include $(CHOPIN_PROJ)/mk/glob_begin.mk
include $(CHOPIN_PROJ)/mk/app_begin.mk

LIBSO+= -lquickfix
LIBSG+= -lquickfix

INCL+=-I$(CHOPIN_PROJ)/quickfix-1.15.1/

SRC = main.cpp TTFixClient.cpp
APPNAM = tt

include $(CHOPIN_PROJ)/mk/app_template.mk
