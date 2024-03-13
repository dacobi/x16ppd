#include "x16ppd.h"
     
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
void PPDaemon::throwError(int cError, std::string cErrMsg){}
void PPDaemon::handleError(std::string cErrMsg){}
        

int PPDaemon::run(){

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
}


int main(int argc, char *argv[]){

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

    mPPd.mPort.test_i2c();

    return 0;
}