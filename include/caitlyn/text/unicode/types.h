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

#ifndef CAITLYN_TEXT_UNICODE_TYPES_H_
#define CAITLYN_TEXT_UNICODE_TYPES_H_

#include <sstream>

namespace cait {

using CodePoint = uint32_t;
using Byte = unsigned char;
using RawByte = char;

namespace unicode {

template <typename CharT>
using Sequence = std::basic_string<CharT>;

template <typename CharT>
using SequenceBuilder = std::basic_ostringstream<CharT>;

}  // namespace unicode
}  // namespace cait

#endif  // CAITLYN_TEXT_UNICODE_TYPES_H_
