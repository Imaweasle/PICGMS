#pragma once

/* 
 * File:   BME280.h
 * Author: lydia
 *
 * Created on April 26, 2026, 4:17 PM
 */
#include "i2cBus.h" 
#include "stdint.h"
#include "stdbool.h"
#ifndef BME280_H
#define	BME280_H

#ifdef	__cplusplus
extern "C" {
#endif


    
/**
 * We don't care about pressure sensors and I may have forgot how quickly the deadline for this was approaching
 * so we will not implement pressure sensing (it is not likely to change so I assume its not super useful)
 * @return 
 */
    
    
typedef struct {
    //These use the naming convention from the data sheet minus the dig_ part
    unsigned short t1;
    short t2;
    short t3;
    unsigned char h1;
    short h2;
    unsigned char h3;
    short h4;
    short h5;
}BME280Params; 
    

    
    
int initBME280();






#define NORMAL 1
#define SLEEP 0
#define FORCED 2

uint8_t mode = 0;

uint8_t configBuf = 0;


/**
 * sets the mode of the BME280
 * 
 * @param setting 0 for sleep, 1 for normal, 2 for forced
 * @return 
 */
int setMode(uint8_t setting);
    

int getId();



int32_t getTemp();

uint32_t getHumidity();


int getCalibData();


/**
 * 
 * @param setting
 * @return 
 */
int setOversampling(uint8_t tmp, uint8_t pres);


/**
 * 
 * @param setting
 * @return 
 */
int setFilter(uint8_t setting);

    
/**
 * 
 * @param setting if set to 0 one second period
 * @return 
 */
int setStandby(uint8_t setting);
    
int getCalibData();
    
    
    
    
    
    
    
    
    
    
    
    
//Spme data in this library comes from the BME280 adafruit driver 
//(the BME280 documentation has a lot of bloat and no comprehensive list of data addresses so enums may come from there)

//THIS IS A TEMPORARY VALUE, IT CAN BE CHANGED BETWEEN OX76 AND OX77 BY SDO WHICH WE WILL USE
#define BME280_ADDR 0x77    
    
/**
 * Register addresses
 */

     
#define BME280_REGISTER_DIG_T1 0x88
#define BME280_REGISTER_DIG_T2 0x8A
#define BME280_REGISTER_DIG_T3 0x8C

#define BME280_REGISTER_DIG_P1 0x8E
#define BME280_REGISTER_DIG_P2 0x90
#define BME280_REGISTER_DIG_P3 0x92
#define BME280_REGISTER_DIG_P4 0x94
#define BME280_REGISTER_DIG_P5 0x96
#define BME280_REGISTER_DIG_P6 0x98
#define BME280_REGISTER_DIG_P7 0x9A
#define BME280_REGISTER_DIG_P8 0x9C
#define BME280_REGISTER_DIG_P9 0x9E

#define BME280_REGISTER_DIG_H1 0xA1
#define BME280_REGISTER_DIG_H2 0xE1
#define BME280_REGISTER_DIG_H3 0xE3
#define BME280_REGISTER_DIG_H4 0xE4
#define BME280_REGISTER_DIG_H5 0xE5
#define BME280_REGISTER_DIG_H6 0xE7

    
//id register contains 0X60 and can be read as soon as power on reset is complete
#define BME280_REGISTER_CHIPID 0xD0
#define BME280_REGISTER_VERSION 0xD1
#define BME280_REGISTER_SOFTRESET 0xE0 //0XB6 written here results in the power-on-reset hardware tripping

#define BME280_REGISTER_CAL26 0xE1 // R calibration stored in 0xE1-0xF0
    
#define BME280_REGISTER_CAL0 0x88 //CAL0-CAL25 are sequential and CAL26-CAL41 are sequential

#define BME280_REGISTER_CONTROLHUMID 0xF2 //Controls oversampling of humidity data

/*
 The ?ctrl_meas? register sets the pressure and temperature data acquisition options of the device. The
register needs to be written after changing ?ctrl_hum? for the changes to become effective.
 
 There are two bits contained in this register that we care about,
 Bit 3 measuring[0] is automatically set to '1' when conversion is running and '0' when 
 results are transferred back to data registers
 bit 0 im_update[0] Automatically set to ?1? when the NVM data are being
copied to image registers and back to ?0? when the
copying is done. The data are copied at power-on-
reset and before every conversion.*/
#define BME280_REGISTER_STATUS 0XF3
    
    
/*
 * bits 7, 6, and 5 of this register control oversampling of temperature data
 * bits 4, 3, and 2 of this register control oversampling of pressure data
 * bits 1, and 0 control the sensor mode of the device 
 */    
#define BME280_REGISTER_CONTROL 0xF4
    
    
    

/*
 * The config register sets the rate, filter, and interface options of the device.
 * Writes to the config register in normal mode may be ignored, in sleep mode writes are not ignored
 * 
 * bits 7,6,5 control inactive duration in normal mode
 * 
 * Valid settings with time in milleseconds are 
 * 0b000 = 0.5 ms
 * 0b001 = 62.5 ms
 * 0b010 = 125 ms
 * 0b011 = 250 ms
 * 0b100 = 500 ms
 * 0b101 = 1000 ms
 * 0b110 = 10 ms
 * 0b111 = 20 ms
 * 
 * 
 * 
 * bits 4,3,2 control the time constant of the IIR low pas filter
 * 
 * Settings for this filter are
 * 0b000 = filter off
 * 0b001 = 2
 * 0b010 = 4
 * 0b011 = 8
 * 0b100 = 16 the last two bits don't matter here
 * 
 * bit 0 enables 3-wire SPI when set to 1
 * 
 * 
 * 
 */    
#define BME280_REGISTER_CONFIG 0xF5
    
    
/*
 * contains press_msb or the MSB part of the raw pressure data 20 bits of data
 */
#define BME280_REGISTER_PRESSUREDATA 0xF7
    
//Contains temp_msb or the MSB of the raw temperature data 20 bits of data 
#define BME280_REGISTER_TEMPDATA 0xFA

//Contains  hum_msb or the MSB part of the raw humidity data 16 bits of data
#define BME280_REGISTER_HUMIDDATA 0xFD
    
//These apply to all oversampling settings
#define BME280_SET_OVERSAMPLING_0X 0b000
#define BME280_SET_OVERSAMPLING_1X 0b001
#define BME280_SET_OVERSAMPLING_2X 0b010
#define BME280_SET_OVERSAMPLING_4X 0b011
#define BME280_SET_OVERSAMPLING_8X 0b100
#define BME280_SET_OVERSAMPLING_16X 0b101
    
//This applies to bits 1, and 0 of REGISTER_CONTROL 
#define BME280_SET_MODE_SLEEP 00
#define BME280_SET_MODE_FORCED 01
#define BME280_SET_MODE_NORMAL 11
    
    
    
    
    
 
    
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* BME280_H */

