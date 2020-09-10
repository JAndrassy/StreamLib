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

#ifndef _BUFFEREDPRINT_H_
#define _BUFFEREDPRINT_H_

#include "PrintPlus.h"

class BufferedPrint : public PrintPlus {

protected:
  Print &target;
  char* buffer;
  size_t size;
  size_t pos;

public:
  BufferedPrint(Print &target, char* buffer, size_t size);

  virtual size_t write(uint8_t b);

  using Print::write; // pull in write(str) and write(buf, size) from Print

  virtual void flush();

  virtual int availableForWrite();

};

#endif
