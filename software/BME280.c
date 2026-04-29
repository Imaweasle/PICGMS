

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
    
    
    //2 chars and 3 shorts is 7 bytes h1 is nonsequential
    uint8_t hDat[8] = {0, 0, 0, 0, 0, 0, 0};
    
    i2cIn(BME280_ADDR, BME280_REGISTER_DIG_T1, tDat, 6);
    i2cIn(BME280_ADDR, BME280_REGISTER_DIG_H1, &calibData.h1, 1);
    i2cIn(BME280_ADDR, BME280_REGISTER_DIG_H2, hDat, 7);
    
    calibData.t1 = ((unsigned short) tDat[0] << 8) + ((unsigned short tDat[1]));
    calibData.t2 = (((short) tDat[2]) << 8) + ((short) tDat[3]);
    calibData.t3 = (((short) tDat[4]) << 8) + ((short) tDat[5]);
    
    calibData.h2 = (((short) hdat[0]) << 8) + ((short) hdat[1]);
    calibData.h3 = hdat[2];
    calibData.h4 = (((short) hdat[3] << 8)) + ((short) hdat[4]);
    calibData.h5 = (((short) hdat[5] << 8)) + ((short) hdat[6]);
    calibData.h6 = ((char)hdat[7]);
    
    
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


//This is taken from pseudocode in the documentation
//returns temp in DegC, resolution is 0.01 DegC.  Output value of 5123 equals 51.23 DegC
int32_t getTemp() {
    uint8_t buf[3] = {0, 0, 0};
    i2cIn(BME280_ADDR, BME_REGISTER_TEMPDATA, buf, 3);
    uint32_t adct = (((int32_t) buf[0])<<16) + (((int32_t) buf[1]) << 8) + ((int32_t) buf[2]);
    
    int32_t var1, var2, T;
    var1 = ((((adct>>3)-((int32_t)calibData->t1))) * ((int32_t calibData->t2)) >> 11);
    var2 = (((((adct>>4)-((int32_t)calibData->t1)) * ((adct>>4)-((int32_t)calibData->t1))) >> 12)*((int32_t)calibData->t3)) >> 14;
    tFine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

//I have no fucking clue
uint32_t getHum() {
    uint8_t buf[2] = {0, 0};
    i2cIn(BME280_ADDR, BME_REGISTER_HUMIDDATA, buf, 2);
    int32_t adch = (((int32_t) buf[0]) << 8) + ((int32_t) buf[1]);
    
    v_x1_32r = (tFine - ((int32_t) 76800));
    
    v_x1_u32r = (((((adch << 14) - (((int32_t)calibData->h4) << 20) - (((int32_t)calibData->h5) * v_x1_u32r)) + ((int32_t)16384)) >> 15)
            * (((((((v_x1_u32r * ((int32_t)calibData->h6)) >> 10) * (((v_x1_u32r * ((int32_t)calibData->h3)) >> 11) + ((int32_t)32768))) >> 10)
            +((int32_t)2097152))*((int32_t)calibData->h2)+8192)>>14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)calibData->h1)) >> 4));
    v_x1_u32r = ( v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
    return((uint32_t)(v_x1_u32r>>12));
}