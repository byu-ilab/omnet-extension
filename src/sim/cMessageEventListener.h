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

#ifndef CMESSAGEEVENTLISTENER_H_
#define CMESSAGEEVENTLISTENER_H_

#include "omnetppextension.h"

//---

class cMessageEventDatagram;

/**
 * An abstract base class for message event listeners.  Note that the simulation
 * environment already has an event log recording feature, which message event
 * listeners should not try to replicate; rather the purpose for message event
 * listeners is to perform runtime message event analysis.
 */
class cMessageEventListener : public cListener
{

protected:
	/** @name Functions to be implemented by subclasses */
	//@{

	/**
	 * Subclasses should implement to handle the signal and datagram in an
	 * appropriate fashion.
	 */
	virtual void handleSignal(cComponent * source, simsignal_t signalID,
			cMessageEventDatagram * datagram) =0;

	//@}

public:
	/** @name Overridden from cListener */
	//@{

	/**
	 * Checks that the object pointer is of type cMessageEventDatagram and calls
	 * handleMessageEventDatagram.
	 *
	 * @throw throws a cRuntimeError if the object pointer is not of type
	 * cMesssageEventDatagram.
	 */
	virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);

	//@}
};

//---

class cMessageEventDatagram : public cObject
{
private:
	cMessage * _msg_ptr;
	int _interface_id;

	void initialize();
	void copy(const cMessageEventDatagram & other);

protected:
	/*
	 * Provided to allow subclasses to delete the message pointer.
	 */
	void deleteMessage();

public:
	/** @name Constructors, Destructor, and Assignment Operator */
	//@{
	cMessageEventDatagram() { initialize(); }
	cMessageEventDatagram(const cMessageEventDatagram & other) { initialize(); copy(other); }
	virtual ~cMessageEventDatagram() { deleteMessage(); }

	cMessageEventDatagram & operator = (const cMessageEventDatagram & other);
	//@}

	/** @name Setters */
	//@{
	virtual void setMessage(const cMessage * msg);
	virtual void setInterfaceID(int id) { _interface_id = id; }
	//@}

	/** @name Getters */
	//@{
	const cMessage * getMessage() const { return _msg_ptr; }
	int getInterfaceID() const { return _interface_id; }
	//@}
};

#endif /* CMESSAGEEVENTLISTENER_H_ */
