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

#ifndef _BUFFEREDREADER_H_
#define _BUFFEREDREADER_H_

#include <Arduino.h>
#include <Client.h>

class BufferedClientReader : public Client {

protected:
  Client& client;
  uint8_t* buffer;
  size_t size;
  size_t length;
  size_t pos;

public:
  BufferedClientReader(Client& client, uint8_t* buffer, size_t size);

  virtual int connect(IPAddress ip, uint16_t port);
  virtual int connect(const char *host, uint16_t port);
  virtual void stop();
  virtual uint8_t connected();
  virtual operator bool();

  virtual int available();
  virtual int read();
  virtual int peek();
  virtual int read(uint8_t *buf, size_t size);

  virtual size_t write(uint8_t b);
  virtual size_t write(const uint8_t *buf, size_t length);
  virtual void flush();
  virtual int availableForWrite();

};

#endif
