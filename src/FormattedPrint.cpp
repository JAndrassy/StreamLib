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

int adapterPut(char c, FILE* _adapter) {
  return ((Print*) _adapter->udata) -> write(c);
}

void FormattedPrint::printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  FILE adapter;
  fdev_setup_stream(&adapter, adapterPut, NULL, _FDEV_SETUP_WRITE);
  fdev_set_udata(&adapter, this);
  vfprintf(&adapter, fmt, args);
  va_end(args);
}

void FormattedPrint::printf(const __FlashStringHelper *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  FILE adapter;
  fdev_setup_stream(&adapter, adapterPut, NULL, _FDEV_SETUP_WRITE);
  fdev_set_udata(&adapter, this);
  vfprintf_P(&adapter, (const char*) fmt, args);
  va_end(args);
}

