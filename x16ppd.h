
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
    PPDM_IDLE,
    PPDM_RESET,
    PPDM_PING, 
    PPDM_WGET
} ppd_mode;


enum{
    PPDS_WAITING,
    PPDS_REVICE, 
    PPDS_SEND,
    PPDS_REVICEBYTES, 
    PPDS_SENDBYTES
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
        bool bActiveLow = true;
        bool init(int cChip, int cPin, bool cActiveLow = true);        
        int poll(int cTimeOut = -1);        
};

class PPort{
    public:
        int mBus = 1;
        int mDevAddr = 0x20;
        int mMode = PP_DISABLED;
        GPIOOut mOutPin;
        GPIOOut mInPin;
        GPIOOut mCA1;
        GPIOInt mCA2;
        bool init(int cBus = 1, int cDevAddr = 0x20, int cOutChip = 3, int cOutPin = 17, int cInChip = 3, int cInPin = 20, int cCA2Chip = 1, int CA2Pin = 17, int cCA1Chip = 1, int cCA1Pin = 25);
        unsigned char read();
        void write(unsigned char);
        void read(vector<unsigned char> &cInBuf, int cBytes);
        void write(vector<unsigned char> &cOutBuf, int cBytes);
        void setMode(int cMode);   
        void changeMode(int cMode);
};

class PPDaemon {
    PPort mPort;
    int mMode = PPDM_IDLE;
    int mState = PPDS_WAITING;
    vector<unsigned char> mInBuf;
    vector<unsigned char> mOutBuf;
    bool init();
    void send(unsigned char cData);
    unsigned char recive();
    void send(int cBytes);
    void recive(int cBytes);
    void handleEvent(int cEvent);
};

