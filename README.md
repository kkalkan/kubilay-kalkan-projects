# kubilaykalkan-projects
A repository of ARM Tiva C Series projects demonstrating embedded systems programming, including low-power modes, floating-point calculations, and LCD interfacing.

Bu repo, kişisel ve profesyonel projelerimin bir derlemesidir. Kodlar ve belgeler, her proje için ayrı bir klasörde organize edilmiştir. Bu projeler, yazılım geliştirme becerilerimi ve mühendislik alanındaki deneyimlerimi yansıtmaktadır.

## İçerik
- **Proje 1:** Tiva C Serisi LCD Kontrol Projesi

Proje Tanımı

Bu proje, ARM Tiva C Serisi (TM4C123G) mikrodenetleyici kullanarak bir 16x2 LCD ekranın 4-bit modda kontrolünü sağlamaktadır. LCD'nin başlatılması, komut gönderimi, veri gösterimi ve metin kaydırma gibi temel ve gelişmiş işlemler gerçekleştirilmiştir. 
Teknik Özellikler

Geliştirme Ortamı: Code Composer Studio (CCS)
Kütüphane: TivaWare Peripheral Driver Library
LCD Modülü: 16x2, 4-bit modda kontrol
Pin Bağlantıları:
RS -> GPIOB Pin 0
E -> GPIOB Pin 1
D4 -> GPIOB Pin 4
D5 -> GPIOB Pin 5
D6 -> GPIOB Pin 6
D7 -> GPIOB Pin 7


- **Proje 2:** Tiva C Serisi LCD ve Dijital Saat Projesi
Proje Tanımı

Bu proje, ARM Tiva C Serisi (TM4C123G) mikrodenetleyici ile 16x2 LCD ekranda dijital saat uygulamasını gerçekleştirmektedir. Proje, saat, dakika ve saniye bilgilerinin kesme kullanarak sürekli güncellenmesini ve LCD üzerinde gösterilmesini sağlar.

Teknik Özellikler

Geliştirme Ortamı: Code Composer Studio (CCS)
Mikrodenetleyici: TM4C123G
LCD Kontrol: 16x2, 4-bit modda bağlantı
Donanım Bağlantıları:
RS -> GPIOB Pin 0
E -> GPIOB Pin 1
D4 -> GPIOB Pin 4
D5 -> GPIOB Pin 5
D6 -> GPIOB Pin 6
D7 -> GPIOB Pin 7
Zamanlayıcı: Timer0, 1 saniyelik kesmelerle saat güncellemesi

- **Proje 3:** Tiva C Serisi LCD ve UART ile Dijital Saat Projesi

Proje Tanımı

Bu proje, ARM Tiva C Serisi (TM4C123G) mikrodenetleyici ile 16x2 LCD ekranda dijital saat uygulamasını gerçekleştirmekte ve UART protokolü ile veri iletişimi sağlamaktadır. Saat, UART üzerinden gelen veriyle ayarlanabilir ve LCD üzerinde sürekli güncellenir.

Teknik Özellikler

Geliştirme Ortamı: Code Composer Studio (CCS)
Mikrodenetleyici: TM4C123G
LCD Kontrol: 16x2, 4-bit modda bağlantı
UART Ayarları:
Baud Rate: 9600
Veri: 8 Bit
Durdurma Bit: 1
Parite: Yok
Donanım Bağlantıları:
LCD Port: GPIOB
RS -> GPIOB Pin 0
E -> GPIOB Pin 1
D4 -> GPIOB Pin 4
D5 -> GPIOB Pin 5
D6 -> GPIOB Pin 6
D7 -> GPIOB Pin 7
UART Port: GPIOA
RX -> GPIOA Pin 0
TX -> GPIOA Pin 1
- **Proje 4:** 
- **Proje 5:** Hibernation (uyku modu) uygulamaları ile ilgili kodlar.
- **Proje 6:** Floating-point işlemlerine yönelik kodlar.


Her proje için açıklama ve görseller bulunmaktadır.


