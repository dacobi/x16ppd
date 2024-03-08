#include "x16ppd.h"

GPIOOut::~GPIOOut();
bool GPIOOut::init(int cChip, int cPin, int cDefault){

}

void GPIOOut::setValue(int cVal){

}

void GPIOOut::pulse(){

}

void GPIOOut::close(){

}


GPIOInt::~GPIOInt(){

}

bool GPIOInt::init(int cChip, int cPin, bool cActiveLow){

}

int GPIOInt::poll(int cTimeOut){

}   

void GPIOInt::close(){

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
