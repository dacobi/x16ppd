
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
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
    PPDM_HOST,
    PPDM_PING, 
    PPDM_WGET
} ppd_mode;

enum{
    PPDS_WAIT,
    PPDS_WAITCMD,
    PPDS_WAITCNK,
    PPDS_REVICE, 
    PPDS_REVICECMD, 
    PPDS_REVICECNK, 
    PPDS_SEND,    
    PPDS_SENDCNK
} ppd_state;

enum{
    PPDR_ERROR = 0,
    PPDR_DONE = 0,
    PPDR_QUIT = 0,
    PPDR_OK = 1,
    PPDR_MORE = 1
} pdd_revtal;

class GPIO{
    public:
        int mChip;
        int mPin;
        int mValue;
        int mDefault = PP_HIGH;
        virtual void close();
};

class GPIOOut : public GPIO{
    public:
        ~GPIOOut();
        bool init(int cChip, int cPin, int cDefault = PP_HIGH);
        void setValue(int cVal);
        void pulse();
        virtual void close();        
};

class GPIOInt : public GPIO{
    public:
        ~GPIOInt();
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

class PPCmd{
    public:
        std::string mCmd;
        std::vector<std::string> mArgs;
        virtual int init(std::string cCmd, int cArgNum);
        void setArg(int cArgNum, std::string cArg);
        virtual void run();
};

class PPCmdBin : public PPCmd{
    public:
      virtual void run();
};

class PPCmdHostStat : public PPCmd{
    public:
      virtual void run();
};


class PPCmdGetRetVal : public PPCmd{
    public:
        virtual int check();
        virtual void run();
};


class PPCmdCheckRetVal : public PPCmd{
    public:
        PPCmdGetRetVal mCmdCheck;        
        virtual void run();
};


class PPDaemon {
    public:
        PPort mPort;
        int mMode = PPDM_IDLE;
        int mState = PPDS_WAITCMD;
        std::vector<unsigned char> mInBuf;
        std::vector<unsigned char> mOutBuf;
        bool init();
        void send(unsigned char cData);
        unsigned char recive();
        void send(std::string cStrSend);
        void send(int cBytes);
        void recive(int cBytes);
        void handleEvent(int cEvent);
};

