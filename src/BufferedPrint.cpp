/*
 Copyright (C) 2018 Juraj Andrássy
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

#include "BufferedPrint.h"

BufferedPrint::BufferedPrint(Print& _target, char* _buffer, size_t _size) : target(_target) {
  buffer = _buffer;
  size = _size;
  pos = 0;
}

size_t BufferedPrint::write(uint8_t b) {
  buffer[pos++] = b;
  if (pos == size) {
    flush();
  }
  return 1;
}

void BufferedPrint::flush() {
  if (!pos)
    return;
  target.write(buffer, pos);
  pos = 0;
}
