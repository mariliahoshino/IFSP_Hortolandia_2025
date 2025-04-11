


  float flowRate;
  int led;
  float temperatura;
  float umidade;
  int umisolo01;
  int umidade_solo_01;
  int bombaStatus =0;
  //int interruptor;
  int estadoBotao = 0;
  int estadoIrrigacaoAutomatica = 0;


#include "DHT.h"

#define pinochaveIrrigacaoAutomatica 32
#define LED 19  //era 22
#define bomba 18  //era 21
#define interruptor 23
#define sensorUmidadeSolo 26   //como utilizar
#define DHTPIN 27  //nunca utilizar pino 12  https://www.reddit.com/r/esp32/comments/yi5zke/esp32_wont_boot_up_with_dht11_connected/?rdt=45599
#define DHTTYPE DHT22  //DHT11 ou DHT22 depende qual vai utilizar
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(bomba,OUTPUT);
  pinMode(interruptor, INPUT);
  pinMode(pinochaveIrrigacaoAutomatica, INPUT);

  dht.begin();
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
}

void loop() {
  leituraSensor();  // chama a subrotina
  leituraUmidadeSolo01(); // chama a subrotina

  estadoBotao = digitalRead(interruptor); //leitura do sinal de entrada
  if(estadoBotao ==1)
  {
    ldbomba();  // chama a subrotina Liga/Desliga bomba se estiver pressionado o botão
  }

  estadoIrrigacaoAutomatica = digitalRead(pinochaveIrrigacaoAutomatica);  //leitura do sinal de entrada
  if(estadoIrrigacaoAutomatica == 1){
    irrigauto();     // chama a subrotina de irrigação automática se estiver ligada a chave
  }
  //escritadisplay();
  delay(1000);
}

void irrigauto(){
  if(umidade_solo_01 <=40)  //aqui o usuário define o valor para ligar automático
  {
    digitalWrite(bomba, 1);  //liga a bomba
    Serial.println("bomba ligada");
    bombaStatus = 1;
  }
  if(umidade_solo_01 >=70)  //aqui o usuário define o valor para desligar automático
  {
    digitalWrite(bomba, 0);  //desliga a bomba
    Serial.println("bomba desligada");
    bombaStatus = 0;
  }
}

void ldbomba()  {
  if (bombaStatus == 0)
  {   ///colocar outra variável
    digitalWrite(bomba, 1);  //liga a bomba
    Serial.println("bomba ligada");
    bombaStatus = 1;
    while(estadoBotao)  // essa condição evita do sistema passar várias vez pelo mesmo lugar enquanto o usuário ficar segurando o botão
    {                // e também evita o problema do sinal de entrada na botoeira  ao dar uma tremida com o dedo e acionar várias vezes
      estadoBotao = digitalRead(interruptor);
      Serial.println("solte o botão");
      delay(500);
    }
  } else
  {
    digitalWrite(bomba, 0);  //desliga a bomba
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
  umidade = dht.readHumidity(); //Lê a umidade
  temperatura = dht.readTemperature();   //Lê a temperatura padrão é em Celsius
  Serial.print("temperatura: ");
  Serial.println(temperatura);
  Serial.print("umidade: ");
  Serial.println(umidade);
}

void leituraUmidadeSolo01()
{
  Serial.print("umidade do solo: ");
  umisolo01 = analogRead(sensorUmidadeSolo) ;
  Serial.println(umisolo01);  
  umidade_solo_01 = map(umisolo01,1000,2400,100,0);   ///https://www.bosontreinamentos.com.br/eletronica/arduino/funcao-map/#google_vignette
  Serial.print("umidade do solo convertido: ");  //o sensor na prática vai de 1000 até +-2500, mas no emulador não tem o sensor umidade do solo então foi utilizado um potenciômetro
  Serial.println(umidade_solo_01);

  if (umidade_solo_01 <=40)
  {
    digitalWrite(LED, HIGH);
    Serial.println("Planta diz: estou com sede");
  } 
  else
  {
    digitalWrite(LED, LOW);
    Serial.println("Planta diz: estou satisfeita");
  }
  //delay(100);
}

void leituraFluxoAgua()
{
}
