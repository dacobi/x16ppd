
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

#ifdef __arm__
    #include "pportbone.h"
#else
    #include "pportlpt.h"
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