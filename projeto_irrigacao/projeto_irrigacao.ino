#include <LiquidCrystal.h>
#include <dht11.h>

#define DHT11PIN 13
dht11 DHT11;
#define umidadeSolo A0
#define luminosidade A1
#define solPin  9
int moisture = 0;
float temp = 0;
int luz = 0;



LiquidCrystal lcd(2,3,4,5,6,7,8);
void setup()
{	
  Serial.begin(9600);
  lcd.begin(16,2);
 
  //pinMode(botaoPin, INPUT);  // Configura o pino do botão como entrada
   pinMode(umidadeSolo, INPUT);
   pinMode(solPin, OUTPUT); //valvula solenoide
  lcd.clear();

  pinMode(luminosidade, INPUT);//
  
}



void loop()
{ 
 

  //limpa a tela
  Serial.println();
  lcd.clear();

  
  int chk = DHT11.read(DHT11PIN);
  int umd_solo = analogRead(umidadeSolo);
  

 byte umidade_angulo = map(umd_solo,600,1023,100,0);
  luz = analogRead(luminosidade);
  byte Luz_angulo = map(luz,1017,344,0,100);

  lcd.setCursor(0,0);
  lcd.print("Umidade do ar: ");
  Serial.print("Humidity (%): ");

  lcd.setCursor(0,1);
  lcd.print((float)DHT11.humidity, 2);
  lcd.write("%");
  Serial.println((float)DHT11.humidity, 2);
  

  delay(1000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Umidade do solo: ");
  Serial.print("Umidade do solo (%): ");
  Serial.println(umidade_angulo);
  lcd.setCursor(0,1);
  lcd.print(umidade_angulo);
  lcd.write("%");
  delay(1000);
  lcd.clear();

  lcd.print("Luminosidade:"); 
  Serial.print("Luminosidade: ");
  Serial.println(Luz_angulo);
  lcd.setCursor(0,1); 
  lcd.print(Luz_angulo); 
  lcd.print("%");
  delay(750);

  lcd.setCursor(0,0);
  lcd.print("Temperatura: ");
  Serial.print("Temperatura (%): ");

  lcd.setCursor(0,1);
  lcd.print((float)DHT11.temperature, 2);
  lcd.write(byte(223));
  lcd.print("C");
  Serial.println((float)DHT11.temperature, 2);

  
temp = (float)DHT11.temperature,2;

    
     if ( umidade_angulo >= 30 ||(temp <= 20 && Luz_angulo <= 90 )) {
    digitalWrite(solPin, LOW);  // Desliga a valvula
    
  } else {
    digitalWrite(solPin, HIGH);   // Liga o motor
    delay(100);
    digitalWrite(solPin, LOW);   // Liga o motor
    delay(100);
    digitalWrite(solPin, HIGH);   // Liga o motor
    delay(100);
    digitalWrite(solPin, LOW);   // Liga o motor
    delay(100);
    
  }
  
}




