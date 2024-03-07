
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <rc/i2c.h>
#include <rc/gpio.h> 

enum{
    PP_LOW,
    PP_HIGH 
} pp_values;

enum {
    PP_DISABLED,
    PP_INTUT, 
    PP_OUTPUT
} pp_mode;

enum{
    PPDS_WAITING,


} ppd_state;

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
        
};

class GPIOInt : public GPIO{
    public:
        bool init(int cChip, int cPin, int cDefault = PP_HIGH;        
        int poll(int cTimeOut = -1);
};

class PPort{
    public:
        int mBus = 1;
        int mDevAddr = 0x20;
        vector<unsigned char> mInBuf;
        vector<unsigned char> mOutBuf;
        GPIOOut mOutPin;
        GPIOOut mInPin;
        GPIOOut mCA1;
        GPIOInt mCA2;
        bool init(int cBus = 1, int cDevAddr = 0x20, int cOutChip = 3, int cOutPin = 17, int cInChip = 3, int cInPin = 20, int cCA2Chip = 1, int CA2Pin = 17, int cCA1Chip = 1, int cCA1Pin = 25);
        unsigned char read();
        void write(unsigned char);
        void read(int cBytes);
        void write(int cBytes);
        void setMode(int cMode);   
        void changeMode(int cMode);
};

class PPDaemon {
    PPort mPort;
    bool init();
    void send(unsigned char cData);
    unsigned char recive();
    void send(vector<unsigned char> &cData);
    vector<unsigned char> cData recive(int cBytes);
};

