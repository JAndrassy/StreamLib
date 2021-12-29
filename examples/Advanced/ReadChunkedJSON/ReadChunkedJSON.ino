
#include <ArduinoJson.h>
#include <StreamLib.h>

const char PROGMEM chunkedHTML[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: application/json\r\n"
    "Transfer-Encoding: chunked\r\n"
    "\r\n"
    "8a\r\n"
    "{\"e\":[{\"i\":0,\"t\":1640768411,\"v1\":0,\"v2\":0,\"c\":1},{\"i\":1,\"t\":1640036415,\"v1\":0,\"v2\":0,\"c\":1},{\"i\":2,\"t\":1640036411,\"v1\":0,\"v2\":0,\"c\":1},{\"i\r\n"
    "8a\r\n"
    "\":3,\"t\":1634386598,\"v1\":2,\"v2\":0,\"c\":1},{\"i\":4,\"t\":1618603559,\"v1\":32,\"v2\":40,\"c\":3},{\"i\":5,\"t\":1639256710,\"v1\":-11,\"v2\":0,\"c\":1},{\"i\":6,\"\r\n"
    "8a\r\n"
    "t\":1635766470,\"v1\":176,\"v2\":2050,\"c\":2},{\"i\":7,\"t\":1637662623,\"v1\":3989,\"v2\":-1420,\"c\":1},{\"i\":8,\"t\":1635767658,\"v1\":0,\"v2\":0,\"c\":3},{\"i\":\r\n"
    "8a\r\n"
    "9,\"t\":1640037014,\"v1\":44,\"v2\":0,\"c\":1},{\"i\":10,\"t\":1640768410,\"v1\":200,\"v2\":0,\"c\":1},{\"i\":11,\"t\":1640717652,\"v1\":77,\"v2\":0,\"c\":1},{\"i\":12,\r\n"
    "85\r\n"
    "\"t\":1631261364,\"v1\":2,\"v2\":3,\"c\":2},{\"i\":13,\"t\":1640036425,\"v1\":-1,\"v2\":0,\"c\":1},{\"i\":14,\"t\":1639572053,\"v1\":30,\"v2\":0,\"c\":2}],\"s\":1}";

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

    DynamicJsonDocument doc(800);
    DeserializationError error = deserializeJson(doc, chunked);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    } else {

      // just print the resulting JSON
      serializeJsonPretty(doc, Serial);
    }

  } else {
    Serial.println(line);
  }
}

void loop() {

}

