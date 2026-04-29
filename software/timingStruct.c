

#include "timingStruct.h"







void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;
    timePassed_ms++;
    
    
}




void timeInit() {
    //Set up timer 1 for a ~1 millesecond period
    T1CON = 0;
    TMR1 = 0;
    PR1 = 15999;
    T1CONbits.TCKPS = 0b00;
    T1CONbits.TON = 1; 
    IEC0bits.T2IE = 1; //enable Timer 1 interrupts
    
    timePassed_ms = 0;

}

void reset(time_t* time) {
    time->ms = 0;
    time->seconds = 0;
    time->minutes = 0;
    time->hours = 0;
    time->days = 0;
    
}

void update(time_t* time) {
   time->ms += timePassed_ms;
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
   if(hours >= 24) {
       time->days++;
       time->hours -= 24;
   }
}

bool timeCompare(time_t* time1, time_t* time2) {
    if(time1->days > time2->days) {
        return 1;
    }
    if(time1->hours > time2->hours) {
        return 1;
    }
    if(time1->minutes > time2->minutes) {
        return 1;
    }
    if(time1->s > time2->s) {
        return 1;
    }
    if(time1->ms > time2->ms) {
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