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

#ifndef STRINGINTKEY_H_
#define STRINGINTKEY_H_

#include <string>

class StringIntKey
{
private:
	std::string _string_part;
	int _int_part;

	void initialize(const std::string & s_value, const int & i_value);

protected:
	/** @name Private field accessors for subclasses */
	//@{

	inline const std::string & _get_string_part() const { return _string_part; }
	inline const int &         _get_int_part()    const { return _int_part; }

	//@}

public:
	StringIntKey() { initialize("", -1); }

	StringIntKey(const std::string & s_value, const int & i_value) { initialize(s_value, i_value); }

	virtual ~StringIntKey() {}

	bool operator < (const StringIntKey & other) const;

	virtual void setStringPart(const std::string & s_value) { _string_part = s_value; }
	virtual void setIntPart(const int & i_value) { _int_part = i_value; }

	std::string getStringPart() const { return _string_part; }
	int getIntPart() const { return _int_part; }
};
#endif /* STRINGINTKEY_H_ */
