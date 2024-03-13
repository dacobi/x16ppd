#ifndef __PPORTBONE__
#define __PPORTBONE__ 

#ifdef __arm__
    #include "pport.h"
    #include <rc/i2c.h>
    #include <rc/gpio.h>


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

#endif