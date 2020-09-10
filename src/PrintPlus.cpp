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

#include "PrintPlus.h"
#include <stdio.h>
#include <stdarg.h>

#ifdef __AVR__
int adapterPut(char c, FILE* _adapter) {
  return ((Print*) _adapter->udata) -> write(c);
}

size_t PrintPlus::printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  FILE adapter;
  fdev_setup_stream(&adapter, adapterPut, NULL, _FDEV_SETUP_WRITE);
  fdev_set_udata(&adapter, this);
  size_t len = vfprintf(&adapter, fmt, args);
  va_end(args);
  return len;
}

size_t PrintPlus::printf(const __FlashStringHelper *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  FILE adapter;
  fdev_setup_stream(&adapter, adapterPut, NULL, _FDEV_SETUP_WRITE);
  fdev_set_udata(&adapter, this);
  size_t len = vfprintf_P(&adapter, (const char*) fmt, args);
  va_end(args);
  return len;
}
#else

int adapterWrite(void* p, const char *buf, int n) {
  return ((Print*) p) -> write(buf, n);
}

size_t PrintPlus::printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  FILE* adapter = funopen(this, nullptr, adapterWrite, nullptr, nullptr);
  size_t len = vfprintf(adapter, fmt, args);
  fclose(adapter);
  va_end(args);
  return len;
}

#ifdef ESP8266
size_t PrintPlus::printf(const __FlashStringHelper *fmt, ...) {
  size_t fmtLen = strlen_P((PGM_P) fmt);
  char format[fmtLen + 1];
  strcpy_P(format, (PGM_P) fmt);
  va_list args;
  va_start(args, fmt);
  FILE* adapter = funopen(this, nullptr, adapterWrite, nullptr, nullptr);
  size_t len = vfprintf(adapter, format, args);
  fclose(adapter);
  va_end(args);
  return len;
}
#else
size_t PrintPlus::printf(const __FlashStringHelper *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  FILE* adapter = funopen(this, nullptr, adapterWrite, nullptr, nullptr);
  size_t len = vfprintf(adapter, (PGM_P) fmt, args);
  fclose(adapter);
  va_end(args);
  return len;
}
#endif
#endif


uint32_t PrintPlus::copyFrom(Stream& stream, uint32_t limit) {
  return copyFromUntil(0, stream, limit);
}

uint32_t PrintPlus::copyAvailableFrom(Stream& stream, uint32_t limit) {
  uint32_t length = 0;
  while (stream.available() && (!limit || length < limit)) {
    if (!write(stream.read()) || getWriteError()) {
      if (!getWriteError()) {
        setWriteError();
      }
      break;
    }
    length++;
  }
  return length;
}

uint32_t PrintPlus::copyFromUntil(char terminator, Stream& stream, uint32_t limit) {
  byte b;
  uint32_t length = 0;
  while (stream.readBytes(&b, 1) && (!limit || length < limit)) {
    if (terminator && b == terminator)
      break;
    if (!write(b) || getWriteError()) {
      if (!getWriteError()) {
        setWriteError();
      }
      break;
    }
    length++;
  }
  return length;
}

