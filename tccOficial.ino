//inicializando biblioteca
#include <LiquidCrystal.h>

//identificação de pinos
#define sensorUmidSol A0
#define sensorUmidAr A3
#define sensorTemp A4

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//definindo e inicializando variáveis
float umidSolValue =  0;
int umidArValue =  0;
int tempValue =  0;
int mensagem = 0;
char charBuf [6];

void setup() {
  pinMode(9, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);

  Serial.println("Setup finalizado, aguardando comando.");
}

void loop() {

  //leitura de sensores
  umidSolValue = analogRead(sensorUmidSol);
  umidArValue = analogRead(sensorUmidAr);
  tempValue = analogRead(sensorTemp);

  //mudança de valor analógico para numeração convencional
  float voltUmidAr = umidArValue * (4.95 / 1023.0);
  float umidAr = map(voltUmidAr, 0.52, 3.88, 10, 80);

  float voltTemp = tempValue * (4.95 / 1023.0);
  float temp = map(voltTemp, 1.52, 3.62, 0, 50);

  //converter float para String
  String umid_sol_strg = dtostrf(umidSolValue, 6, 2, charBuf);
  String umid_ar_strg = dtostrf(umidAr, 6, 2, charBuf);
  String temp_strg = dtostrf(temp, 6, 2, charBuf);

  if (Serial.available() > 0) {
    mensagem = Serial.read();

    if ( mensagem == 'l' ) {
      Serial.println(umid_sol_strg + "\t" + umid_ar_strg + "\t" + temp_strg);
    }//if para enviar uma mensagem ao receber 'l'
    
  } //if para verificar se a comunicação serial está disponível

  if (umidSolValue <= 600) {
    lcd.setCursor(0, 0);
    lcd.print("Solo seco :(");
    lcd.setCursor(2, 1);
    lcd.print(" (");
    lcd.print(umidSolValue);
    lcd.print(")");

    lcd.setCursor(15, 0);
    lcd.print("Umidade do ar: ");
    lcd.print(umidAr);
    lcd.print("%");

    lcd.setCursor(15, 1);
    lcd.print("Temperatura: ");
    lcd.print(temp);
    lcd.print("C");

    for (int posicao = 0; posicao < 40; posicao++)
    {
      lcd.scrollDisplayLeft();
      delay(300);
    }//laço que permite que os caracteres "deslizem" pelo display LCD

  } else if (umidSolValue > 600) {
    lcd.setCursor(0, 0);
    lcd.print("Solo úmido :)");
    lcd.setCursor(3, 1);
    lcd.print(" (");
    lcd.print(umidSolValue);
    lcd.print(")");

    lcd.setCursor(18, 0);
    lcd.print("Umidade do ar: ");
    lcd.print(umidAr);
    lcd.print("%");

    lcd.setCursor(18, 1);
    lcd.print("Temperatura: ");
    lcd.print(temp);
    lcd.print("C");

    for (int posicao = 0; posicao < 40; posicao++)
    {
      lcd.scrollDisplayLeft();
      delay(300);
    }//laço que permite que os caracteres "deslizem" pelo display LCD

  }//if para definição de solo seco ou úmido, para ser exibido no display LCD

  if (umidSolValue <= 600) {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }//if para ativar ou não a bomba

  delay(500);

  //"limpa" a tela do display
  lcd.clear();

}
