/*
  SD Web Server example sketch for StreamLib library

  the example demonstrates real use of BufferedStream and ChunkedStream

  This example doesn't fit into 2 kB SRAM of ATmega328p,
  so it can't be run on Uno, classic Nano or Mini
  It works perfect on Mega, Nano Every, Nano 33 BLE, MKR, Zero, M0, ...

  created in December 2019
  by Juraj Andrassy https://github.com/jandrassy

*/
#include <Ethernet.h>
#include <SD.h>
#include <StreamLib.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

const int SDCARD_CS = 4;
const int ETHERNET_CS = 10;
const int RESPONSE_BUFFER_SIZE = 64;

EthernetServer server(80);

void setup() {

  Serial.begin(115200);
  while (!Serial);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH);

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  Ethernet.init(ETHERNET_CS);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    while (true) {
       delay(1); // do nothing, no point running without Ethernet hardware
    }
  }

  if (!SD.begin(SDCARD_CS)) {
    Serial.println(F("SD card initialization failed!"));
    // don't continue
    while (true);
  }

  server.begin();

  IPAddress ip = Ethernet.localIP();
  Serial.println();
  Serial.println(F("Connected to network."));
  Serial.print(F("To access the server, enter \"http://"));
  Serial.print(ip);
  Serial.println(F("/\" in web browser."));

}

void loop() {

  EthernetClient client = server.available();

  if (client && client.connected()) {
    if (client.find(' ')) { // GET /fn HTTP/1.1
      char fn[32];
      int l = client.readBytesUntil(' ', fn, sizeof(fn) - 1); // read the filename from URL
      fn[l] = 0;
      client.find((char*) "\r\n\r\n");
      File file = SD.open(fn);
      if (!file) { // file was not found
        char buff[RESPONSE_BUFFER_SIZE];
        BufferedPrint response(client, buff, sizeof(buff));
        response.println(F("HTTP/1.1 404 Not Found"));
        response.println(F("Connection: close"));
        response.print(F("Content-Length: "));
        response.println(strlen(" not found") + strlen(fn));
        response.println();
        response.print(fn);
        response.print(F(" not found"));
        response.flush();
      } else if (file.isDirectory()) {
        char buff[RESPONSE_BUFFER_SIZE]; // buffer for chunks
        ChunkedPrint chunkedResp(client, buff, sizeof(buff));
        chunkedResp.println(F("HTTP/1.1 200 OK"));
        chunkedResp.println(F("Connection: close"));
        chunkedResp.println(F("Content-Type: text/html"));
        chunkedResp.println(F("Transfer-Encoding: chunked"));
        chunkedResp.println();
        chunkedResp.begin();
        chunkedResp.printf(F("<!DOCTYPE html>\r\n<html>\r\n<body>\r\n<h3>Folder '%s'</h3>\r\n"), fn);
        while (true) {
          File entry = file.openNextFile();
          if (!entry)
            break;
          if (strcmp(fn, "/") == 0) {
            chunkedResp.printf(F("<a href='%s'>"), entry.name());
          } else {
            chunkedResp.printf(F("<a href='%s/%s'>"), fn, entry.name());
          }
          chunkedResp.print(entry.name());
          if (entry.isDirectory()) {
            chunkedResp.println(F("/</a><br>"));
          } else {
            chunkedResp.printf(F("</a> (%ld b)<br>\r\n"), entry.size());
          }
          entry.close();
        }
        chunkedResp.println(F("</body>\r\n</html>"));
        chunkedResp.end();
      } else {
        char buff[RESPONSE_BUFFER_SIZE];
        BufferedPrint response(client, buff, sizeof(buff));
        response.println(F("HTTP/1.1 200 OK"));
        response.println(F("Connection: close"));
        response.print(F("Content-Length: "));
        response.println(file.size());
        response.print(F("Content-Type: "));
        const char *ext = strchr(file.name(), '.');
        response.println(getContentType(ext));
        response.println();
        response.copyAvailableFrom(file);
        response.flush();
        file.close();
        if (response.getWriteError()) {
          Serial.println(F("Warning: write error."));
        }
      }
    }
    client.stop();
  }
}

const char* getContentType(const char* ext){
  if (!strcmp(ext, ".HTM"))
    return "text/html";
  if (!strcmp(ext, ".CSS"))
    return "text/css";
  if (!strcmp(ext, ".JS"))
    return "application/javascript";
  if (!strcmp(ext, ".PNG"))
    return "image/png";
  if (!strcmp(ext, ".GIF"))
    return "image/gif";
  if (!strcmp(ext, ".JPG"))
    return "image/jpeg";
  if (!strcmp(ext, ".XML"))
    return "text/xml";
  return "text/plain";
}
