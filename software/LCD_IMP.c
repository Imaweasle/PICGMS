/*
 * File:   LCD_IMP.c
 * Author: jimba
 *
 * Created on April 23, 2026, 11:32 PM
 */


#include <xc.h>
#include "CN0296D.h"
#include <libpic30.h> 
#include <stdio.h>

// CW1: FLASH CONFIGURATION WORD 1
#pragma config ICS = PGx1
#pragma config FWDTEN = OFF
#pragma config GWRP = OFF
#pragma config GCP = OFF
#pragma config JTAGEN = OFF
 
// CW2: FLASH CONFIGURATION WORD 2
#pragma config I2C1SEL = PRI
#pragma config IOL1WAY = OFF
#pragma config OSCIOFNC = ON
#pragma config FCKSM = CSECME
#pragma config FNOSC = FRCPLL

int main(void) {

    // Initialize the LCD
    lcd_init();

    // Print to the screen
    lcd_setCursor(0, 0);
    lcd_printStr("Library Loaded!");

    lcd_setCursor(7, 2);
    lcd_printStr(" :3 ");
    
    
    // Define the heart pixels (5x8 grid)
    const unsigned char heart[8] = {
        0b00000,
        0b01010,
        0b11111,
        0b11111,
        0b11111,
        0b01110,
        0b00100,
        0b00000
    };
    
    //Create it in slot 0 
    lcd_createChar(0, heart);

    // Print it to the screen!
    lcd_setCursor(11, 2);
    lcd_printChar(0); // Print whatever is saved in slot 0'
    
    lcd_setCursor(6, 2);
    lcd_printChar(0); // Print whatever is saved in slot 0



    while (1) {
        // Main loop
    }

    return 0;
}