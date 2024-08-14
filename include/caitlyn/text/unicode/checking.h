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

#ifndef CAITLYN_TEXT_UNICODE_CHECKING_H_
#define CAITLYN_TEXT_UNICODE_CHECKING_H_

#include "caitlyn/text/unicode/utility.h"

namespace cait {
namespace unicode {

inline bool IsContinuationByte(const Byte value) {
  return (value & 0xC0) == 0x80;
}

template <typename CharT>
bool IsValidUnicodeSequence(const Sequence<CharT>& sequence);

template <>
inline bool IsValidUnicodeSequence(const Sequence<char>& sequence) {
  const auto length = sequence.length();

  if (length == 0 || length > 4) {
    return false;
  }
  const auto lead = MakeByte(sequence[0]);

  if ((lead & 0x80) == 0) {  // 0xxxxxxx
    return length == 1;
  }

  if ((lead & 0xE0) == 0xC0) {  // 110xxxxx 10xxxxxx
    return length == 2 && IsContinuationByte(sequence[1]) && lead >= 0xC2;
  }

  if ((lead & 0xF0) == 0xE0) {  // 1110xxxx 10xxxxxx 10xxxxxx
    return length == 3 && IsContinuationByte(sequence[1]) &&
           IsContinuationByte(sequence[2]) &&
           !(lead == 0xE0 && (MakeByte(sequence[1]) & 0xE0) == 0x80);
  }

  if ((lead & 0xF8) == 0xF0) {  // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    return length == 4 && IsContinuationByte(sequence[1]) &&
           IsContinuationByte(sequence[2]) && IsContinuationByte(sequence[3]) &&
           !(lead == 0xF0 && (MakeByte(sequence[1]) & 0xF0) == 0x80);
  }
  return false;
}

}  // namespace unicode
}  // namespace cait

#endif  // CAITLYN_TEXT_UNICODE_CHECKING_H_
