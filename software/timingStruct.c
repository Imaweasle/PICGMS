

#include "timingStruct.h"




volatile unsigned int timePassed_ms;


void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;
    timePassed_ms++;
    
    
}




void timeInit() {
    //Set up timer 1 for a ~1 millesecond period
    T2CON = 0;
    TMR2 = 0;
    PR2 = 15999;
    T2CONbits.TCKPS = 0b00;
    T2CONbits.TON = 1; 
    IEC0bits.T2IE = 1; //enable Timer 1 interrupts
    
    timePassed_ms = 0;

}

void reset(time_t* time) {
    time->ms = 0;
    time->s = 0;
    time->minutes = 0;
    time->hours = 0;
    time->days = 0;
    
}

void update(time_t* time) {
   time->ms += timePassed_ms;
   timePassed_ms = 0;
   while(time->ms >= 1000) {
       time->s++;
       time->ms -= 1000;
   }
   while(time->s >= 60) {
       time->minutes++;
       time->s -= 60;
   }
   while(time->minutes >= 60) {
       time->hours++;
       time->minutes -= 60;
   }
   if(time->hours >= 24) {
       time->days++;
       time->hours -= 24;
   }
}


/*
 * Basically each time measurement is compared, then a 1 is given to any number that is higher than the other in its corresponding value big1 or big2.
 * This is a bitwise operation, so days will have a bigger impact than milliseconds.  The numbers will be in the form of 0b000,days,hours,minutes,seconds,milliseconds
 */
bool timeCompare(time_t* time1, time_t* time2) {
    uint8_t big1 = 0;
    uint8_t big2 = 0;
    
    if(time1->days > time2->days) {
        big1 += 16;
    } else if(time1->days < time2->days){
        big2 += 16;
    }
    if(time1->hours > time2->hours) {
        big1 += 8;
    } else if(time1->hours < time2->hours){
        big2 += 8;
    }
    if(time1->minutes > time2->minutes) {
        big1 += 4;
    } else if(time1->minutes < time2->minutes){
        big2 += 4;
    }
    if(time1->s > time2->s) {
        big1 += 2;
    } else if(time1->s < time2->s){
        big2 += 2;
    }
    if(time1->ms > time2->ms) {
        big1 += 1;
    } else if(time1->ms < time2->ms){
        big2 += 1;
    }
    if(big1 > big2) {
        return 1;
    }
    return 0;
    
}

void setTime(time_t* time, uint64_t milleseconds, uint32_t seconds, uint16_t minutes, uint8_t hours, uint16_t days) {
    time->ms = milleseconds;
    time->s = seconds;
    time->minutes = minutes;
    time->hours = hours;
    time->days = days;

}

void incTime(time_t* time, uint64_t milleseconds, uint32_t seconds, uint16_t minutes, uint8_t hours, uint16_t days) {
    
    time->ms += milleseconds;
    time->s += seconds;
    time->minutes += minutes;
    time->hours += hours;
    time->days += days;
}