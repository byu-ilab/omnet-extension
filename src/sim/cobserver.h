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

#ifndef COBSERVER_H_
#define COBSERVER_H_

#include "omnetppextension.h"

//---

/**
 * Parent class for all observer datagram objects.  Provided for object
 * classification and not for any functionality.
 */
class cObserverDatagram : public cObject
{
public:
	/** @name Constructors and Destructor */
	//@{

	cObserverDatagram() {}
	virtual ~cObserverDatagram() {}

	//@}
};

//---

/**
 * An abstract base class for simulation runtime observers.  Observers listen
 * on signals for cObserverDatagrams and perform analysis of the received data.
 * Analysis results can be printed to the simulation environment during runtime
 * or written out to the simulation environment or a log file when the
 * simulation terminates.  Observers should not be written to take the place of
 * already provided simulation logging features (e.g. event logging).
 */
class cObserver : public cListener
{
private:
	simsignal_t _default_signal_id;
	bool _new_data_since_finish_called;

public:
	cObserver() { _default_signal_id = SIMSIGNAL_NULL; }
	virtual ~cObserver() {}

protected:
	bool _getNewDataSinceFinishCalled() { return _new_data_since_finish_called; }
	void _setNewDataSinceFinishCalled(bool value) { _new_data_since_finish_called = value; }

	/** @name Functions to be implemented by subclasses */
	//@{

	/**
	 * Subclasses should implement to handle the signal and datagram in an
	 * appropriate fashion.
	 *
	 * @param source -- A cComponent pointer to the signal source.
	 * @param signalID -- The signal id.
	 * @param obj -- A cObserverDatagram object pointer.
	 *
	 * @return Nothing.
	 */
	virtual void handleSignal(cComponent * source, simsignal_t signalID,
			cObserverDatagram * datagram) =0;

public:

	/**
	 * Subclasses should implement to return the default signal name (probably
	 * a static field).
	 */
	virtual const std::string & getDefaultSignalName() const =0;

	//@}

	/** @name Convenient default signal access/subscription */
	//@{

	/**
	 * Subclasses should implement to return the default signal id.
	 */
	virtual simsignal_t getDefaultSignalID();

	virtual void subscribeOnDefaultSignal(cComponent * source);

	//@}

	/** @name Overridden from cListener */
	//@{

	/**
	 * Checks that the object pointer is of type cObserverDatagram and calls
	 * handleSignal.
	 *
	 * Sets the state variable _new_data_since_finish_called to true.
	 *
	 * @param source -- A cComponent pointer to the signal source.
	 * @param signalID -- The signal id.
	 * @param obj -- A cObject pointer which should be non-NULL and of type
	 * 		cObserverDatagram.
	 *
	 * @return Nothing.
	 *
	 * @throw Throws a cRuntimeError if the object pointer is not of type
	 * cObserverDatagram or is NULL.
	 */
	virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);

	/**
	 * Sets the state variable _new_data_since_finish_called to false.
	 */
	virtual void finish(cComponent *component, simsignal_t signalID);

	//@}

};

//---

/**
 * Abstract class that provides a log filename member and accessors.
 */
class cLoggableObserver : public cObserver
{
private:
	std::string _logfilename;

public:
	// Keep default constructor, copy constructor, assignment operator
	virtual ~cLoggableObserver() {}

	/** @name Log filename accessors */
	//@{

	virtual void setLogFilename(const std::string & filename) { _logfilename = filename; }
	const std::string & getLogFilename() const { return _logfilename; }

	//@}
};

#endif /* COBSERVER_H_ */
