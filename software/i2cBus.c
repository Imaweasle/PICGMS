/*
 * File:   i2cBus.c
 * Author: lydia
 *
 * Created on April 25, 2026, 5:58 PM
 */


#include "xc.h"
#include "i2cBus.h"











volatile int elapsedTime_ms;



void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;
    elapsedTime_ms++;
    
    
}




void startTimer() {
    elapsedTime_ms = 0;
    TMR1 = 0;
    T1CONbits.TON = 1;
}

void endTimer() {
    T1CONbits.TON = 0;
}

int i2cInit() {
    //Set baud to 100 kHz
    I2C1BRG = 157;
    I2C1CONbits.I2CEN = 1;
    
    
    I2C1CONbits.I2CSIDL = 1;

    //Set up timer 1 for a ~1 millesecond period
    T1CON = 0;
    TMR1 = 0;
    PR1 = 15999;
    T1CONbits.TCKPS = 0b00;
    T1CONbits.TON = 0; //Keep the timer off for now
    IEC0bits.T1IE = 1; //enable Timer 1 interrupts

    return 0;

}

int startSignal() {
    _MI2C1IF = 0;
    
    I2C1CONbits.SEN = 1;
    
    startTimer();
    while(I2C1CONbits.SEN) {
        if(elapsedTime_ms > timeoutTime) {
            return -1;
        }
    }
    endTimer();
    
    //Waiting for SEN to finish
    _MI2C1IF = 0;
    
    return 0;
    
}

int endSignal() {
    _MI2C1IF = 0;

    
    I2C1CONbits.PEN = 1;
    startTimer();
    while(I2C1CONbits.PEN) {
        if(elapsedTime_ms > timeoutTime) {
            return -1;
        }
    }
    endTimer();
    
    //Waiting for PEN to finish before setting interrupt to false again
    _MI2C1IF = 0;
    
    return 0;
}

int i2cOut(uint8_t addr, uint8_t cmd, uint8_t* data, uint8_t packetSize) {
    
    int buf = startSignal();
    if(buf) {
        return buf;
    }
    
    
    
     _MI2C1IF = 0;
    
    I2C1TRN = (addr << 1);
    
    //10 millesecond delay
    startTimer();
    while(!(_MI2C1IF && !I2C1STATbits.TRSTAT)) {
        if(elapsedTime_ms > timeoutTime) {
            endSignal();
            return -2;
        }
    
    }
    endTimer();
    
    _MI2C1IF = 0;
    int i = 0;
    
    while(packetSize) {

        //Command or data mode
        I2C1TRN = cmd;
        startTimer();
        while(!(_MI2C1IF && !I2C1STATbits.TRSTAT)) {
            if(elapsedTime_ms > timeoutTime) {
                endSignal();
                return -2;
            }

        }
        endTimer();


        _MI2C1IF = 0;

        I2C1TRN = data[i];
        startTimer();
        while(!(_MI2C1IF && !I2C1STATbits.TRSTAT)) {
            if(elapsedTime_ms > timeoutTime) {
                endSignal();
                return -2;
                
            }

        }
        endTimer();

        _MI2C1IF = 0;
        
        packetSize--;
        i++;
    }
    
    buf = endSignal();
    if(buf){
        return buf;
    } else {
        return 0;
    }
    
}

int i2cIn(uint8_t addr, uint8_t reg, uint8_t* dataArr, uint8_t packetSize) {
    int buf = startSignal();
    if(buf) {
        return buf;
    }
    
    _MI2C1IF = 0;
    
    I2C1TRN = (addr << 1) | 1;
     
    //10 millesecond delay
    startTimer();
    while(!(_MI2C1IF && !I2C1STATbits.TRSTAT)) {
        if(elapsedTime_ms > timeoutTime) {
            endSignal();
            return -2;
        }
    
    }
    endTimer();
    
    _MI2C1IF = 0;//Command or data mode
        I2C1TRN = reg;
        startTimer();
        while(!(_MI2C1IF && !I2C1STATbits.TRSTAT)) {
            if(elapsedTime_ms > timeoutTime) {
                endSignal();
                return -2;
            }

        }
        endTimer();
    
    
    
    //byte size
    int i = 0;
    while(packetSize) {


        _MI2C1IF = 0;

        
        I2C1CONbits.RCEN = 1;
        
        startTimer();
        
        while(!(_MI2C1IF && !I2C1STATbits.RBF)) {
            if(elapsedTime_ms > timeoutTime) {
                endSignal();
                return -2;
                
            }

        }
        dataArr[i] = I2C1RCV;
        
        
        endTimer();

        
        i++;
        packetSize--;
        
        
        if(packetSize) {
            I2C1CONbits.ACKEN = 1;
        }
    }
    
    
    
    buf = endSignal();
    if(buf) {
        return buf;
    } else {
        return 0;
    }
    
}