#include "x16ppd.h"

PPDaemon mPPd;

extern "C" {

void mypidkill(int signum){

    switch (signum){

        case SIGTERM:
            mPPd.throwError(PPDERR_PIDKILL, "Signal Caught: SIGTERM");
            break;
        case SIGKILL:
            mPPd.throwError(PPDERR_PIDKILL, "Signal Caught: SIGKILL");
            break;    
        case SIGINT:
            mPPd.throwError(PPDERR_PIDKILL, "Signal Caught: SIGINT");
            break;    
        default:
            mPPd.throwError(PPDERR_UNKNOWN, "Signal Caught: UNKNOWN!");
            break;
    }

}

}
bool PPDaemon::init(){

    if(mPort.init()){
        return true;
    }

    setMode(PPDM_IDLE);
    setState(PPDS_WAITCMDB);

    return false;
}

void PPDaemon::send(unsigned char cData){

}

unsigned char PPDaemon::recive(){

    unsigned char cByte = 0x00;


    return cByte;
}

void PPDaemon::send(std::string cStrSend){

}

void PPDaemon::send(int cBytes){

}

void PPDaemon::recive(int cBytes){

}

void PPDaemon::handleEvent(int cEvent){

}

void PPDaemon::handleState(int cState){

    setState(cState);

    handleState();
}

void PPDaemon::handleState(){

    switch (mState)
    {
    case PPDS_WAITCMDB:
        
        break;
    
    default:
        break;
    }

}

void PPDaemon::setMode(int cMode){}
void PPDaemon::setState(int cState){}

void PPDaemon::throwError(int cError, std::string cErrMsg){

    mError = cError;
    throw std::runtime_error(cErrMsg);
}


void PPDaemon::handleError(std::string cErrMsg){
    switch (mError)
    {
    case PPDERR_PIDKILL:
        std::cout << "Program Exit: " << cErrMsg << std::endl;
        bRunning = false;
        break;    
    default:
        std::cout << "UNKNOWN ERROR!!! HARD EXIT: " << cErrMsg << std::endl;
        exit(1);
        break;
    }

}
        

int PPDaemon::run(){

    int retval = 0;

    while (bRunning){

        try{
            switch (mMode)
            {
            case PPDM_IDLE :
                handleState(PPDS_WAITCMDB);

                switch (mInData){
                    case PPDCMD_HOST:
                        setMode(PPDM_HOSTARGS);                
                        break;                
                    default:
                        setMode(PPDM_IDLE);                    
                        break;
                }

                break;

            case PPDM_HOSTARGS :
                    handleState(PPDS_REVICECMDB);

                    switch (mInData){
                        case HOST_RESET:
                            handleEvent(PPDE_RESET);
                            break;                
                        case HOST_STATUS:
                            handleEvent(PPDE_STATUS);
                            break;                
                        default:
                            setMode(PPDM_IDLE);                    
                            break;
                    }

                    break;

            default:
                break;
            }



        } catch(std::exception &e){
            if(mError == PPDERR_NONE){
                mError = PPDERR_UNKNOWN;
            }

            handleError(e.what());
        }

    }

    return retval;
}


int main(int argc, char *argv[]){

    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = mypidkill;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGKILL, &action, NULL);
    sigaction(SIGINT, &action, NULL);

/*
    int retval; 

    if(mPPd.init()){
         std::cout << "PPort: Init Error!" << std::endl;
         return 1;
    }

    retval = mPPd.run();
    
    std::cout << "Shutdown..." << std::endl;

    mPPd.close();

    return retval;
*/
    try{
        mPPd.mPort.test_i2c();
    } catch(std::exception &e){        
        mPPd.handleError(e.what());
    }

    std::cout << "Shutdown..." << std::endl;

    return 0;
}