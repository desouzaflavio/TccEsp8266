#include "TopicConnect.h"

String TopicConnect::key;
String TopicConnect::url;
String TopicConnect::user;
String TopicConnect::header;
String TopicConnect::chipId;
String TopicConnect::sensor;
String TopicConnect::payload;
String TopicConnect::macaddress;
String TopicConnect::jSonString;
String TopicConnect::receiveddata;

int TopicConnect::httpresponse;

float TopicConnect::sensorvalue;

HTTPClient TopicConnect::h;
StaticJsonBuffer<1024> TopicConnect::JSONBuffer;

TopicConnect::TopicConnect()
{
    //construtor
}

TopicConnect::~TopicConnect()
{
    //destrutor
}

String TopicConnect::getUrl(){
    return url;
}

String TopicConnect::getHeader(){
    return header;
}

String TopicConnect::getChipid(){
    return chipId;
}

String TopicConnect::getMacAddress(){
    return macaddress;
}

String TopicConnect::getUser(){
    return user;
}

String TopicConnect::getKey(){
    return key;
}

String TopicConnect::getSensor(){
    return sensor;
}

String TopicConnect::getSensorValue(){
    return String(sensorvalue);
}

String TopicConnect::getJSonString(){
    return jSonString;
}

String TopicConnect::getPayload(){
    return payload;
}

String TopicConnect::getReceivedData(){
  return receiveddata;
}

void TopicConnect::setUrl(String u){
    url = u;
}

void TopicConnect::setHeader(String h){
    header = h;
}

void TopicConnect::setChipid(String i){
    chipId = i;
}

void TopicConnect::setChipid(int i){
    chipId = String(i);
}

void TopicConnect::setMacAddress(String m){
    macaddress = m;
}

void TopicConnect::setUser(String u){
    user = u;
}

void TopicConnect::setKey(String k){
    key = k;
}

void TopicConnect::setSensorType(String t){
    sensor = t;
}

void TopicConnect::setSensorValue(float s){
  sensorvalue = s;
}

void TopicConnect::jSonCreate(){
    jSonString = "{ \"nome\": \"" + chipId + "\", \"tipo\": \"" + sensor + "\", \"valor\": \"" + String(sensorvalue) + "\" }" ;
}

int TopicConnect::getHttpResponse(){
  return httpresponse;
}

int TopicConnect::tp_register(){
    jSonString = "{ \"nome\": \"" + chipId + "\", \"login\": \"" + user + "\", \"chave\": \"" + key + "\" }" ;
    h.begin( getUrl() + "/dispositivo" );
    h.addHeader("Content-Type", "application/json");
    httpresponse = h.POST( getJSonString() );
    payload = h.getString();
    h.end();
    return httpresponse;
}

int TopicConnect::tp_send(){
    jSonCreate();
    h.begin( getUrl() + "/topico" );
    h.addHeader("Content-Type", "application/json");
    httpresponse = h.POST( getJSonString() );
    payload = h.getString();
    h.end();
    return httpresponse;
}

String TopicConnect::tp_receive(String d){
    h.begin( getUrl() );
    httpresponse = h.GET();
    payload = h.getString();
    h.end();

    JsonObject &parsed = JSONBuffer.parseObject( payload );
    
    if(!parsed.success()){
      delay(5000);
      return "Parse Failed!!!";
    }
    
    receiveddata = parsed[d].asString();
    return parsed[d];
}

// json string example: "{ \"nome\": \"ESP8266\", \"login\": \"Flavio\", \"chave\": \"5ac2b122abe9a7001451f228\" }"
