/*
Copyright (C) 2022 Juraj Andrássy
repository https://github.com/jandrassy

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "BufferedClientReader.h"

BufferedClientReader::BufferedClientReader(Client& _client, uint8_t* _buffer, size_t _size) : client(_client) {
  buffer = _buffer;
  size = _size;
  length = 0;
  pos = 0;
}

int BufferedClientReader::connect(IPAddress ip, uint16_t port) {
  return client.connect(ip, port);
}

int BufferedClientReader::connect(const char *host, uint16_t port) {
  return client.connect(host, port);
}

void BufferedClientReader::stop() {
  return client.stop();
}

uint8_t BufferedClientReader::connected() {
  return client.connected();
}

BufferedClientReader::operator bool() {
  return client;
}

int BufferedClientReader::available() {
	if (pos == length && client.available()) {
    length = client.read(buffer, size);
    pos = 0;
	}
	return length - pos + client.available();
}

int BufferedClientReader::read() {
  if (!available())
    return -1;
  return buffer[pos++];
}

int BufferedClientReader::peek() {
  if (!available())
    return -1;
  return buffer[pos];
}

int BufferedClientReader::read(uint8_t *buf, size_t _size) {
  if (pos == length && (_size >= size || _size > client.available()))
    return client.read(buf, _size); // skip the internal buffer
  for (int i = 0; i < _size; i++) {
    int b = read();
    if (b == -1)
      return i;
    buf[i] = b;
  }
  return _size;
}

size_t BufferedClientReader::write(uint8_t b) {
  return client.write(b);
}

size_t BufferedClientReader::write(const uint8_t *buf, size_t size) {
  return client.write(buf, size);
}

void BufferedClientReader::flush() {
  client.flush();
}

int BufferedClientReader::availableForWrite() {
  return client.availableForWrite();
}
