
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
#include "pstream.h"

enum{
    PP_LOW,
    PP_HIGH 
} pp_values;

enum {
    PP_DISABLED,
    PP_INPUT, 
    PP_OUTPUT
} pp_mode;

enum {
    PP_IDLE,
    PP_WAITREADY, 
    PP_READDATA,
    PP_SENDTAKEN,    
    PP_WRITEDATA,
    PP_SENDREADY,
    PP_WAITTAKEN
} pp_state;

enum{
    PPDM_INIT,
    PPDM_IDLE,
    PPDM_HOST,
    PPDM_PING, 
    PPDM_WGET
} ppd_mode;

enum{
    PPDS_IDLE,
    PPDS_WAITB,
    PPDS_WAITCMDB,
    PPDS_WAITCMDCNK,
    PPDS_WAITCNK,
    PPDS_REVICEB,     
    PPDS_REVICECNK, 
    PPDS_REVICECMDB, 
    PPDS_REVICECMDCNK, 
    PPDS_SENDB,    
    PPDS_SENDCNK
} ppd_state;

enum{
    PPDR_ERROR = 0,
    PPDR_DONE = 0,
    PPDR_QUIT = 0,
    PPDR_OK = 1,
    PPDR_MORE = 1
} pdd_revtal;

enum{
    PPDERR_NONE,
    PPDERR_TIMEOUT_IO,
    PPDERR_TIMEOUT_PROG,
    PPDERR_CMD_ERROR,
    PPDERR_CMD_UNKNOWN,
    PPDERR_FATAL_IO,
    PPDERR_UNKNOWN
} pdd_error;


class GPIO{
    public:
        int mChip;
        int mPin;
        int mValue;
        int mDefault = PP_HIGH;
        redi::pstream mProcess;
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
        GPIOOut mOutPin;
        GPIOOut mInPin;
        GPIOOut mCA1;
        GPIOInt mCA2;
        bool init(int cBus = 1, int cDevAddr = 0x20, int cOutChip = 3, int cOutPin = 17, int cInChip = 3, int cInPin = 20, int cCA2Chip = 1, int cCA2Pin = 17, int cCA1Chip = 1, int cCA1Pin = 25);
        unsigned char read();
        void write(unsigned char cByte);
        void read(vector<unsigned char> &cInBuf, int cBytes);
        void write(vector<unsigned char> &cOutBuf, int cBytes);
        void setMode(int cMode);   
        void changeMode(int cMode);
        void close();
};

class PPCmd{
    public:
        std::string mCmd;
        std::vector<std::string> mArgs;
        virtual int init(std::string cCmd, int cArgNum);
        void setArg(int cArgNum, std::string cArg);
        std::string getCmd();
        virtual void run();
};

class PPCmdStr : public PPCmd{
    public:
      virtual void run();
};

class PPCmdBin : public PPCmd{
    public:
      virtual void run();
};


class PPCmdHostStat : public PPCmdStr{
    public:
      virtual void run();
};


class PPCmdGetRetVal : public PPCmdStr{
    public:
        virtual int check();
        virtual void run();
};


class PPCmdCheckRetVal : public PPCmdBin{
    public:
        PPCmdGetRetVal mCmdCheck;        
        virtual void run();
};


class PPDaemon {
    public:
        PPort mPort;
        int mMode = PPDM_IDLE;
        int mState = PPDS_IDLE;
        int mError = PPDERR_NONE;
        redi::pstream mProcess;
        std::vector<unsigned char> mInBuf;
        std::vector<unsigned char> mOutBuf;
        bool init();
        void send(unsigned char cData);
        unsigned char recive();
        void send(std::string cStrSend);
        void send(int cBytes);
        void recive(int cBytes);
        void handleEvent(int cEvent);
        int run();
        void close();
};

PPDaemon mPPd;