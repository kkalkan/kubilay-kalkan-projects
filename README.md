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


- **Proje 4:** Tiva C Serisi LCD  UART ve ADC  ile Dijital Saat Projesi/Sıcaklık okuması 

Proje Tanımı
Bu proje, ARM Tiva C Serisi (TM4C123G) mikrodenetleyici kullanılarak bir dijital saat uygulaması gerçekleştirmekte ve 16x2 LCD ekranda saat bilgisini görüntülemektedir. Saat, UART protokolü üzerinden gelen veri ile ayarlanabilir ve sürekli güncellenir. Ayrıca mikrodenetleyici üzerinde sıcaklık verisi ADC ile ölçülüp LCD'ye ve UART üzerinden gönderilmektedir.

Teknik Özellikler

Geliştirme Ortamı: Code Composer Studio (CCS)
Mikrodenetleyici: TM4C123G
LCD Kontrol: 16x2 LCD, 4-bit mod
UART Ayarları:
Baud Rate: 9600
Veri: 8 Bit
Durdurma Bit: 1
Parite: Yok
ADC Kullanımı: Dahili sıcaklık sensöründen alınan veriler işlenmekte ve hem LCD hem UART üzerinden gösterilmektedir.
Donanım Bağlantıları

LCD Portu: GPIOB
RS: GPIOB Pin 0
E: GPIOB Pin 1
D4: GPIOB Pin 4
D5: GPIOB Pin 5
D6: GPIOB Pin 6
D7: GPIOB Pin 7
UART Portu: GPIOA
RX: GPIOA Pin 0
TX: GPIOA Pin 1
Fonksiyonlar ve Özellikler

Saat Güncelleme: UART üzerinden % ile başlayan 8 karakterlik saat verisi alınarak (hh:mm:ss formatında) LCD'ye yazılır.
Mesaj Gösterimi: / ile başlayan veri, LCD'nin ikinci satırına yazılır ve veri UART üzerinden alınmaya devam eder.
ADC İşlemi: Dahili sıcaklık sensöründen sıcaklık ölçümü yapılır, UART üzerinden gönderilir ve LCD'nin birinci satırında görüntülenir.
Timer İşlemleri: Timer modülü kullanılarak 1 saniyelik zaman aralıklarıyla saat güncellemesi yapılır.
Projede Yapılan İşlemler:

Başlangıç Ayarları: UART, ADC ve Timer modülleri yapılandırılmıştır.
LCD Başlatma ve Kontrol: 16x2 LCD ekrana veri gönderimi 4-bit modda gerçekleştirilmiştir.
UART Veri İşleme: UART üzerinden gelen veriler saat ve mesaj olarak ayrıştırılıp LCD'de görüntülenmiştir.
ADC Ölçümü: Mikrodenetleyicinin dahili ADC modülü kullanılarak sıcaklık ölçümü yapılmış ve UART ile gönderilmiştir.
Saat Uygulaması: Timer kullanılarak saniye bazlı zaman güncellemesi yapılmış, saat LCD'de dinamik olarak gösterilmiştir. 

- **Proje 5:**
- Proje Tanımı
Bu proje, ARM Tiva C Serisi (TM4C123G) mikrodenetleyicisinin düşük güç modlarından biri olan "Hibernation" (uyku modu) özelliğini kullanarak enerji tasarrufu sağlamayı amaçlar. Uyku moduna geçiş ve uyanma işlemleri, belirli bir zamanlayıcı veya dış bir tetikleme ile gerçekleştirilir.

Teknik Özellikler

Mikrodenetleyici: TM4C123G
Geliştirme Ortamı: Code Composer Studio (CCS)
Hibernation Özellikleri:
RTC kullanılarak belirli bir süre sonra mikrodenetleyicinin uyanması.
Uyku moduna geçiş sırasında sistemin enerji tüketimini minimuma indirme.
Uyandıktan sonra işlem durumunu geri yükleme.

- **Proje 6:**
- Proje tanımı Floating-Point İşlemlerine Yönelik Kodlar
Proje Tanımı
Bu proje, ARM Tiva C Serisi (TM4C123G) mikrodenetleyicisinin donanım destekli floating-point (kayan noktalı) birimini kullanarak matematiksel işlemlerin yüksek doğruluk ve hızla gerçekleştirilmesini sağlar. Kayan noktalı işlemler, trigonometrik, logaritmik veya üstel fonksiyonlar gibi karmaşık matematiksel hesaplamalarda kullanılır.

Teknik Özellikler

Mikrodenetleyici: TM4C123G
Geliştirme Ortamı: Code Composer Studio (CCS)
Floating-Point Özellikleri:
Donanım destekli single-precision (32-bit) floating-point işlemler.
Karmaşık matematiksel fonksiyonların hesaplanması.
Kütüphaneler: <math.h>
Örnek Uygulama: Temel trigonometrik ve üstel işlemler.





