#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/hibernate.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"

int main(void) {
    // Sistem frekansı ayarı
    SysCtlClockSet(SYSCTL_SYSDIV_16 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Hibernation modülünü etkinleştir
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    HibernateEnableExpClk(SysCtlClockGet());

    // RTC başlangıç değerini ayarla ve modülü başlat
    HibernateRTCSet(0);
    HibernateRTCEnable();

    // Uyandırma için süreyi belirle (5 saniye sonra uyanma)
    HibernateRTCMatchSet(0, HibernateRTCGet() + 5);

    // Wake pinini ve RTC'yi etkinleştir
    HibernateWakeSet(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC);

    // LED gösterimi (uyku modundan önce)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); // Mavi LED açık

    // Hibernation moduna geç
    HibernateRequest();

    // Uyandıktan sonra işlem
    while (1) {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); // Mavi LED kapalı
    }
}
