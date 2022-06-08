#include <HTTPClient.h>
#include <WiFi.h>
const char* ssid = "*******";
const char* pass = "*********";

const int gaspin = 0;
const int buzzer = 14;
int valorGas = 0;
void msj(){
  if (valorGas < 1000){
    if(WiFi.status() == WL_CONNECTED){
   HTTPClient http;
   http.begin("https://api.callmebot.com/whatsapp.php?phone=*******&text=Peligro%gas&apikey=*********");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
    int codigo_respuesta = http.GET();
    
    if(codigo_respuesta>0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));
      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);
    }
  }else{
    
     Serial.print("Error enviando GET, código: ");
     Serial.println(codigo_respuesta);
  }
     http.end(); 
    }else{

     Serial.println("Error en la conexión WIFI");

  }
}
}
void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  delay(1000);
   WiFi.begin(ssid, pass);
  
  Serial.print("Conectando!!!");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
Serial.print("conectado con exito");

Serial.print("la IP es:");
Serial.println(WiFi.localIP());
  }
void loop() {
  valorGas = analogRead(gaspin);
  Serial.print("el Valor del gas es: ");
  Serial.print(valorGas);
 
  if (valorGas < 1000){
    for(int a=0; a<=20; a++){
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(75);
    } 
  }
    
  delay(1000);

}
