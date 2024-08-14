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

#ifndef CAITLYN_TEXT_UNICODE_CONVERSION_H_
#define CAITLYN_TEXT_UNICODE_CONVERSION_H_

#include <stdexcept>

#include "caitlyn/text/unicode/length.h"

namespace cait {
namespace unicode {

template <typename CharT>
CodePoint ToCodePoint(const Sequence<CharT>& sequence);

template <>
inline CodePoint ToCodePoint(const Sequence<char>& sequence) {
  if (!IsValidUnicodeSequence(sequence)) {
    throw std::invalid_argument{"Invalid Unicode sequence"};
  }
  CodePoint code_point;
  const auto lead = MakeByte(sequence[0]);

  if ((lead & 0x80) == 0x0) {
    code_point = lead;
  } else if ((lead & 0xE0) == 0xC0) {
    if (sequence.size() < 2) {
      throw std::invalid_argument{"Invalid Unicode sequence"};
    }
    code_point = (lead & 0x1F) << 6;
    code_point |= (MakeByte(sequence[1]) & 0x3F);
  } else if ((lead & 0xF0) == 0xE0) {
    if (sequence.size() < 3) {
      throw std::invalid_argument{"Invalid Unicode sequence"};
    }
    code_point = (lead & 0x0F) << 12;
    code_point |= (MakeByte(sequence[1]) & 0x3F) << 6;
    code_point |= (MakeByte(sequence[2]) & 0x3F);
  } else if ((lead & 0xF8) == 0xF0) {
    if (sequence.size() < 4) {
      throw std::invalid_argument{"Invalid Unicode sequence"};
    }
    code_point = (lead & 0x07) << 18;
    code_point |= (MakeByte(sequence[1]) & 0x3F) << 12;
    code_point |= (MakeByte(sequence[2]) & 0x3F) << 6;
    code_point |= (MakeByte(sequence[3]) & 0x3F);
  } else {
    throw std::invalid_argument{"Invalid lead byte"};
  }

  return code_point;
}

inline Sequence<char> FromCodePoint(const CodePoint code_point) {
  const auto length = GetLength(code_point);
  SequenceBuilder<char> result;

  if (length == 1) {
    result << MakeRawByte(code_point);
  } else if (length == 2) {
    result << MakeRawByte(0xC0 | (code_point >> 6));
    result << MakeRawByte(0x80 | (code_point & 0x3F));
  } else if (length == 3) {
    result << MakeRawByte(0xE0 | (code_point >> 12));
    result << MakeRawByte(0x80 | ((code_point >> 6) & 0x3F));
    result << MakeRawByte(0x80 | (code_point & 0x3F));
  } else if (length == 4) {
    result << MakeRawByte(0xF0 | (code_point >> 18));
    result << MakeRawByte(0x80 | ((code_point >> 12) & 0x3F));
    result << MakeRawByte(0x80 | ((code_point >> 6) & 0x3F));
    result << MakeRawByte(0x80 | (code_point & 0x3F));
  }
  return result.str();
}

inline Sequence<char> FromCodePoint(const Byte value) {
  return FromCodePoint(MakeCodePoint(value));
}

} // namespace unicode
} // namespace cait

#endif // CAITLYN_TEXT_UNICODE_CONVERSION_H_
