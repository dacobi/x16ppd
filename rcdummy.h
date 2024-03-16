
int rc_i2c_init(int cBus,int cDevAddr){return 0;}
int rc_i2c_read_byte(int cBus, int cReg, unsigned char *cData){return 0;}
int rc_i2c_write_byte(int cBus, int cReg, unsigned char *cData){return 0;}
int rc_i2c_close(int cBus){return 0;}
int rc_gpio_init(int cChip,int cPin, int cFlag){return 0;}
int rc_gpio_set_value(int cChip,int cPin,int cValue){return 0;}
int rc_gpio_cleanup(int cChip,int cPin){return 0;}
int rc_gpio_init_event(int cChip,int cPin,int cFlagH,int cFlagE){return 0;}
int rc_gpio_poll(int cChip,int cPin,int cTimeOut, void* cET){return 0;}

#define GPIOHANDLE_REQUEST_OUTPUT 1
#define GPIOHANDLE_REQUEST_ACTIVE_LOW 1
#define RC_GPIOEVENT_FALLING_EDGE 1
#define RC_GPIOEVENT_RISING_EDGE 1
#define RC_GPIOEVENT_TIMEOUT 1