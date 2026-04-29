#pragma once
/* 
 * File:   timingStruct.h
 * Author: lydia
 *
 * Created on April 28, 2026, 4:52 PM
 */

#ifndef TIMINGSTRUCT_H
#define	TIMINGSTRUCT_H

#include "stdint.h"
#incldue "stdbool.h"
#include "xc.h"

#ifdef	__cplusplus
extern "C" {
#endif
   
    
    volatile unsigned int timePassed_ms;
    
    
    typedef struct {
        
        
        //milleseconds (should make it roll over every day)
        uint64_t ms;
        
        //seconds
        uint32_t s;
        
        uint16_t minutes;
        
        uint8_t hours;
        
        //If this stays on for more than a few years im impressed
        uint16_t days;
        
        
        
    }time_t;

    //does time_t arithmetic outside of interrupts timeElapsed is in ms
    void update(time_t* time);
        
    //sets all values of a time_t to zeros
    void reset(time_t* time);
    
    void timeInit();
    
    //compare two time structs, if the first is greater than the second return 1
    bool timeCompare(time_t* time1, time_t* time2);
    
    void setTime(time_t* time, uint64_t milleseconds, uint32_t seconds, uint16_t minutes, uint8_t hours, uint16_t days);
    void incTime(time_t* time, uint64_t milleseconds, uint32_t seconds, uint16_t minutes, uint8_t hours, uint16_t days);
        


#ifdef	__cplusplus
}
#endif

#endif	/* TIMINGSTRUCT_H */

