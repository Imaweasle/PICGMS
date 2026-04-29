
#include "pumpctrl.h"

void pumpInit() {
    
    universalClock.reset();
    
    reset(&pumpT1);
    reset(&pumpT2);
    reset(&pumpT3);
    reset(&pumpT4);
    
    pumpState1 = 0;
    pumpState2 = 0;
    pumpState3 = 0;
    pumpState4 = 0;
    
    activePeriod1 = 70;
    activePeriod2 = 70;
    activePeriod3 = 70;
    activePeriod4 = 70;
    
    inactivePeriod1 = 12;
    inactivePeriod2 = 12;
    inactivePeriod3 = 12;
    inactivePeriod4 = 12;
    
    //We are gonna assume that TRISA is set correctly before
    
}


void runPumpMaintenance() {
    update(&universalClock);
    if(timeCompare(&universalClock, &pumpT1)) {
        
        if(pumpState1) {
            //requires pump to be on and we are turning it off
            incTime(&pumpT1, 0, 0, 0, inactivePeriod1, 0)
        } else {
            //Pump is off we turn it on for active period
           incTime(&pumpT1, 0, activePeriod1, 0, 0, 0) 
        }
        pumpState1 = !pumpState1
    }
    if(timeCompare(&universalClock, &pumpT2)) {
        
        if(pumpState2) {
            //requires pump to be on and we are turning it off
            incTime(&pumpT2, 0, 0, 0, inactivePeriod2, 0)
        } else {
            //Pump is off we turn it on for active period
           incTime(&pumpT2, 0, activePeriod2, 0, 0, 0) 
        }
        pumpState2 = !pumpState2
    }
    if(timeCompare(&universalClock, &pumpT3)) {
        
        if(pumpState3) {
            //requires pump to be on and we are turning it off
            incTime(&pumpT3, 0, 0, 0, inactivePeriod3, 0)
        } else {
            //Pump is off we turn it on for active period
           incTime(&pumpT3, 0, activePeriod3, 0, 0, 0) 
        }
        pumpState3 = !pumpState3
    }
    if(timeCompare(&universalClock, &pumpT4)) {
        
        if(pumpState4) {
            //requires pump to be on and we are turning it off
            incTime(&pumpT4, 0, 0, 0, inactivePeriod4, 0)
        } else {
            //Pump is off we turn it on for active period
           incTime(&pumpT4, 0, activePeriod4, 0, 0, 0) 
        }
        pumpState4 = !pumpState4
    }
    
    //We assume this was setup correctly
    LATAbits.LATA2 = pumpState1;
    LATAbits.LATA3 = pumpState2;
    LATBbits.LATB4 = pumpState3;
    LATAbits.LATA4 = pumpState4;

}