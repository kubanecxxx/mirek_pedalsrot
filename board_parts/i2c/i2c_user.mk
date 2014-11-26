I2C = $(BOARD_PARTS_DIR)/i2c

I2C_USER_INC = $(I2C)
#I2C_USER_SRC = $(I2C)/i2c_user.c $(I2C)/harmonist.c $(I2C)/footswitch.c $(I2C)/delay.c
I2C_USER_SRC = $(I2C)/i2c_master.c $(I2C)/i2c_leds.c
I2C_USER_SRC += $(I2C)/i2c_buttons.c
I2C_USER_SRC += $(I2C)/i2c_harmonist.c

CSRC += $(I2C_USER_SRC)
INCDIR += $(I2C_USER_INC)