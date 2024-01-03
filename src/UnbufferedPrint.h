/*
 Copyright (C) 2024 Juraj Andrássy
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

#ifndef _UNBUFFEREDPRINT_H_
#define _UNBUFFEREDPRINT_H_

#include "PrintPlus.h"

class UnbufferedPrint : public PrintPlus {

protected:
  Print& target;

public:
  UnbufferedPrint(Print &_target) : target(_target) {}

  virtual size_t write(uint8_t b) {
    return target.write(b);
  }

  virtual size_t write(const uint8_t *buffer, size_t length) {
    return target.write(buffer, length);
  }

  using Print::write; // pull in write(str) and write(buf, size) from Print

  virtual void flush() {
    target.flush();
  }

  virtual int availableForWrite() {
    return target.availableForWrite();
  }

};

#endif
