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

#include "dynamicresultrecorder.h"

#define DEBUG_CLASS false

bool EncapsulatedValue::increment()
{
	bool did_increment = true;
	switch(getValueType())
	{
	case LONG: 	  ++l; break;
	case ULONG:   ++ul; break;
	case DOUBLE:  ++d; break;
	case SIMTIME: t += 1; break;
	default: // STRING and OBJECT
		did_increment = false;
		break;
	}
	return did_increment;
}

bool EncapsulatedValue::decrement()
{
	bool did_decrement = true;
	switch(getValueType())
	{
	case LONG: 	  --l; break;
	case ULONG:   --ul; break;
	case DOUBLE:  --d; break;
	case SIMTIME: t -= 1; break;
	default: // STRING and OBJECT
		did_decrement = false;
		break;
	}
	return did_decrement;
}

CommonStringPool DynamicResultValue::namesPool;

CommonStringPool DynamicResultRecorder::resultNamesPool;

DynamicResultRecorder::~DynamicResultRecorder()
{
	for (DynamicResultsMap::iterator it = results_map.begin(); it != results_map.end(); ++it)
	{
		deleteResultValue(it->second);
		it->second = NULL;
	}
}

void DynamicResultRecorder::init(cComponent *component, const char *statisticName, const char *recordingMode)
{
	ResultRecorder::init(component, statisticName, recordingMode);

	cProperty *property = getComponent()->getProperties()->get("statistic", getStatisticName());
	if (property == NULL)
	{
		return;
	}

	// get the pattern string
	const char * pattern = property->getValue("pattern");

	if (pattern == NULL)
	{
		pattern = property->getValue("title");
	}

	if (pattern == NULL)
	{
		pattern = getStatisticName();
	}

	// TODO make the pattern settings configurable?
	matcher.setPattern(pattern, true, true, true);
	LOG_DEBUG_LN("Initialized: mode: "<<getRecordingMode()<<"\t\t pattern: "<<pattern);
}

bool DynamicResultRecorder::matchesPattern(const char * line)
{
	return matcher.matches(line);
}

ResultNames DynamicResultRecorder::getResultNames() const
{
	ResultNames keys;
	DynamicResultsMap::const_iterator it = results_map.begin();
	for ( ; it != results_map.end(); it++)
	{
		keys.insert(it->first);
	}
	return keys;
}

void DynamicResultRecorder::setResultValue(const char * result_name, void * result_value)
{
	if (result_name != NULL && result_value != NULL)
	{
		results_map[result_name] = result_value;
	}
}

void * DynamicResultRecorder::getResultValue(const char * result_name) const
{
	if (result_name == NULL)
	{
		return NULL;
	}

	DynamicResultsMap::const_iterator drm_itr = results_map.find(result_name);

	if (drm_itr == results_map.end())
	{
		return NULL;
	}

	return drm_itr->second;
}

void * DynamicResultRecorder::removeResultValue(const char * result_name)
{
	if (result_name == NULL)
	{
		return NULL;
	}

	DynamicResultsMap::iterator drm_itr = results_map.find(result_name);

	if (drm_itr == results_map.end())
	{
		return NULL;
	}

	void * value = drm_itr->second;
	results_map.erase(drm_itr);

	return value;
}

bool DynamicResultRecorder::resultEntryExists(const char * result_name) const
{
	return results_map.find(result_name) != results_map.end();
}

std::string DynamicResultRecorder::getResultName(const char * result_name) const
{

#define USE_DYNAMIC_NAME true
#ifdef USE_DYNAMIC_NAME
	// use dynamic-name:record-mode form
	return getPostfixedModeForm(result_name);
#undef USE_DYNAMIC_NAME
#else
	// use statistic-name:record-mode form
	return getResultName();
#endif
}

std::string DynamicResultRecorder::getPostfixedModeForm(const char * result_name) const
{
	return (std::string(result_name)+":"+getRecordingMode());
}

#define EXPECTED_OBJECT_NAME "DynamicResultValue"
#define THROW(datatype) throw cRuntimeError("%s: Cannot record %s value.  Encapsulate in a %s object.", getClassName(), datatype, EXPECTED_OBJECT_NAME)


void DynamicResultRecorder::receiveSignal(ResultFilter *prev, simtime_t_cref t, long l)
{
	THROW("long");
}

void DynamicResultRecorder::receiveSignal(ResultFilter *prev, simtime_t_cref t, unsigned long l)
{
	THROW("unsigned long");
}

void DynamicResultRecorder::receiveSignal(ResultFilter *prev, simtime_t_cref t, double d)
{
	THROW("double");
}

void DynamicResultRecorder::receiveSignal(ResultFilter *prev, simtime_t_cref t, const SimTime& v)
{
	THROW("SimTime");
}

void DynamicResultRecorder::receiveSignal(ResultFilter *prev, simtime_t_cref t, const char *s)
{
	THROW("const char *");
}

#undef THROW

void DynamicResultRecorder::receiveSignal(ResultFilter *prev, simtime_t_cref t, cObject *obj)
{
	//LOG_DEBUG_FUN_BEGIN("");
	DynamicResultValue * wrapper = dynamic_cast<DynamicResultValue *>(obj);
	if (wrapper == NULL)
	{
		throw cRuntimeError("%s: Cannot record object of non-type %s.", getClassName(), EXPECTED_OBJECT_NAME);
	}

	const char * result_name = wrapper->getStatisticName();
	ASSERT(result_name != NULL);

	if (!resultEntryExists(result_name) && matchesPattern(result_name))
	{
		setResultValue(result_name, initializeResultValue(result_name));
	}

	if (resultEntryExists(result_name))
	{
		// Only executes if the result name matches the pattern and the subclass appropriately
		// implemented initializeResultValue()
		switch(wrapper->getValueType())
		{
			case EncapsulatedValue::LONG:    handleValue(result_name, t, wrapper->longValue()); break;
			case EncapsulatedValue::ULONG:   handleValue(result_name, t, wrapper->unsignedLongValue()); break;
			case EncapsulatedValue::DOUBLE:  handleValue(result_name, t, wrapper->doubleValue()); break;
			case EncapsulatedValue::SIMTIME: handleValue(result_name, t, wrapper->simtimeValue()); break;
			case EncapsulatedValue::STRING:  handleValue(result_name, t, wrapper->stringValue()); break;
			case EncapsulatedValue::OBJECT:  handleValue(result_name, t, wrapper->objectValue()); break;
			default: throw cRuntimeError("%s: Got %s object with undefined or unknown data type.", getClassName(), EXPECTED_OBJECT_NAME);
		}
	}
	//LOG_DEBUG_FUN_END("");
}

void DynamicResultRecorder::finish(ResultFilter * prev)
{
	for (DynamicResultsMap::iterator it = results_map.begin(); it != results_map.end(); ++it)
	{
		recordResult(it->first, it->second);
	}
}

#undef EXPECTED_OBJECT_NAME

//---

//bool NumericDynamicResultRecorder::makeResultCollectionIfNecessary(const char * result_name)
//{
//	ASSERT(result_name != NULL);
//
//	if (getResultValue(result_name) == NULL)
//	{
//		setResultValue(result_name, (void *) new double(initialResultValue()));
//		return true;
//	}
//	return false;
//}

void * NumericDynamicResultRecorder::initializeResultValue(const char * result_name)
{
	return static_cast<void *>(new double(default_initial_result_value));
}

void NumericDynamicResultRecorder::recordResult(const char * result_name, void * result_value)
{
	opp_string_map attributes = getStatisticAttributes();
	ev.recordScalar(getComponent(), getResultName(result_name).c_str(),
			*(static_cast<double *>(result_value)), &attributes);
}

void NumericDynamicResultRecorder::deleteResultValue(void * value)
{
	double * value_ptr = static_cast<double *>(value);
	deleteSafe(value_ptr);
}

// calls makeResultCollectionIfNecessary and then collect
void NumericDynamicResultRecorder::handleValue(const char * r, simtime_t_cref t, long l)
{
	//makeResultCollectionIfNecessary(r);
	DEBUG_BLOCK(ASSERT(resultEntryExists(r)));
	collect(r, t, l);
}

void NumericDynamicResultRecorder::handleValue(const char * r, simtime_t_cref t, unsigned long ul)
{
	//makeResultCollectionIfNecessary(r);
	DEBUG_BLOCK(ASSERT(resultEntryExists(r)));
	collect(r, t, ul);
}

void NumericDynamicResultRecorder::handleValue(const char * r, simtime_t_cref t, double d)
{
	//makeResultCollectionIfNecessary(r);
	DEBUG_BLOCK(ASSERT(resultEntryExists(r)));
	collect(r, t, d);
}

void NumericDynamicResultRecorder::handleValue(const char * r, simtime_t_cref t, const SimTime& v)
{
	//makeResultCollectionIfNecessary(r);
	DEBUG_BLOCK(ASSERT(resultEntryExists(r)));
	collect(r, t, v.dbl());
}


#define THROW(datatype) throw cRuntimeError("%s: Cannot convert %s to double.", getClassName(), datatype)

void NumericDynamicResultRecorder::handleValue(const char * r, simtime_t_cref t, const char * s)
{
	THROW("const char *");
}

void NumericDynamicResultRecorder::handleValue(const char * r, simtime_t_cref t, cObject * obj)
{
	THROW("cObject *");
}

#undef THROW

