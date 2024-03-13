#ifdef __arm__

#include "pportbone.h"

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

    unsigned char mInitByte;

    mInitByte = IOCON::BANK;

    if(rc_i2c_write_byte(mBus, MCP23017Reg::IOCON, &mInitByte) == PP_ERROR){
        return true;
    }

    mInitByte = 0x00;

    if(rc_i2c_write_byte(mBus, MCP23017Reg::IODIR_B, &mInitByte) == PP_ERROR){
        return true;
    }

    setMode(PP_INPUT);

    return false;
}

void PPort::test_i2c(){
    
    if(init()){
        std::cout << "ERROR!!!" << std::endl;
        exit(1);
    }

    int cCount = 100;
    int cDel = 10000000;

    while(cCount--){
        setMode(PP_INPUT);
        std::cout << "Read: " << (int)read() << std::endl;
        setMode(PP_OUTPUT);
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

    unsigned char mRead;

    int retval = rc_i2c_read_byte(mBus, MCP23017Reg::GPIO_A, &mRead);

    if(retval == PP_ERROR){
        mPPd.throwError(PPDERR_FATAL_IO, "I2C IO Error!");        
    }

    // std::cout << "I2C Read: " << (int)mRead << std::endl;

    return mRead;
}

void PPort::write(unsigned char cByte){

    unsigned char mWrite;

    mWrite = cByte;
    
    int retval = rc_i2c_write_byte(mBus, MCP23017Reg::GPIO_B, &mWrite);

    if(retval == PP_ERROR){
        mPPd.throwError(PPDERR_FATAL_IO, "I2C IO Error!");
    }
}

void PPort::setMode(int cMode){

    mMode = cMode;

    mOutPin.setValue(PP_HIGH);
    mInPin.setValue(PP_HIGH);

    if(mMode == PP_INPUT){        
        mInPin.setValue(PP_LOW);
    }

    if(mMode == PP_OUTPUT){
        mOutPin.setValue(PP_LOW);
    }
    
    return;
}

void PPort::changeMode(int cMode){

    if(mMode == cMode){
        return;
    }

    setMode(cMode);
}


#endif