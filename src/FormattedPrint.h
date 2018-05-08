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

#ifndef _FORMATTEDPRINT_H_
#define _FORMATTEDPRINT_H_

#include <Arduino.h>

class FormattedPrint : public Print {

public:

#if defined(__AVR__) || defined(ESP8266)

  size_t printf(const char *fmt, ... );

  size_t printf(const __FlashStringHelper *fmt, ... );

#endif

};

#endif
