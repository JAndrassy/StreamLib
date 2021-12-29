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

#include "StringReadStream.h"

StringReadStream::StringReadStream(const char *_str, bool _progmem) :
    str(_str), progmem(_progmem) {
  if (progmem) {
    length = strlen_P(str);
  } else {
    length = strlen(str);
  }
}

StringReadStream::StringReadStream(__FlashStringHelper* _str) :
    str((const char*) _str), progmem(true) {
  length = strlen_P(str);
}

StringReadStream::StringReadStream(String& _str) :
    str(_str.c_str()), progmem(false) {
  length = _str.length();
}

int StringReadStream::available() {
  return length - pos;
}

int StringReadStream::read() {
  int c = peek();
  if (c != -1) {
    pos++;
  }
  return c;
}

int StringReadStream::peek() {
  if (pos == length)
    return -1;
  if (progmem)
    return pgm_read_byte(str + pos);
  return str[pos];
}
