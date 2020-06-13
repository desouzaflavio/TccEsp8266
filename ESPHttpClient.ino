#include "TopicConnect.h"
#include "DHT.h"

#define DHT_DATA_PIN 4
#define DHTTYPE DHT22

DHT dht(DHT_DATA_PIN, DHTTYPE);

#define LDR_PIN 0
int ldr_value = 0;

const char* ssid = "ESPWIFI";
const char* password = "esp8266net";

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);

  TopicConnect::setUrl("http://ec2-54-208-57-36.compute-1.amazonaws.com");
  TopicConnect::setUser("teste");
  TopicConnect::setKey("5bfae354aa0aa91e33abfcd0");
  TopicConnect::setChipid("ESP_TESTE_09");
  //TopicConnect::setChipid(ESP.getChipId());
  
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting...");
  }

  TopicConnect::tp_register();
  Serial.println(TopicConnect::getPayload());
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
        
  if( WiFi.status()== WL_CONNECTED ){

    TopicConnect::setSensorType("Temperatura");
    TopicConnect::setSensorValue(dht.readTemperature());
    Serial.println(TopicConnect::getJSonString());
    Serial.println();

    TopicConnect::tp_send();

    TopicConnect::setSensorType("Umidade");
    TopicConnect::setSensorValue(dht.readHumidity());
    Serial.println(TopicConnect::getJSonString());
    Serial.println();
    
    TopicConnect::tp_send();

    float vout = 3.3*((1023 - analogRead(LDR_PIN))/1023);
    
    float duty = 1023 - analogRead(LDR_PIN);
    vout = 3.3*duty/1023;
    float lux = 50*((3.3 - vout)/vout);
    
    TopicConnect::setSensorType("Luminosidade");
    TopicConnect::setSensorValue(lux);
    Serial.println(TopicConnect::getJSonString());
    Serial.println();

    TopicConnect::tp_send();

    //TopicConnect::tp_receive( "chave" );
    //Serial.println( TopicConnect::getReceivedData());
    
    if( TopicConnect::getHttpResponse() > 0 ){
        
        Serial.print("POST HTTP Status code: ");
        Serial.println(TopicConnect::getHttpResponse());
        Serial.println(TopicConnect::getPayload());
    }
  }
  else{
    Serial.println("Failure to connect!!!");
  }
  
  delay(15000);
}
