#ifndef __PPORTBONE__
#define __PPORTBONE__ 

#include "pport.h"

#ifdef __arm__
    #include <rc/i2c.h>
    #include <rc/gpio.h>
#else
    #include "rcdummy.h"
#endif

enum class IOCON : unsigned char{
    BANK = 0x80
}; 

enum class MCP23017Reg : unsigned char{
    IODIR_A		= 0x00, 		///< Controls the direction of the data I/O for port A.
	IODIR_B		= 0x10,			///< Controls the direction of the data I/O for port B.
	IPOL_A		= 0x01,			///< Configures the polarity on the corresponding GPIO_ port bits for port A.
	IPOL_B		= 0x11,			///< Configures the polarity on the corresponding GPIO_ port bits for port B.
	GPINTEN_A	= 0x02,			///< Controls the interrupt-on-change for each pin of port A.
	GPINTEN_B	= 0x12,			///< Controls the interrupt-on-change for each pin of port B.
	DEFVAL_A	= 0x03,			///< Controls the default comparaison value for interrupt-on-change for port A.
	DEFVAL_B	= 0x13,			///< Controls the default comparaison value for interrupt-on-change for port B.
	INTCON_A	= 0x04,			///< Controls how the associated pin value is compared for the interrupt-on-change for port A.
	INTCON_B	= 0x14,			///< Controls how the associated pin value is compared for the interrupt-on-change for port B.
	IOCON		= 0x0A,			///< Controls the device.
    IOCONAI		= 0x05,			///< Controls the device.
	GPPU_A		= 0x06,			///< Controls the pull-up resistors for the port A pins.
	GPPU_B		= 0x16,			///< Controls the pull-up resistors for the port B pins.
	INTF_A		= 0x07,			///< Reflects the interrupt condition on the port A pins.
	INTF_B		= 0x17,			///< Reflects the interrupt condition on the port B pins.
	INTCAP_A	= 0x08,			///< Captures the port A value at the time the interrupt occured.
	INTCAP_B	= 0x18,			///< Captures the port B value at the time the interrupt occured.
	GPIO_A		= 0x09,			///< Reflects the value on the port A.
	GPIO_B		= 0x19,			///< Reflects the value on the port B.
	OLAT_A		= 0x0A,			///< Provides access to the port A output latches.
	OLAT_B		= 0x1A,			///< Provides access to the port B output latches.
};


class GPIO{
    public:
        int mChip;
        int mPin;
        int mValue;
        int mDefault = PP_HIGH;
};

class GPIOOut : public GPIO{
    public:        
        bool init(int cChip, int cPin, int cDefault = PP_HIGH);        
        void setValue(int cVal);
        void pulse();
        virtual void close();        
};


class GPIOInt : public GPIO{
    public:
        bool bActiveLow = true;
        bool init(int cChip, int cPin, bool cActiveLow = true);        
        int poll(int cTimeOut = -1);        
        virtual void close();        
};

class PPort{
    public:
        int mBus = 1;
        int mDevAddr = 0x20;
        int mMode = PP_DISABLED;
        int mState = PP_IDLE;
        unsigned char mOutData;
        unsigned char mInData;
        GPIOOut mOutPin;
        GPIOOut mInPin;
        GPIOOut mCA1;
        GPIOInt mCA2;
        bool init(int cBus = 1, int cDevAddr = 0x20, int cOutChip = 3, int cOutPin = 17, int cInChip = 3, int cInPin = 20, int cCA2Chip = 1, int cCA2Pin = 17, int cCA1Chip = 1, int cCA1Pin = 25);
        unsigned char read();
        void write(unsigned char cByte);        
        unsigned char recive();
        void send(unsigned char cByte);        
        void setMode(int cMode);  
        void setState(int cState); 
        void changeMode(int cMode);        
        void handleState();
        void handleState(int cState);
        void test_i2c();
        void close();
};



#endif