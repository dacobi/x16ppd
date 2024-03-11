
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include "pstream.h"

//#define NOBONE

#ifndef NOBONE
    #include <rc/i2c.h>
    #include <rc/gpio.h>
#endif

enum{
    PP_ERROR=-1,
    PP_LOW=0,
    PP_HIGH=1 
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
    PPDM_HOSTARGS,
    PPDM_HOST,
    PPDM_PINGARGS, 
    PPDM_PING, 
    PPDM_WGETARGS,
    PPDM_WGET
} ppd_mode;

enum{
    PPDS_IDLE,
    PPDS_WAITB,
    PPDS_WAITCNK,    
    PPDS_WAITCMDB,        
    PPDS_WAITCMDCNK,
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
    PPDVAL_NONE,
    PPDVAL_TOIO,
    PPDVAL_TOPRG,
    PPDVAL_ROOT
} ppd_values;

enum{
    PPDERR_NONE,
    PPDERR_TIMEOUT_IO,
    PPDERR_TIMEOUT_PROG,
    PPDERR_CMD_ERROR,
    PPDERR_CMD_UNKNOWN,
    PPDERR_FATAL_IO,
    PPDERR_UNKNOWN
} pdd_error;

enum {
    PPDE_NONE,
    PPDE_RESET,
    PPDE_STATUS,
    PPDE_RESTART,
    PPDE_SHUTDOWN
} ppd_event;

enum{
    PPDCMD_HOST,
    PPDCMD_PING,
    PPDCMD_WGET
} ppd_cmds;

enum{
    HOST_RESET,
    HOST_STATUS,
    HOST_SAVE,
    HOST_RESTART,        
    HOST_SHUTDOWN
} host_args;

#ifndef NOBONE

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

#else

class PPort{
    public:
        bool init(){return false;};
        unsigned char read(){return 0x00;};
        void write(unsigned char cByte){};        
        unsigned char recive(){return 0x00;};
        void send(unsigned char cByte){};        
        void setMode(int cMode){};  
        void setState(int cState){}; 
        void changeMode(int cMode){};        
        void handleState(){};
        void handleState(int cState){};
        void close(){};
};

#endif


class PPCmd{
    public:
        std::string mCmd;
        std::vector<std::string> mArgs;
        virtual int init(std::string cCmd, int cArgNum);
        void setArg(int cArgNum, std::string cArg);
        std::string getCmd();
        virtual void run();
};

class PPCmdGetRetVal : public PPCmd{
    public:
        virtual int check();
        virtual void run();
};


class PPCmdCheckRetVal : public PPCmd {
    public:
        PPCmdGetRetVal mCmdCheck;
};

class PPCmdHostStat : public PPCmd{
    public:
        PPCmdHostStat();
        virtual void run();
};

class PPCmdPing : public PPCmd{
    public:
        PPCmdPing();
        void setHost(std::string cHost);
        void setCount(std::string cCount);        
        virtual void run();
};

class PPCmdWget : public PPCmdCheckRetVal{
    public:
        PPCmdWget();
        void setURL(std::string cURL);                
        virtual void run();
};


class PPDaemon {
    public:
        PPort mPort;
        int mMode = PPDM_INIT;
        int mState = PPDS_IDLE;
        int mError = PPDERR_NONE;
        redi::pstream mProcess;
        unsigned char mOutData;
        unsigned char mInData;        
        std::vector<unsigned char> mOutBuf;
        std::vector<unsigned char> mInBuf;
        bool bRunning = true;
        bool init();
        void send(unsigned char cData);
        unsigned char recive();
        void send(std::string cStrSend);
        void send(int cBytes);
        void recive(int cBytes);
        void setMode(int cMode);  
        void setState(int cState); 
        void handleEvent(int cEvent);
        void throwError(int cError, std::string cErrMsg);
        void handleError(std::string cErrMsg);
        void handleState();
        void handleState(int cState);
        int getValue(int cVal);
        int run();
        void close();
};

PPDaemon mPPd;