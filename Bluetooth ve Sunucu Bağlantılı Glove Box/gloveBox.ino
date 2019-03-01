#include <SPI.h>
#include <Ethernet.h>//Ethernet bağlantisi icin gerekli kütüphane
#include <HttpClient.h> //Tarayıcıya ulaşmak için gerekli kütühane
#include <Xively.h> // Xively.com 'a veri göndermek için gerekli kütühane
#include <LiquidCrystal.h> //LCD ekranı kullanabilmek için gerekli kütühane
#include <dht.h> //Nem ve sicaklik sensörünü kullanabilmek için gerkeli kütüphane
dht DHT; // DHT 11 kütüphanesi için gerekli bir işlem
LiquidCrystal lcd(4, 5, 6, 7, 8, 9); //LCD için arduino'nun Digital 4,5,6,7,8 ve 9 pinlerini kullanacağımız belirtiyoruz.

#define DHT11_PIN 2 // DHT11 sensörünün verilerini arduino'nun digital 2. pininden okuyacağımızi belirtiyoruz.
char xivelyKey[] = "pbcb1r7qimLoKJUouDULUUKAiKBC3gZ6aRqv8tVl6tc6Ssop"; //Xively.com ' daki üyeliğimiz  de oluşturduğumuz kanala ulaşmak için bize verilen API keyi bir karekter dizisi 
                                                                       // yardımıyla arduinoya öğretiyoruz.
#define FEED_ID 1159114779 // xively.com ' a aldığımız verileri göndereceğimiz haberleşme ID 'sini define komutu ile sabit olarak belirtiyoruz.

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // İnternete bağlanmak için gerekli olan mac adresinin  beliritiyoruz.

byte ip[] = {192,168,1,177}; // Bağlanacağımız İp adresini belirtiyoruz.
byte gateway[] = {192,168,1,1}; //Bağlanacağımız modemin İp adresini belirtiyoruz.
byte subnet[] = {255,255,255,0}; //

char sensorId1[] = "Sicaklik"; // Xively.com ' da oluşturduğumuz kanal içine kanal isimlerini gönderiyoruz.
char sensorId2[] = "Nem";
char sensorId3[] = "Degerlendirme" ;


XivelyDatastream xivelyVeriler[] = {                                                       // Göndereceğimiz veri gruplarının tiplerini ve sayısını matris olarak kayıt ediypruz.
  XivelyDatastream(sensorId1, strlen(sensorId1), DATASTREAM_FLOAT),
  XivelyDatastream(sensorId2,strlen(sensorId2),DATASTREAM_FLOAT),XivelyDatastream(sensorId3,strlen(sensorId3),DATASTREAM_STRING)
};

XivelyFeed feed(1159114779, xivelyVeriler, 3 ); // (Göndereciğimiz xively.com haberleşme ID 'si , Oluşturdupumuz veri matrisi , Göndereceğimiz veri sayısı ) gönderime hazırlanır.;

EthernetClient client; // Ethernet bağlantısına başalanıyor.
XivelyClient xivelyclient(client); // xively.com bağlantısı başlatılıyor.
void setup() { // Gerekli ayarlamaların bir sefer yapıldığı yer.
  Ethernet.begin(mac,ip,gateway,subnet); // İnternete bağlantısı sağlanıyor
  
 Serial.begin(9600); //  Seri haberleşme portunun hızı belirleniyor.
  lcd.begin(16,2); // LCD nin 16 sütünlü 2 satırlı olduğu ve haberleşmenin başlyacağı berlitiyliyor.
   lcd.setCursor(0,0); // LCD ye yazma işleminin 0. sütün ve 0. satrıdan başlayacağını gösteriyor.
lcd.print("Sistem"); // Lcd ye 'Sistem' yazılıyor.
  lcd.setCursor(0,2); // LCD ye yeni yazılacak metnin 0. sütün 2 .satırdan dan başlayacağını söylüyor.
  lcd.print("Aciliyor..."); // LCD nin 0.sütün ,2. satırına 'Açiliyor' yazılacağını söylüyor.
  delay(3000); // 3 sn 'lik bir bekleme süresi veriliyor.
  lcd.clear(); // LCD ekranındaki yazılan metinler siliniyor.
  lcd.setCursor(0,0); // Metnin konumu tekrar berlitiliyor.
lcd.print("Internet istemi"); // 'internet istemi' yaziliyor.
  lcd.setCursor(0,2); // Tekrar metin konumu ayarlanıyor.
  lcd.print("Baslatiliyor.."); // 'Başlatılıyor' metini lcd ye yazlıyor.
  delay(4000); // 4 ^sn lik bekleme yapılıyor.
  
   if (Ethernet.begin(mac) != 1) {                              // İnternet bağlantisinin olup olmadığı kontrol ediliyor.
 
  } //

    lcd.clear(); //LCD ekran yazıları siliniyor.
  lcd.setCursor(0,0); // Metin konumu ayarlanıyor.
lcd.print("Veriler"); // 'Veriler' metni LCD ye yaziliryor.
  lcd.setCursor(0,2); // Metin konumu ayarlanıyor.  
  lcd.print("Yukleniyor.."); //'Yükleniyo' metni lcd ye yaziliyor.
  delay(4000); // 4 san'lik bekleme süresi veriliyor.
  pinMode(3, OUTPUT);} // Arduino digital 3 pininin OUTPUT 5V çıkış vermesi gerektiğiğ belirtiliyor.


void loop() { // İşlemlerin sürekli yapılacapı fonksiyon
 
 String a={" Sicalik Degeri Kritik Seviyede!!"} ;
 String b={"SICAKLIK ve NEM NORMAL SEVIYEDE"};
 String c={"Nem Degeri Kritik Seviyede !"} ;
 String d={"Sistem Tehlikede !!"} ;
     xivelyVeriler[0].setFloat(DHT.temperature);
  xivelyVeriler[1].setFloat(DHT.humidity);
 
 
  Serial.print("Nem Degeri = ");
   Serial.print(DHT.humidity, 1) ;
   Serial.print("  %" ) ;
   Serial.println("");
   Serial.print("Sicaklik Degeri= ") ;
  Serial.print(DHT.temperature, 1);
  Serial.println(" C") ;
  lcd.clear();
  lcd.setCursor(0,0);      
  lcd.print("Sicaklik="); 
  lcd.print(DHT.temperature,0);
  lcd.print("C"); 
  lcd.setCursor(0,2);        
 lcd.print("Nem ="); 
  lcd.print(DHT.humidity,0);
  lcd.print("%  "); 
  if(DHT.temperature<=15 &&DHT.humidity<=100 ){
      digitalWrite(3,HIGH);
  Serial.println("ALARM DURUMU , SICAKLIK KRITIK SEVİYEDE");
  lcd.clear();
  lcd.setCursor(0,0);        
  lcd.print("Sicaklik =");
  lcd.print(DHT.temperature,0);
   lcd.print("C");
  lcd.setCursor(2,2);        
  lcd.print("Kritik!!");
      xivelyVeriler[2].setString(a);
  }
  else if(DHT.humidity>50 &&DHT.temperature<=60){
      digitalWrite(3,HIGH);
  Serial.println("ALARM DURUMU , NEM KRITIK SEVİYEDE");
   lcd.clear();
  lcd.setCursor(0,0);         
  lcd.print("Nem =");
  lcd.print(DHT.humidity,0);
   lcd.print("%");
  lcd.setCursor(2,2);        
  lcd.print("Kritik!!");
      xivelyVeriler[2].setString(c);
  }
  else if(DHT.humidity>38&&DHT.temperature<=15){
  lcd.clear();
  lcd.setCursor(0,0);         
  lcd.print("Sistem ");
  lcd.print(DHT.humidity,0);
  lcd.print(DHT.temperature,0);
   lcd.print("%");
  lcd.setCursor(2,2);        
  lcd.print("Tehlikede!!");
    xivelyVeriler[2].setString(d);}
  else{
  digitalWrite(3,LOW);
  xivelyVeriler[2].setString(b);}
  int donusDegeri = xivelyclient.put(feed, xivelyKey);
  // Xivly'e giden HTML isteğinin sonuç değeri (200 - OK)
  delay(2000);
}
