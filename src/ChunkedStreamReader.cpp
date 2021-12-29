/*
Copyright (C) 2021 Juraj Andrássy
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

#include "ChunkedStreamReader.h"

ChunkedStreamReader::ChunkedStreamReader(Stream& _input) : input(_input) {

}

void ChunkedStreamReader::readChunkSize() {

  // [\r\n]<size in hex>[;<any chars>]\r\n
  char buff[10];
  int l = 0;
  for (byte i = 0; !l && i < 2; i++) {
    l = input.readBytesUntil('\r', buff, sizeof(buff) - 1);
    input.find('\n');
  }
  if (!l)
    return;
  buff[l] = 0;
  char* ptr;
  counter = strtoul(buff, &ptr, 16);
}

int ChunkedStreamReader::available() {
  if (counter == 0) {
    readChunkSize();
  }
  return min(counter, (unsigned long) input.available());
}

int ChunkedStreamReader::read() {
  if (!available())
    return -1;
  counter--;
  return input.read();
}

int ChunkedStreamReader::peek() {
  if (!available())
    return -1;
  return input.peek();
}

unsigned long ChunkedStreamReader::chunkAvailable() {
  available();
  return counter;
}
