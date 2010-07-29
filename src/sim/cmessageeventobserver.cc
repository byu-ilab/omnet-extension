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

#include "cmessageeventobserver.h"

//---

std::string cMessageEventObserver::__default_signal_name = "msgevent";

void cMessageEventObserver::handleSignal(cComponent * source, simsignal_t signalID, cObserverDatagram * datagram)
{
	cMessageEventDatagram * me_datagram = dynamic_cast<cMessageEventDatagram *>(datagram);
	if (me_datagram == NULL)
	{
		throw cRuntimeError("The datagram pointer is not of type cMessageEventDatagram.");
	}

	handleSignal(source, signalID, me_datagram);
}

//---

void cMessageEventDatagram::initialize(const cMessage * msg, const int & id)
{
	if (msg == NULL)
	{
		_msg_ptr = NULL;
	}
	else
	{
		_msg_ptr = msg->dup();
		take(_msg_ptr);
	}
	_interface_id = id;
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
