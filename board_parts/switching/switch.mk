SWI = $(BOARD_PARTS_DIR)/switching

INCDIR += $(SWI)
CSRC += $(SWI)/switch_lld.c $(SWI)/optocouplers.c $(SWI)/switch_master.c 
