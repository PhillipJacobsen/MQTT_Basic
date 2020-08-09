
#define MQTT_SERVER_IP    "40.85.223.207"
#define MQTT_USERNAME     "ESP_MQTT_Basic"
#define MQTT_PASSWORD     "compost2"
#define MQTT_CLIENT_NAME  "TestClient"    //this should be a "random" value. This value is ignored if you call WiFiMQTTclient.enableMACaddress_for_ClientName();
#define MQTT_SERVER_PORT  1883

#define WIFI_SSID         "TELUS0357"
#define WIFI_PASS         "77kmm7r7hz"

//#define _enableNTP        //undefine this if you don't have internet access 

// Todo: try using this library to handle daylight savings:  https://github.com/JChristensen/Timezone
//int8_t TIME_ZONE = -6;      //set timezone:  MST (works in summer)
int8_t TIME_ZONE = -7;        //set timezone:  MST (works in winter)
int16_t DST = 3600;           //To enable Daylight saving time set it to 3600. Otherwise, set it to 0. I am not sure if this actually works. Need to confirm in the fall.
