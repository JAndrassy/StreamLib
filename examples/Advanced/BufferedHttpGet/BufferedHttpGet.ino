/*
  Buffered HTTP GET example
  with ArduinoHttpClient library
  and BufferedClientReader

  created in Jan 2021
  by Juraj Andrassy https://github.com/jandrassy

*/

#include <Ethernet.h>
#include <ArduinoHttpClient.h>
#include <StreamLib.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

char server[] = "arduino.tips";    // name address  (using DNS)

EthernetClient ethClient;
uint8_t readBuffer[32];
BufferedClientReader bc(ethClient, readBuffer, sizeof(readBuffer));
HttpClient client(bc, server, 80);

void setup() {

  Serial.begin(115200);
  while (!Serial);

  Ethernet.init(10);

  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    }
    while (true) {
      delay(1);
    }
  }

  Serial.println("making GET request");
  client.get("/asciilogo.txt");

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

}

void loop() {
}
