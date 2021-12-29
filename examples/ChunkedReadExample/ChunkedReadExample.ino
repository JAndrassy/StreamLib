#include <StreamLib.h>

const char PROGMEM chunkedHTML[] = "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "Transfer-Encoding: chunked\r\n"
    "\r\n"
    "2a\r\n"
    "0abcdefghijklmnopqrstuvwxyz\r\n"
    "1abcdefghijkl\r\n"
    "2a\r\n"
    "mnopqrstuvwxyz\r\n"
    "2abcdefghijklmnopqrstuvwxy\r\n"
    "2a\r\n"
    "z\r\n"
    "3abcdefghijklmnopqrstuvwxyz\r\n"
    "4abcdefghi\r\n"
    "2a\r\n"
    "jklmnopqrstuvwxyz\r\n"
    "5abcdefghijklmnopqrstuv\r\n"
    "2a\r\n"
    "wxyz\r\n"
    "6abcdefghijklmnopqrstuvwxyz\r\n"
    "7abcdef\r\n"
    "16\r\n"
    "ghijklmnopqrstuvwxyz\r\n"
    "\r\n"
    "0\r\n";

StringReadStream client(chunkedHTML, true); // simulates network client

void setup() {

  Serial.begin(115200);
  while (!Serial);

  char line[20];
  int length = client.readBytesUntil('\r', line, sizeof(line) - 1); // read the first line
  line[length] = 0; // terminate the C string

  if (strcmp(line, "HTTP/1.1 200 OK") == 0) { // if equals

    // skipping the rest of the HTTP headers
    client.find("\r\n\r\n"); // find the empty line after the headers

    // read client from this point with the chunked format decoder
    ChunkedStreamReader chunked(client);

    // output to Serial
    while (chunked.chunkAvailable()) { // this returns count of chars remaining in the current chunk
      if (chunked.available()) { // this returns count of chars available to read (already received)
        Serial.write(chunked.read());
      }
    }

    // alternative: read into a C string (comment out the 3 lines above)
//    char buff[500];
//    CStringBuilder sb(buff, sizeof(buff));
//    sb.copyFrom(chunkedReader, sizeof(buff));
//    Serial.print(buff);

  } else {
    Serial.println(line);
  }
}

void loop() {

}

