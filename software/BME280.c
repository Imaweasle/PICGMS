

#include "xc.h"
#include "BME280.h"


BME280Params calibData;

int setMode(uint8_t setting) {
    mode = setting;
}

int initBME280() {
    setMode(NORMAL);
}


int getId() {
    
}


int getCalibData() {
    //3 shorts is 6 bytes
    uint8_t tDat[6] = {0, 0, 0, 0, 0, 0};
    
    
    //1 chars and 3 shorts is 7 bytes h1 is nonsequential
    uint8_t hDat[7] = {0, 0, 0, 0, 0, 0, 0};
    
    i2cIn(BME280_ADDR, BME280_REGISTER_DIG_T1, tDat, 6);
    i2cIn(BME280_ADDR, BME280_REGISTER_DIG_H1, &calibData.h1, 1);
    i2cIn(BME280_ADDR, BME280_REGISTER_DIG_T1, hDat, 7);
    
    calibData.t1 = ((unsigned short) tDat[0] << 8) + ((unsigned short tDat[1]));
    calibData.t2 = ((short) tDat[2] << 8) + ((short) tDat[3]);
    calibData.t3 = ((short) tDat[4] << 8) + ((short) tDat[5]);
    
    
}


int setStandby(uint8_t setting) {
    
    //set to 1 second standby 
    configBuf &= 0b10111100;
    return(i2cOut(BME280_ADDR, BME280_REGISTER_CONFIG, configBuf, 1));
    
}


int setFilter(uint8_t setting) {
    //set to 1 second standby 
    configBuf &= 0b11100000;
    return(i2cOut(BME280_ADDR, BME280_REGISTER_CONFIG, configBuf, 1));
    
}

int setOversampling(uint8_t tmp,  uint8_t pres) {
    
    //massage values into the correct bits in the register
    
    uint8_t data = tmp * 32 + pres * 4 + mode;
    
    return(i2cOut(BME280_ADDR, BME280_REGISTER_CONTROL, data, 1));
}