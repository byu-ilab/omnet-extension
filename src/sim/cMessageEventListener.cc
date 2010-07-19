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

#include "cMessageEventListener.h"

//---

void cMessageEventListener::receiveSignal(cComponent * source, simsignal_t signalID, cObject * obj)
{
	cMessageEventDatagram * datagram = dynamic_cast<cMessageEventDatagram *>(obj);
	if (datagram == NULL)
	{
		throw cRuntimeError("The object pointer is not of type cMessageEventDatagram.");
	}

	handleSignal(source, signalID, datagram);
}

//---

void cMessageEventDatagram::initialize()
{
	_msg_ptr = NULL;
	_interface_id = -1;
}

void cMessageEventDatagram::copy(const cMessageEventDatagram & other)
{
	ASSERT(this != &other);

	setMessage(other._msg_ptr);
	setInterfaceID(other._interface_id);
}

void cMessageEventDatagram::deleteMessage()
{
	if (_msg_ptr != NULL)
	{
		drop(_msg_ptr);
		delete _msg_ptr;
	}
}

cMessageEventDatagram & cMessageEventDatagram::operator = (const cMessageEventDatagram & other)
{
	if (this != &other)
	{
		copy(other);
	}

	return *this;
}

void cMessageEventDatagram::setMessage(const cMessage * msg)
{
	deleteMessage();

	if (msg != NULL)
	{
		_msg_ptr = msg->dup();
		take(_msg_ptr);
	}
}
