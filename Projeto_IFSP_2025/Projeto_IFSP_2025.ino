int umisolo01;   //declaração de variáveis
int umidade_solo_01;

#define LED 22
#define sensorUmidadeSolo 26   

void setup() {
  Serial.begin(115200);  //velocidade de comunicação serial
  pinMode(LED,OUTPUT);  //define saída LED como saída
  delay(1500); 
}

void loop() {
  Serial.print("umidade do solo: ");
  umisolo01 = analogRead(sensorUmidadeSolo);  //leitura analógica do sensor umidade do solo que irá passar pelo conversor AD
  Serial.println(umisolo01);
  umidade_solo_01 = map(umisolo01,1000,2400,100,0);   ///conversão do valor do conversor AD para uma escala de 0 a 100 
  //https://www.bosontreinamentos.com.br/eletronica/arduino/funcao-map/#google_vignette
  //para quem ficou com dúvida utilize a lógica de Celsius para Fahrenheit em que 0 está para 32 e 100 para 212
  //tempF = map(tempC,0,100,32,212); 
  Serial.print("umidade do solo convertido: ");
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
  delay(1000);
}