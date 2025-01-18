#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "driverlib/uart.h"
#include "driverlib/adc.h"


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
void initLCD(void);
void LCD_Clear(void);                               //Clear the screen
void LCD_Print(char *s, char *d);                   //Print 2 lines
void LCD_PrintLn(char i, char *s);                  //Print specific line
void LCD_PrintJustify(char i, char *s, char *d);    //Print specific line floated left and floated right text
void LCD_Cursor(char x, char y);                    //Set cursor
void ilkayarlar();
void initClock(void);
void updateClock();
void adcserigonder(deger);
void LCD_PrintAt(char row, char col, char *s);

int timerkesmesi;
char timeString[8]={'0','0',':','0','0',':','0','0'};  // "00:00:00\0"
//volatile uint8_t hour = 0, minute = 0, second = 0;
int gelenveri;
bool saatmi=false;
bool karaktermi=false;
int gelensaatno=0;
int gelenkarakterno=0;
char geldiVeri[16];


int main(void) {
    initClock();
    initLCD();
    ilkayarlar();
    uint32_t gelendata[4];
    uint32_t ortdata;
    uint32_t temp;
    char tempString[5];

    while (1) {
        timerkesmesi=TimerIntStatus(TIMER0_BASE, true);
        if(UARTCharsAvail(UART0_BASE)) {
                    gelenveri=UARTCharGet(UART0_BASE);
                    if (gelenveri=='%'){
                        saatmi=true;
                        karaktermi=false;
                        gelensaatno=0;
                        TimerDisable(TIMER0_BASE, TIMER_A);
                    }
                    else if (saatmi==true) {
                        timeString[gelensaatno]=gelenveri;
                        gelensaatno++;
                        if (gelensaatno==8) {
                            saatmi=false;
                            gelensaatno=0;
                            TimerEnable(TIMER0_BASE, TIMER_A);
                        }
                    }
                    else if (gelenveri=='/') {
                        karaktermi=true;
                        gelenkarakterno=0;
                        LCD_Clear();
                        TimerDisable(TIMER0_BASE, TIMER_A);
                    }
                    else if (karaktermi==true) {
                        LCD_Clear();
                        geldiVeri[gelenkarakterno] =gelenveri;
                        gelenkarakterno++;
                        gelenveri=0;
                        geldiVeri[gelenkarakterno]=gelenveri;
                        TimerEnable(TIMER0_BASE, TIMER_A);
                        if (gelenkarakterno==16) {
                            karaktermi=false;
                            gelenkarakterno=0;
                            LCD_Clear();
                        }
                    }
                }
        if(timerkesmesi!=0) {
            updateClock();
            LCD_Clear();
            LCD_Print(timeString, "");
            LCD_PrintAt(1, 0, geldiVeri);
            TimerIntClear(TIMER0_BASE, timerkesmesi);

            ADCProcessorTrigger(ADC0_BASE, 1); // yazýlýmsal tetikleme ayarý
        }
        if (ADCIntStatus(ADC0_BASE, 1, false)) {
            ADCIntClear(ADC0_BASE, 1);

            ADCSequenceDataGet(ADC0_BASE, 1, gelendata);
            ortdata = (gelendata[0]+gelendata[1]+gelendata[2]+gelendata[3])/4;
            temp = (1475-((2475*ortdata)/4096))/10;
            sprintf(tempString, "%d", temp);
        }
        adcserigonder(ortdata);

        LCD_PrintAt(0, 10, tempString); // 1. satýr, 11. sütundan itibaren yazdýrýr
   }
}

void adcserigonder(deger){
    char hane3;
    char hane2;
    char hane1;
    char hane0;

    if (deger<10) {
        hane3=0; hane2=0; hane1=0; hane0=deger;
    } else if (deger<100) {
        hane3=0; hane2=0; hane0=(deger % 10); hane1=(deger-hane0)/10;
    } else if (deger<1000) {
        hane3=0; hane0=(deger % 10); hane1=(((deger-hane0)/10) % 10); hane2=(deger-(hane1*10)-(hane0*1));
    } else {
        hane0=(deger % 10);; hane1=(((deger-hane0)/10) % 10); hane2=((deger-(10*hane1)-(1*hane0)) % 100); hane3=((deger-(100*hane2)-(10*hane1)-(1*hane0))/1000);
    }

    UARTCharPut(UART0_BASE, '('); //adc gidiyo
    UARTCharPut(UART0_BASE, hane3+48);
    UARTCharPut(UART0_BASE, hane2+48);
    UARTCharPut(UART0_BASE, hane1+48);
    UARTCharPut(UART0_BASE, hane0+48);
    UARTCharPut(UART0_BASE, '\n');
}
void LCD_init() {

        SysCtlPeripheralEnable(LCDPORTENABLE);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);
        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
        GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);

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
    // Timer0 konfigürasyonu
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() - 1);  // 1 saniye

    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    TimerEnable(TIMER0_BASE, TIMER_A);

}

void initLCD(void) {
    LCD_init();
    LCD_Clear();
}

void updateClock() {
    int second = (timeString[6]-'0')*10+(timeString[7]-'0');
    int minute = (timeString[3]-'0')*10+(timeString[4]-'0');
    int hour = (timeString[0]-'0')*10+(timeString[1]-'0');
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
    timeString[1]= hour %10 + '0';
    timeString[0]= (hour - timeString[1] + '0')/10 + '0';

    timeString[4]= minute %10 + '0';
    timeString[3]= (minute - timeString[4] + '0')/10 + '0';

    timeString[7]= second %10 + '0';
    timeString[6]= (second - timeString[7] + '0')/10 + '0';

    //snprintf(timeString, 9, "%02d:%02d:%02d", hour, minute, second);
}
void LCD_PrintAt(char row, char col, char *s) {
    int j;
    for (j = 0; j < strlen(s); j++) {
        LCD_Cursor(row, col + j);
        LCD_Show(s[j]);
    }
    LCD_Command(0xC0 + 16); // Cursor'u gizle
}
void ilkayarlar(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    // sadece hangi pinleri uart olarak kullanacagýz
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
                        UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    UARTEnable(UART0_BASE);

    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 1); // se:1 yazýlýmsal çevirim

    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);

    ADCSequenceEnable(ADC0_BASE, 1);
    ADCProcessorTrigger(ADC0_BASE, 1); // yazýlýmsal tetikleme ayarý)
}
