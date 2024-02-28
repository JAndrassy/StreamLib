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

#ifndef _CHUNKEDREADER_H_
#define _CHUNKEDREADER_H_

#include <Arduino.h>

class ChunkedStreamReader : public Stream {

protected:
  Stream& input;
  unsigned long counter = 0;

public:
  ChunkedStreamReader(Stream & input);

  virtual int available();
  virtual int read();
  virtual int peek();

  unsigned long chunkAvailable();

  virtual size_t write(uint8_t b) {
    (void) b;
    return 0;
  }

private:
  ChunkedStreamReader(ChunkedStreamReader& other) : input(other.input) {} // disabled copying
  void readChunkSize();
};


#endif
