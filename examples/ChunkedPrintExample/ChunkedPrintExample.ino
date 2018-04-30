#include <StreamLib.h>
#include <IPAddress.h>

IPAddress ipAddress(192, 168, 0, 1);

const char* uri = "/servicecgi-bin/save";

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  char buff[100];
  ChunkedPrint chunked(Serial, buff, sizeof(buff));

  chunked.printf(F("POST %s HTTP/1.1\r\n"), uri);
  chunked.print(F("Host: "));
  chunked.println(ipAddress);
  chunked.println(F("Transfer-Encoding: chunked"));
  chunked.println(F("Connection: close"));
  chunked.println();
  chunked.begin();
  printSomeData(chunked);
  chunked.end();
}

void loop()
{

}

void printSomeData(Print& out) {
  randomSeed(analogRead(0));
  int l = random(500, 700);
  for (int i = 0; i < l; i++) {
    char c = random(65, 122);
    if (c >= 91 && c < 97) {
      c = ' ';
    }
    out.print(c);
  }
}
