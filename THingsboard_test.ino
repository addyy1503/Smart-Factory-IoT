#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Network details
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


const char* token  = "JjvqElNqPGQak4dpcYJq";  /// paste your acess token here
const char* broker = "mqtt.thingsboard.cloud"; // adress of the things board broker
EthernetClient ethClient;
PubSubClient   client(ethClient);// mqtt client


void setup() 
{
  Serial.begin(9600);
  Ethernet.begin(mac);
  client.setServer(broker, 1883); // connecting the arduino to the things board cloud 
}

void reconnect()
{
  while (!client.connected())
  {
    if (client.connect("Node1", token, NULL))
    {
      Serial.println("Connected to ThingsBoard");
    }
    else
    {
      Serial.println("Retrying...");  // retry after every 2 sec
      delay(2000);
    }
  }
}

void loop() 
{
  if (!client.connected()) reconnect();  // check if board is connected to things board , if not reattemt for connnection 
  char payload[50];
int temperature = 28;
// put data into json fomat 
sprintf(payload, "{\"temperature\":%d}", temperature);  // payload = "temperature":28

client.publish("v1/devices/me/telemetry", payload);  // sending data to productionline device telemetry 
  delay(5000);
}