GUI = gui
INCDIR+=$(GUI)
CSRC+= print.c
CPPSRC +=  $(GUI)/PirisPort.cpp $(GUI)/gui_api.cpp
CPPSRC += $(GUI)/main_screen.cpp