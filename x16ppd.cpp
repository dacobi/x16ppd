#include "x16ppd.h"

#ifndef NOBONE

bool GPIOOut::init(int cChip, int cPin, int cDefault){
    
    mChip = cChip;
    mPin = cPin;
    mDefault = cDefault;

    if( rc_gpio_init(mChip, mPin, GPIOHANDLE_REQUEST_OUTPUT) == PP_ERROR ){
        return true;
    }

    mValue = mDefault;

    rc_gpio_set_value(mChip, mPin, mDefault);

    return false;
}

void GPIOOut::setValue(int cVal){

    mValue = cVal;

    rc_gpio_set_value(mChip, mPin, mValue);
}

void GPIOOut::pulse(){

    if(mValue){
        rc_gpio_set_value(mChip, mPin, PP_LOW);
        rc_gpio_set_value(mChip, mPin, PP_HIGH);
    } else {
        rc_gpio_set_value(mChip, mPin, PP_HIGH);
        rc_gpio_set_value(mChip, mPin, PP_LOW);
    }

}

void GPIOOut::close(){

    rc_gpio_set_value(mChip, mPin, mDefault);

    rc_gpio_cleanup(mChip, mPin);
}

bool GPIOInt::init(int cChip, int cPin, bool cActiveLow){

    mChip = cChip;
    mPin = cPin;

    bActiveLow = cActiveLow;

    if(bActiveLow){
        if( rc_gpio_init_event(mChip, mPin, GPIOHANDLE_REQUEST_ACTIVE_LOW, RC_GPIOEVENT_FALLING_EDGE) == PP_ERROR){
            return true;
        }
    } else {
        if( rc_gpio_init_event(mChip, mPin, 0, RC_GPIOEVENT_RISING_EDGE) == PP_ERROR){
            return true;        
        }
    }

    return false;
}

int GPIOInt::poll(int cTimeOut){

    int retval = rc_gpio_poll(mChip, mPin, cTimeOut, NULL);

    if(retval == RC_GPIOEVENT_TIMEOUT){
        return 1;
    }

    return 0;
}   

void GPIOInt::close(){

    rc_gpio_cleanup(mChip, mPin);

}      

bool PPort::init(int cBus, int cDevAddr, int cOutChip, int cOutPin, int cInChip, int cInPin, int cCA2Chip, int cCA2Pin, int cCA1Chip, int cCA1Pin){

    if(mOutPin.init(cOutChip, cOutPin) == PP_ERROR){
        return true;
    }

    if(mInPin.init(cInChip, cInPin) == PP_ERROR){
        return true;
    }

    if(mCA1.init(cCA1Chip, cCA1Pin) == PP_ERROR){
        return true;
    }

    if(mCA2.init(cCA2Chip, cCA2Pin) == PP_ERROR){
        return true;
    }

    setMode(PP_DISABLED);

    mBus = cBus;
    mDevAddr = cDevAddr;

    if(rc_i2c_init(mBus, mDevAddr) == PP_ERROR){
        return true;
    }

    setMode(PP_INPUT);

    return false;
}

void PPort::test_i2c(){

    mBus = 1;
    mDevAddr = 0x20;

    if(rc_i2c_init(mBus, mDevAddr) == PP_ERROR){
        std::cout << "ERROR!!!" << std::endl;
        exit(1);
    }

    int cCount = 100;
    int cDel = 10000000;

    while(cCount--){
        write(0x00);
        std::cout << "Read: ";
        read();
        std::cout << std::endl;
        write(0xAA);
        while(cDel--){}
        cDel = 10000000;
        write(0x55);
        while(cDel--){}
        cDel = 10000000;
    }
}

void PPort::close(){

    setMode(PP_DISABLED);

    mOutPin.close();
    mInPin.close();
    mCA2.close();
    mCA1.close();

    rc_i2c_close(mBus);
}

unsigned char PPort::read(){

    unsigned char mRead[2];

    unsigned char mWrite[2];

    mWrite[0] = 0xff;
    mWrite[1] = 0xff;

    int retval = rc_i2c_write_bytes(mBus, mDevAddr, 2, mWrite);

    retval = rc_i2c_read_bytes(mBus, mDevAddr, 2, mRead);

    if(retval == PP_ERROR){
        mPPd.throwError(PPDERR_FATAL_IO, "I2C IO Error!");        
    }

    std::cout << (int)mRead[0] << " - " << (int)mRead[1];

    return mRead[1];
}

void PPort::write(unsigned char cByte){

    unsigned char mWrite[2];

    mWrite[0] = cByte;
    mWrite[1] = 0xFF;

    int retval = rc_i2c_write_bytes(mBus, mDevAddr, 2, mWrite);

    if(retval == PP_ERROR){
        mPPd.throwError(PPDERR_FATAL_IO, "I2C IO Error!");
    }
}

void PPort::setMode(int cMode){

    mMode = cMode;

    mOutPin.setValue(PP_HIGH);
    mInPin.setValue(PP_HIGH);

    write(0x00);

    if(mMode == PP_INPUT){
        mInPin.setValue(PP_LOW);
        return;
    }

    if(mMode == PP_OUTPUT){
        mOutPin.setValue(PP_LOW);
        return;
    }

    return;
}

void PPort::changeMode(int cMode){

    if(mMode == cMode){
        return;
    }

    mMode = cMode;

    mOutPin.setValue(PP_HIGH);
    mInPin.setValue(PP_HIGH);

    if(mMode == PP_INPUT){
        mInPin.setValue(PP_LOW);
        return;
    }

    if(mMode == PP_OUTPUT){
        mOutPin.setValue(PP_LOW);
        return;
    }
}

#endif
     
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