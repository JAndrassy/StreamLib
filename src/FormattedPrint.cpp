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

#include "FormattedPrint.h"

#ifdef __AVR__
int adapterPut(char c, FILE* _adapter) {
  return ((Print*) _adapter->udata) -> write(c);
}

size_t FormattedPrint::printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  FILE adapter;
  fdev_setup_stream(&adapter, adapterPut, NULL, _FDEV_SETUP_WRITE);
  fdev_set_udata(&adapter, this);
  size_t len = vfprintf(&adapter, fmt, args);
  va_end(args);
  return len;
}

size_t FormattedPrint::printf(const __FlashStringHelper *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  FILE adapter;
  fdev_setup_stream(&adapter, adapterPut, NULL, _FDEV_SETUP_WRITE);
  fdev_set_udata(&adapter, this);
  size_t len = vfprintf_P(&adapter, (const char*) fmt, args);
  va_end(args);
  return len;
}
#elif ESP8266

ssize_t adapterWrite(void* p, const char *buf, size_t n) {
  return ((Print*) p) -> write(buf, n);
}

FILE* openAdapter(void *p) {
  cookie_io_functions_t fncs; // @suppress("Type cannot be resolved")
  fncs.write = adapterWrite; // @suppress("Field cannot be resolved")
  fncs.close = NULL; // @suppress("Field cannot be resolved")
  return fopencookie(p, "w", fncs); // @suppress("Function cannot be resolved")
}

size_t FormattedPrint::printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  FILE* adapter = openAdapter(this);
  size_t len = vfprintf(adapter, fmt, args);
  fclose(adapter);
  va_end(args);
  return len;
}

size_t FormattedPrint::printf(const __FlashStringHelper *fmt, ...) {
  size_t fmtLen = strlen_P((PGM_P) fmt);
  char format[fmtLen + 1];
  strcpy_P(format, (PGM_P) fmt);
  va_list args;
  va_start(args, fmt);
  FILE* adapter = openAdapter(this);
  size_t len = vfprintf(adapter, format, args);
  fclose(adapter);
  va_end(args);
  return len;
}

#endif
