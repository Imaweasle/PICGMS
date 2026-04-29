#pragma once

/* 
 * File:   i2cBus.h
 * Author: lydia
 *
 * Created on April 25, 2026, 5:58 PM
 */

#ifndef I2CBUS_H
#define	I2CBUS_H

#include "stdint.h"
#include "stdbool.h"
#include "xc.h"

#ifdef	__cplusplus
extern "C" {
#endif
    

#define timeoutTime 10

volatile int elapsedTime_ms;

void startTimer();

void endTimer();

int startSignal();

int endSignal();

int i2cOut(uint8_t addr, uint8_t cmd, uint8_t data, uint8_t packetSize, bool rnw);

int i2cInit();


int i2cIn(uint8_t addr, uint8_t reg, uint8_t* dataArr, uint8_t packetSize);




#ifdef	__cplusplus
}
#endif

#endif	/* I2CBUS_H */

