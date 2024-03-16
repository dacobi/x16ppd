#ifndef __PPORTLPT__
#define __PPORTLPT__ 

#include "pport.h"

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
        void test_i2c(){};
};

#endif