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

#include "cobserver.h"

#define DEBUG_CLASS false

//---

Register_Class(cObserverDatagram);

//---

void cObserver::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj)
{
	LOG_DEBUG_FUN_BEGIN("");

	cObserverDatagram * datagram = dynamic_cast<cObserverDatagram *>(obj);
	if (datagram == NULL)
	{
		throw cRuntimeError("Object is not of type cObserverDatagram.");
	}

	handleSignal(source, signalID, datagram);
	_setNewDataSinceFinishCalled(true);

	LOG_DEBUG_FUN_END("");
}

void cObserver::finish(cComponent *component, simsignal_t signalID)
{
	LOG_DEBUG_LN("Set new data since finished called to false");
	_setNewDataSinceFinishCalled(false);
}

simsignal_t cObserver::getDefaultSignalID()
{
	LOG_DEBUG_FUN_BEGIN("");
	if (_default_signal_id == SIMSIGNAL_NULL)
	{
		_default_signal_id = simulation.getSystemModule()->registerSignal(getDefaultSignalName().c_str());
	}
	LOG_DEBUG_LN("default signal id: "<<_default_signal_id);
	LOG_DEBUG_FUN_END("");
	return _default_signal_id;
}

void cObserver::subscribeOnDefaultSignal(cComponent * source)
{
	LOG_DEBUG_FUN_BEGIN("");
	source->subscribe(getDefaultSignalID(), this);
	LOG_DEBUG_FUN_END("");
}
