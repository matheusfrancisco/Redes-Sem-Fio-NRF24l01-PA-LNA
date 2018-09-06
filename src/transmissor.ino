#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define tamanhomsg 9
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
char text[tamanhomsg] = "11100110";

// chave que o receptor deve ter para receber msg
char tC= 230;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}
void loop() {
  char textC[tamanhomsg];
  textC[0]= tC;
  for( int i = 1 ; i < strlen(text)+1  ; i++ )    {
        textC[i]= tC^text[i-1] ;
    }
  Serial.print("MSG C:");
  Serial.println(textC);
  Serial.print("MSG ORIGINAL:");
  Serial.println(text);
  radio.write(&textC, sizeof(text));
  delay(1000);
}
