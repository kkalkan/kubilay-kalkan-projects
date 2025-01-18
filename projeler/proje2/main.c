#include <stdbool.h>
#include <stdint.h>

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"

#define LCDPORT         GPIO_PORTB_BASE
#define LCDPORTENABLE   SYSCTL_PERIPH_GPIOB
#define RS              GPIO_PIN_0
#define E               GPIO_PIN_1
#define D4              GPIO_PIN_4
#define D5              GPIO_PIN_5
#define D6              GPIO_PIN_6
#define D7              GPIO_PIN_7

void LCD_init(void);                                //LCD initialization
void LCD_Command(unsigned char c);                  //Send command
void LCD_Show(unsigned char d);                     //Show a char

void LCD_Clear(void);                               //Clear the screen
void LCD_Print(char *s, char *d);                   //Print 2 lines
void LCD_PrintLn(char i, char *s);                  //Print specific line
void LCD_PrintJustify(char i, char *s, char *d);    //Print specific line floated left and floated right text
void LCD_Cursor(char x, char y);                    //Set cursor

volatile uint8_t hour = 0, minute = 0, second = 0;


void Timer0IntHandler(void) {
    char timeString[9];  // "00:00:00\0"
    updateClock(timeString);

    LCD_Clear();
    LCD_Print(timeString, "");

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}


int main(void) {
    initClock();
    initLCD();

    // Timer0 konfig�rasyonu
    setClock("00:00:00", 23, 58, 56);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() - 1);  // 1 saniye

    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);

    TimerEnable(TIMER0_BASE, TIMER_A);

    while (1) {
        // Ana d�ng� burada bo�
    }
}

void LCD_init() {

        SysCtlPeripheralEnable(LCDPORTENABLE);
        GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, RS,  0x00 );

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x20 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);


        LCD_Command(0x0F); //Turn on Lcd
        LCD_Clear(); //Clear screen

}

void LCD_Command(unsigned char c) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(10);

        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

}

void LCD_Show(unsigned char d) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(50000);

}

void LCD_Cursor(char x, char y){

    if (x==0) {
        LCD_Command(0x80 + (y % 16));
        return;
    }
    LCD_Command(0xC0 + (y % 16));

}

void LCD_Clear(void){

        LCD_Command(0x01);
        SysCtlDelay(10);

}


void LCD_Yaz(char* s){

    int j, p=1, i;
    for (j=0; j<strlen(s)||j<15; j++) {
        LCD_Cursor(0, 15-j);
        for (i=0; i<strlen(s); i++) {
            LCD_Show(s[i]);
        }

        SysCtlDelay(8000000/3);
    }


    if (strlen(s)>16) {
        while (p < strlen(s)-16) {
            LCD_Cursor(0,0);
            for (j=0; j<16; j++) {
                LCD_Show(s[p+j]);
            }
            SysCtlDelay(800000/3);
            p++;
        }
        i = p;
        while (p < strlen(s) + i) {
            LCD_Cursor(0,0);
            for (j=0; j<16; j++) {
                LCD_Show(s[(p + j) % strlen(s)]);
            }
            SysCtlDelay(800000/3);
            p++;
        }
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}


void LCD_PrintJustify(char i, char *s, char *d) {
    if (i==0) {
        for (i=0; i<strlen(s); i++) {
            LCD_Cursor(0, i);
            LCD_Show(s[i]);
        }
        for (i=0; i<strlen(d); i++) {
            LCD_Cursor(0, 15-i);
            LCD_Show(d[strlen(d)-i-1]);
        }
        LCD_Command(0xC0 + 16);
        return;
    }
    for (i=0; i<strlen(s); i++) {
        LCD_Cursor(1, i);
        LCD_Show(s[i]);
    }
    for (i=0; i<strlen(d); i++) {
        LCD_Cursor(1, 15-i);
        LCD_Show(d[strlen(d)-i-1]);
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}

void LCD_Print(char *s, char *d) {
    int j;
    for (j=0; j<16; j++) {
        if (j<strlen(s)) {
            LCD_Cursor(0,j);
            LCD_Show(s[j]);
        }
        if (j<strlen(d)) {
            LCD_Cursor(1,j);
            LCD_Show(d[j]);
        }
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}

void LCD_PrintLn(char i, char *s) {
    LCD_Cursor(i, 0);
    for (i=0; i<strlen(s); i++) {
        LCD_Show(s[i]);
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}
void initClock(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
}

void initLCD(void) {
    LCD_init();
    LCD_Clear();
}

void updateClock(char *timeString) {
    second++;
    if (second == 60) {
        second = 0;
        minute++;
        if (minute == 60) {
            minute = 0;
            hour++;
            if (hour == 24) {
                hour = 0;
            }
        }
    }

    snprintf(timeString, 9, "%02d:%02d:%02d", hour, minute, second);
}
void setClock(char *timeString, uint8_t newHour, uint8_t newMinute, uint8_t newSecond) {
    if (newHour < 24 && newMinute < 60 && newSecond < 60) {
        hour = newHour;
        minute = newMinute;
        second = newSecond;
        snprintf(timeString, 9, "%02d:%02d:%02d", hour, minute, second);
    }
}
