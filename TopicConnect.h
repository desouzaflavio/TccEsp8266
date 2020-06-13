#ifndef TOPICCONNECT_H
#define TOPICCONNECT_H

#include<Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

class TopicConnect
{
    public:
    
        TopicConnect();
        virtual ~TopicConnect();

        static String getUrl();
        static void setUrl( String );

        static String getHeader();
        static void setHeader( String );

        static String getUser();
        static void setUser( String );

        static String getKey();
        static void setKey( String );

        static String getChipid();
        static void setChipid( int );
        static void setChipid( String );

        static String getMacAddress();
        static void setMacAddress( String );

        static String getPayload();
        static String getJSonString();
        static String getReceivedData();

        static String getSensor();
        static String getSensorValue();
        static void setSensorValue(float);
        static void setSensorType( String );

        static int getHttpResponse();

        static int tp_send();
        static String tp_receive( String );
        static int tp_register();

    private:

        static HTTPClient h;
        static StaticJsonBuffer<1024> JSONBuffer;

        static String url;
        static String header;

        static String user;
        static String key;

        static String jSonString;

        static String chipId;
        static String macaddress;

        static String payload;
        static String receiveddata;

        static String sensor;
        static float sensorvalue;

        static int httpresponse;

        static void jSonCreate();

  protected:
  
};

#endif // TOPICCONNECT_H
