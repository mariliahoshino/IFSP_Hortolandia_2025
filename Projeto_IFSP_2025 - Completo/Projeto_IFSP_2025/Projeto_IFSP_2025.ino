

  float flowRate;
  int led;
  float temperatura;
  float umidade;
  int umisolo01;
  int umidade_solo_01;
  int bombaStatus =0;
  int interruptor;
  int estadoBotao = 0;


#include "DHT.h"

#define LED 22
#define bomba 21
#define interruptor 23
#define sensorUmidadeSolo 26   //como utilizar
#define DHTPIN 27  //nunca utilizar pino 12  https://www.reddit.com/r/esp32/comments/yi5zke/esp32_wont_boot_up_with_dht11_connected/?rdt=45599
#define DHTTYPE DHT22  //DHT11 ou DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(bomba,OUTPUT);

  dht.begin();
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
}

void loop() {
  leituraSensor();
  leituraUmidadeSolo01();
  estadoBotao = digitalRead(interruptor);
  //Serial.println(estadoBotao);
  if(estadoBotao ==1)
  {
    //Serial.println(bombaStatus);
    ldbomba();
  }
  delay(1000);
}

void ldbomba()  {
  if (bombaStatus == 0)
  {   ///colocar outra variável
    digitalWrite(bomba, 1);
    Serial.println("bomba ligada");
    bombaStatus = 1;
    while(estadoBotao)
    {
      estadoBotao = digitalRead(interruptor);
      Serial.println("solte o botão");
      delay(500);
    }
  } else
  {
    digitalWrite(bomba, 0);
    Serial.println("bomba desligada");
    bombaStatus = 0;
    while(estadoBotao)
    {
      estadoBotao = digitalRead(interruptor);
      Serial.println("solte o botão");
      delay(500);
    }
  }
}

void leituraSensor()
{
  umidade = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temperatura = dht.readTemperature(); 
  //temperatura = t;
  //umidade = h;
  Serial.print("temperatura: ");
  Serial.println(temperatura);
  Serial.print("umidade: ");
  Serial.println(umidade);
}

void leituraUmidadeSolo01()
{
  Serial.print("umidade do solo: ");
  Serial.println(analogRead(sensorUmidadeSolo));
  umisolo01 = analogRead(sensorUmidadeSolo) ;
  umidade_solo_01 = map(umisolo01,1000,2400,100,0);   ///https://www.bosontreinamentos.com.br/eletronica/arduino/funcao-map/#google_vignette
  Serial.print("umidade do solo convertido: ");
  Serial.println(umidade_solo_01);

  if (umidade_solo_01 <=40)
  {
    digitalWrite(LED, HIGH);
  } 
  else
  {
    digitalWrite(LED, LOW);
  }
}

void leituraFluxoAgua()
{
}
