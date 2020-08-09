/********************************************************************************
  This file contains various fuctions
********************************************************************************/


/********************************************************************************
  send MQTT Packet periodically every UpdateInterval_MQTT_Publish
********************************************************************************/
void send_MQTTpacket() {

  if (millis() - previousUpdateTime_MQTT_Publish > UpdateInterval_MQTT_Publish)  {
    previousUpdateTime_MQTT_Publish += UpdateInterval_MQTT_Publish;

    if (WiFiMQTTclient.isMqttConnected()) {

      String  buf;              //create a buffer for the MQTT string
      long rssi = WiFi.RSSI();  //get the WiFi received signal level
      buf = String(rssi);       //convert long to String

      Serial.println();
      Serial.print("sent MQTT topic jake/rssi: ");
      Serial.println(buf);

      const char* MQTT_Base_Topic = "jake/rssi";

      WiFiMQTTclient.publish(MQTT_Base_Topic, buf);

    }
  }
}
