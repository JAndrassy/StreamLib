#include <CStringBuilder.h>
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
  CStringBuilder sb(buff, sizeof(buff));

  sb.print(F("Some text: "));
  sb.println(s);
  sb.print(F("Some char: "));
  sb.println(c);
  sb.print(F("HEX of char: "));
  sb.println(c, HEX);
  sb.print(F("Some integer: "));
  sb.println(i);
  sb.print(F("Some float: "));
  sb.println(f, 3);
  sb.print(F("IP address: "));
  sb.println(ipAddress);

  int l = sb.length();
  sb.print("this text doesn't fit in the remaining space in the buffer");
  if (sb.getWriteError()) {
    sb.setLength(l);
  }
  sb.println("test test");

  Serial.print("size to print: ");
  Serial.println(sb.length());
  Serial.println();
  Serial.println(buff);

  sb.reset();
  sb.printf(F("Formatted: %s;%c;%05d\r\n"), s, c, i);
  Serial.println(buff);

  sb.reset();
  Serial.println("Enter some short text please");
  sb.print("You entered: ");
  while (!Serial.available());
  sb.copyFromUntil('\n', Serial);
  Serial.println(buff);
}

void loop()
{

}
