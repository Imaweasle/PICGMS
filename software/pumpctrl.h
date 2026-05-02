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

    
    
    void pumpInit();
    
    void runPumpMaintenance();
    
    void setWaterFreq(uint8_t pump, uint8_t hours);
    
    void setWaterRate(uint8_t pump, uint8_t seconds);
    
    
    
    
    
    
    



#ifdef	__cplusplus
}
#endif

#endif	/* PUMPCTRL_H */

