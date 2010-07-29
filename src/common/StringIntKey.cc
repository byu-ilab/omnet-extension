//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "StringIntKey.h"

void StringIntKey::initialize(const std::string & s_value, const int & i_value)
{
	setStringPart(s_value);
	setIntPart(i_value);
}

bool StringIntKey::operator < (const StringIntKey & other) const
{
	// Remember it should behave like < (less than)

	if (this->_string_part < other._string_part)
	{
		return true;
	}
	if (this->_string_part == other._string_part)
	{
		if (this->_int_part < other._int_part)
		{
			return true;
		}
		return false;
	}
	return false;
}
