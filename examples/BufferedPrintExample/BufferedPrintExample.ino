#include <StreamLib.h>
#include <IPAddress.h>

const char* s = "Lorem ipsum";
char c = 'X';
int i = 42;
float f = PI;
IPAddress ipAddress(192, 168, 0, 1);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  char buff[150];
  BufferedPrint bp(Serial, buff, sizeof(buff));

  bp.print(F("Some text: "));
  bp.println(s);
  bp.print(F("Some char: "));
  bp.println(c);
  bp.print(F("HEX of char: "));
  bp.println(c, HEX);
  bp.print(F("Some integer: "));
  bp.println(i);
  bp.print(F("Some float: "));
  bp.println(f, 5);
  bp.print(F("IP address: "));
  bp.println(ipAddress);

  bp.printf(F("Formated: %s;%c;%05d\r\n"), s, c, i);

  bp.flush();

}

void loop()
{

}
