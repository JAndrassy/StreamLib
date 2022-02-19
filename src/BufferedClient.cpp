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

#include <BufferedClient.h>

BufferedClient::BufferedClient(Client& _client, uint8_t* readBuffer, size_t readBufferSize, uint8_t* writeBuffer, size_t writeBufferSize) :
    BufferedClientReader(_client, readBuffer, readBufferSize), bp(_client, (char*) writeBuffer, writeBufferSize) {
}

size_t BufferedClient::write(uint8_t b) {
  return bp.write(b);
}

size_t BufferedClient::write(const uint8_t *buf, size_t size) {
  return bp.write(buf, size);
}

void BufferedClient::flush() {
  bp.flush();
}

int BufferedClient::availableForWrite() {
  return bp.availableForWrite();
}

