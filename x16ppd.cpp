#include "x16ppd.h"

GPIOOut::~GPIOOut(){
    close(); 
}

bool GPIOOut::init(int cChip, int cPin, int cDefault){
    
    mChip = cChip;
    mPin = cPin;
    mDefault = cDefault;

    if( rc_gpio_init(mChip, mPin, GPIOHANDLE_REQUEST_OUTPUT) != 0 ){
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

    rc_gpio_cleanup(mChip, mPin)
}


GPIOInt::~GPIOInt(){
    close(); 
}

bool GPIOInt::init(int cChip, int cPin, bool cActiveLow){

    mChip = cChip;
    mPin = cPin;

    bActiveLow = cActiveLow;

    if(bActiveLow){
        if( rc_gpio_init_event(mChip, mPin, GPIOHANDLE_REQUEST_ACTIVE_LOW, RC_GPIOEVENT_FALLING_EDGE) == -1){
            return true;
        }
    } else {
        if( rc_gpio_init_event(mChip, mPin, 0, RC_GPIOEVENT_RISING_EDGE) == -1){
            return true;        
        }
    }

    return false;
}

int GPIOInt::poll(int cTimeOut){

    int retval = rc_gpio_poll(mChip, mPin, cTimeOut, NULL);

    if(retval == RC_GPIO_EVENT_TIMEOUT){
        return 1;
    }

    return 0;
}   

void GPIOInt::close(){

    if(bActiveLow){
        rc_gpio_set_value(mChip, mPin, PP_HIGH);
    } else {
        rc_gpio_set_value(mChip, mPin, PP_LOW);
    }

    rc_gpio_cleanup(mChip, mPin)

}      

bool PPort::init(int cBus, int cDevAddr, int cOutChip, int cOutPin, int cInChip, int cInPin, int cCA2Chip, int CA2Pin, int cCA1Chip, int cCA1Pin){

}

unsigned char PPort::read(){

}

void PPort::write(unsigned char){

}

void PPort::read(vector<unsigned char> &cInBuf, int cBytes){

}

void PPort::write(vector<unsigned char> &cOutBuf, int cBytes){

}

void PPort::setMode(int cMode){

}

void PPort::changeMode(int cMode){

}
     
bool PPDaemon::init(){

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

int PPDaemon::run(){

}
