
#include "pumpctrl.h"



time_t universalClock;

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




void pumpInit() {
    reset(&universalClock);
    
    
    reset(&pumpT1);
    reset(&pumpT2);
    reset(&pumpT3);
    reset(&pumpT4);
    
    pumpState1 = 0;
    pumpState2 = 0;
    pumpState3 = 0;
    pumpState4 = 0;
    
    activePeriod1 = 60;
    activePeriod2 = 60;
    activePeriod3 = 60;
    activePeriod4 = 60;
    
    inactivePeriod1 = 10;
    inactivePeriod2 = 10;
    inactivePeriod3 = 10;
    inactivePeriod4 = 10;
    
    //We are gonna assume that TRISA is set correctly before
    
}


void runPumpMaintenance() {
    update(&universalClock);
    if(timeCompare(&universalClock, &pumpT1)) {
        
        if(pumpState1) {
            //requires pump to be on and we are turning it off
            incTime(&pumpT1, 0, 0, 0, inactivePeriod1, 0);
        } else {
            //Pump is off we turn it on for active period
           incTime(&pumpT1, 0, activePeriod1, 0, 0, 0); 
        }
        pumpState1 = !pumpState1;
    }
    if(timeCompare(&universalClock, &pumpT2)) {
        
        if(pumpState2) {
            //requires pump to be on and we are turning it off
            incTime(&pumpT2, 0, 0, 0,inactivePeriod2, 0);
        } else {
            //Pump is off we turn it on for active period
           incTime(&pumpT2, 0, activePeriod2, 0, 0, 0); 
        }
        pumpState2 = !pumpState2;
    }
    if(timeCompare(&universalClock, &pumpT3)) {
        
        if(pumpState3) {
            //requires pump to be on and we are turning it off
            incTime(&pumpT3, 0, 0, 0, inactivePeriod3, 0);
        } else {
            //Pump is off we turn it on for active period
           incTime(&pumpT3, 0, activePeriod3, 0, 0, 0); 
        }
        pumpState3 = !pumpState3;
    }
    if(timeCompare(&universalClock, &pumpT4)) {
        
        if(pumpState4) {
            //requires pump to be on and we are turning it off
            incTime(&pumpT4, 0, 0, 0, inactivePeriod4, 0);
        } else {
            //Pump is off we turn it on for active period
           incTime(&pumpT4, 0, activePeriod4, 0, 0, 0); 
        }
        pumpState4 = !pumpState4;
    }
    
    //We assume this was setup correctly
    LATAbits.LATA2 = pumpState1;
    LATAbits.LATA3 = pumpState2;
    LATBbits.LATB4 = pumpState3;
    LATAbits.LATA4 = pumpState4;

}

void setWaterFreq(uint8_t pump, uint8_t hours) {
    switch(pump) {
        case 1:
            inactivePeriod1 = hours;
            break;
        case 2:
            inactivePeriod2 = hours;
            break;
        case 3:
            inactivePeriod3 = hours;
            break;
        case 4:
            inactivePeriod4 = hours;
            break;
    }
}
    
void setWaterRate(uint8_t pump, uint8_t seconds) {
    switch(pump) {
        case 1:
            activePeriod1 = seconds;
            break;
        case 2:
            activePeriod2 = seconds;
            break;
        case 3:
            activePeriod3 = seconds;
            break;
        case 4:
            activePeriod4 = seconds;
            break;
    } 
}