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

#ifndef STRINGREADSTREAM_H_
#define STRINGREADSTREAM_H_

#include <Arduino.h>

class StringReadStream: public Stream {

protected:
  const char *str = nullptr;
  const bool progmem = false;
  int length = 0;
  int pos = 0;

public:

  StringReadStream(const char *str, bool progmem = false);
  StringReadStream(__FlashStringHelper* str);
  StringReadStream(String& str); // the String content is not copied!

  virtual int available();
  virtual int read();
  virtual int peek();

  virtual size_t write(uint8_t b) {
    return 0;
  }

private:
  StringReadStream(StringReadStream& other) {} // disabled copying
};

#endif
