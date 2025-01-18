#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/fpu.h"

int main(void) {
    // FPU'yu etkinleştir (Floating-Point Unit)
    FPUEnable();
    FPULazyStackingEnable();

    // Matematiksel işlem değişkenleri
    float angle = 45.0;         // Derece cinsinden açı
    float angle_rad;            // Radyan cinsinden açı
    float sine_result;          // Sinüs sonucu
    float exponential_result;   // Üstel fonksiyon sonucu

    // Dereceyi radyana çevir
    angle_rad = angle * (M_PI / 180.0);

    // Trigonometrik işlem (sinüs)
    sine_result = sinf(angle_rad);

    // Üstel işlem (e^x)
    exponential_result = expf(1.0); // e^1 = e

    // İşlem sonuçlarını kontrol için sonsuz döngü
    while (1) {
        // Sonsuz döngüye girerek işlemleri burada kullanabilirsiniz.
    }

    return 0;
}

