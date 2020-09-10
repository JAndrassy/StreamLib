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

#include "CStringBuilder.h"

CStringBuilder::CStringBuilder(char* _buffer, size_t _size) {
  buffer = _buffer;
  size = _size - 1;
  buffer[size] = 0;
  setLength(0);
}

void CStringBuilder::reset() {
  setLength(0);
  setWriteError(0);
}

size_t CStringBuilder::length() {
  return pos;
}

void CStringBuilder::setLength(size_t l) {
  if (l < size) {
    pos = l;
    buffer[l] = 0;
    setWriteError(0);
  }
}

size_t CStringBuilder::write(uint8_t b) {
  if (pos == size) {
    setWriteError(1);
    return 0;
  }
  buffer[pos++] = b;
  buffer[pos] = 0;
  return 1;
}

int CStringBuilder::availableForWrite() {
  return size - pos;
}