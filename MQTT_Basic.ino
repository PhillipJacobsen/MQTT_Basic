/********************************************************************************
    Basic MQTT project

    MQTT_Basic.ino
    2020 @phillipjacobsen

    Program Features: basic ESP32 template with Wifi and MQTT connection handling

    Instructions for use
  
    1. Install latest version of ArduinoJson by Benoit Blanchon from Library Manager (not needed if MQTT data is not JSON encoded)
    2. Install PubSubClient by Nick O'Leary version 2.7.0.  NOT the newest 2.8.0!!!!!
    3. Install Forked EspMQTTClient library from https://github.com/PhillipJacobsen/EspMQTTClient
       Install dev_pj fork (NOT the main branch)

********************************************************************************/

/********************************************************************************
                              Conditional Assembly
********************************************************************************/


/********************************************************************************
                              Private Data
  IMPORTANT - Modify the secrets.h file with your secure network connection details
********************************************************************************/
#include "secrets.h"

/********************************************************************************
                            Misc I/O Definitions
********************************************************************************/
const int LED_PIN = 13;     //LED integrated on Adafruit HUZZAH32 module
const int BAT_PIN = 35;     //ADC connected to Battery input pin (A13 = 35;)

/********************************************************************************
                              Various Global Variables
********************************************************************************/
bool initialConnectionEstablished_Flag = false;   //used to detect first run after power up


/********************************************************************************
   Arduino Json Libary - This is not needed if your MQTT packets are not JSON encoded

********************************************************************************/
#include <ArduinoJson.h>


/********************************************************************************
    WiFi and MQTT connection handler for ESP32
    This library does a nice job of encapsulating the handling of WiFi and MQTT connections.
    EspMQTTClient is a wrapper around the MQTT PubSubClient Library Version 2.7 by @knolleary
********************************************************************************/
// You need to update this line in PubSubClient.h. Setting it here does nothing.
// the maximum MQTT message size, including header, is 128 bytes by default. 
// Configurable in \Arduino\libraries\PubSubClient\src\PubSubClient.h.  Example change to 512 bytes: #define MQTT_MAX_PACKET_SIZE 512

#include "EspMQTTClient.h"


EspMQTTClient WiFiMQTTclient(
  WIFI_SSID,
  WIFI_PASS,
  MQTT_SERVER_IP,   // MQTT Broker server ip
  MQTT_USERNAME,    // Can be omitted if not needed
  MQTT_PASSWORD,    // Can be omitted if not needed
  MQTT_CLIENT_NAME, // Client name that uniquely identify your device
  MQTT_SERVER_PORT  // The MQTT port, default to 1883. this line can be omitted
);



#ifdef _enableNTP
/********************************************************************************
  Time Library
  required for internal clock to syncronize with NTP server.
********************************************************************************/
#include "time.h"

#endif

/********************************************************************************
  Update Intervals for various algorithms
********************************************************************************/
//Frequency at which the MQTT packets are published
uint32_t UpdateInterval_MQTT_Publish = 10000;           // 10 seconds
uint32_t previousUpdateTime_MQTT_Publish = millis();

/********************************************************************************
  State Machine
********************************************************************************/
enum State_enum {STATE_0, STATE_1, STATE_2, STATE_3, STATE_4, STATE_5, STATE_6};    //The possible states of the state machine
State_enum state = STATE_0;     //initialize the starting state.


/********************************************************************************
  Function prototypes
  Arduino IDE normally does its automagic here and creates all the function prototypes for you.
  We have put functions in other files so we need to manually add some prototypes as the automagic doesn't work correctly
********************************************************************************/
void StateMachine();
void send_MQTTpacket();

/********************************************************************************
  MAIN LOOP
********************************************************************************/
void loop() {

  //--------------------------------------------
  // Process state machine
  StateMachine();

  //--------------------------------------------
  // Handle the WiFi and MQTT connections
  WiFiMQTTclient.loop();

  //--------------------------------------------
  // Publish MQTT data every UpdateInterval_MQTT_Publish (10 seconds)
  send_MQTTpacket();

}
