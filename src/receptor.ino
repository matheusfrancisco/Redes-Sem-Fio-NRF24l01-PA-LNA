
#define tamanhoMSG 100
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

// se for a mesma chave do emissor, ele recebe a mensagem
const char addr = '9';
char textC[tamanhoMSG] = "";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&textC, sizeof(textC));
    if (textC[0] ^ addr) { // Verifica se a mensagem é para mim
      Serial.print(textC);
      Serial.println(" => Mensagem para outro");
    } else {
      char textDC[tamanhoMSG] = "";
      for (int i = 1; i < strlen(textC); i++){
          textDC[i - 1] = textC[i] ^ addr;
      }
      Serial.print(textC);
      Serial.print(" = ");
      Serial.println(textDC);
    }
  }
}