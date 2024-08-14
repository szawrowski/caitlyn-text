/**
 * This file is part of the CaitlynText library
 * Copyright (C) 2024 Alexander Szawrowski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CAITLYN_TEXT_UNICODE_LENGTH_H_
#define CAITLYN_TEXT_UNICODE_LENGTH_H_

#include "caitlyn/text/unicode/types.h"

namespace cait {
namespace unicode {

inline size_t GetLength(const CodePoint code_point) {
  if (code_point <= 0x0000007F) {
    return 1; // 0xxxxxxx
  }
  if (code_point <= 0x000007FF) {
    return 2; // 110xxxxx 10xxxxxx
  }
  if (code_point <= 0x0000FFFF) {
    return 3; // 1110xxxx 10xxxxxx 10xxxxxx
  }
  if (code_point <= 0x0010FFFF) {
    return 4; // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
  }
  throw std::invalid_argument{"Invalid code point"};
}

inline size_t CalculateLength(const Byte lead) {
  if ((lead & 0x80) == 0x00) {
    return 1; // 0xxxxxxx
  }
  if ((lead & 0xE0) == 0xC0) {
    return 2; // 110xxxxx 10xxxxxx
  }
  if ((lead & 0xF0) == 0xE0) {
    return 3; // 1110xxxx 10xxxxxx 10xxxxxx
  }
  if ((lead & 0xF8) == 0xF0) {
    return 4; // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
  }
  throw std::invalid_argument{"Invalid lead byte"};
}

} // namespace unicode
} // namespace cait

#endif // CAITLYN_TEXT_UNICODE_LENGTH_H_
