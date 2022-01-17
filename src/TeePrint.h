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

#ifndef TEEPRINT_H_
#define TEEPRINT_H_

#include <Arduino.h>

class TeePrint: public PrintPlus {

  Print &out1;
  Print &out2;

public:

  TeePrint(Print &_out1, Print &_out2) : out1(_out1), out2(_out2) {}

  virtual size_t write(uint8_t b) {
    out1.write(b);
    return out2.write(b);
  }

  virtual size_t write(const uint8_t *buffer, size_t size) {
    out1.write(buffer, size);
    return out2.write(buffer, size);
  }


  virtual int availableForWrite() {
  	return min(out1.availableForWrite(), out2.availableForWrite());
  }

  virtual void flush() {
    out1.flush();
    out2.flush();
  }

};

#endif
