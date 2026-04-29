#pragma once

/* 
 * File:   pumpctrl.h
 * Author: lydia
 *
 * Created on April 28, 2026, 5:24 PM
 */

#ifndef PUMPCTRL_H
#define	PUMPCTRL_H

#include "stdbool.h"
#include "stdint.h"
#include "xc.h"
#include "timingStruct.h"

#ifdef	__cplusplus
extern "C" {
#endif

    time_t universalClock;
    
    void pumpInit();
    
    void runPumpMaintenance();
    
    
    //Times set for next pump Toggle
    time_t pumpT1;
    time_t pumpT2;
    time_t pumpT3;
    time_t pumpT4;
    
    //these will be set false in pumpinit();
    bool pumpState1;
    bool pumpState2;
    bool pumpState3;
    bool pumpState4;
    
    
    //How long in seconds each pump remains active
    uint8_t activePeriod1;
    uint8_t activePeriod2;
    uint8_t activePeriod3;
    uint8_t activePeriod4;
    
    //This is in hours and controls the inactive pump period
    uint8_t inactivePeriod1;
    uint8_t inactivePeriod2;
    uint8_t inactivePeriod3;
    uint8_t inactivePeriod4;
    
    
    



#ifdef	__cplusplus
}
#endif

#endif	/* PUMPCTRL_H */

