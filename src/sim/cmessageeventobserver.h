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
#include "cobserver.h"

//---

class cMessageEventDatagram;

/**
 * An abstract base class for message event listeners.  Note that the simulation
 * environment already has an event log recording feature, which message event
 * listeners should not try to replicate; rather the purpose for message event
 * listeners is to perform runtime message event analysis.
 *
 * @todo Rename to cMessageEventObserver.  Add super class cObserver.  Make
 * the Datagram class extend the cObserverDatagram class.
 */
class cMessageEventObserver : public cLoggableObserver
{
private:
	static std::string __default_signal_name;

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

	/** @name Implemented from cObserver */
	//@{

	/**
	 * Checks that the object pointer is of type cMessageEventDatagram and calls
	 * handleSignal for cMessageEventDatagram objects.
	 *
	 * @throw Throws a cRuntimeError if the datagram pointer is not of type
	 * cMesssageEventDatagram or is NULL.
	 */
	virtual void handleSignal(cComponent * source, simsignal_t signalID,
			cObserverDatagram * datagram);

public:

	/**
	 * Subclasses should implement to return the default signal name (probably
	 * a static field).
	 */
	virtual const std::string & getDefaultSignalName() const { return __default_signal_name; }

	//@}

};

//---

class cMessageEventDatagram : public cObserverDatagram
{
private:
	cMessage * _msg_ptr;
	int _interface_id;

	void initialize(const cMessage * msg, const int & id);
	void copy(const cMessageEventDatagram & other);

protected:
	/*
	 * Provided to allow subclasses to delete the message pointer.
	 */
	void deleteMessage();

public:
	/** @name Constructors, Destructor, and Assignment Operator */
	//@{
	cMessageEventDatagram() { initialize(NULL, -1); }
	cMessageEventDatagram(const cMessage * msg, const int & id) { initialize(msg, id); }
	cMessageEventDatagram(const cMessageEventDatagram & other) { initialize(NULL, -1); copy(other); }
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
