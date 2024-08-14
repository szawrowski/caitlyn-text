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

#ifndef CAITLYN_TEXT_UNICODE_UTILITY_H_
#define CAITLYN_TEXT_UNICODE_UTILITY_H_

#include "caitlyn/text/unicode/types.h"

namespace cait {
namespace unicode {

inline CodePoint MakeCodePoint(const Byte value) {
  return value;
}

inline Byte MakeByte(const RawByte value) {
  return static_cast<Byte>(value);
}

inline RawByte MakeRawByte(const CodePoint value) {
  return static_cast<RawByte>(value);
}

}  // namespace unicode
}  // namespace cait

#endif  // CAITLYN_TEXT_UNICODE_UTILITY_H_
