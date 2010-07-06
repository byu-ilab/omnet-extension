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
// Author: Kevin Black
// Patterned after result recorder base classes in resultrecorder.h and .cc

#ifndef DYNAMICRESULTRECORDER_H_
#define DYNAMICRESULTRECORDER_H_

#include "omnetppextension.h"
#include <envirdefs.h>
#include <resultrecorder.h>
#include <string.h>
#include <patternmatcher.h>

// Could become the parent class to cTimestampedValue inasmuch this class
// was patterned off of that one.
class ENVIR_API EncapsulatedValue : public cObject, public noncopyable
{
public:
	enum ValueType {UNDEF, LONG, ULONG, DOUBLE, SIMTIME, STRING, OBJECT};

private:
	ValueType type;
	union {
		long l;
		unsigned long ul;
		double d;
		const char * s;
		cObject * obj;
	};
	SimTime t;

public:
	/** @name Constructors and Destructor */
	//@{
	EncapsulatedValue() 				{ this->type=UNDEF; }
	EncapsulatedValue(long l) 			{ setValue(l); }
	EncapsulatedValue(unsigned long ul) { setValue(ul); }
	EncapsulatedValue(double d) 		{ setValue(d); }
	EncapsulatedValue(const SimTime& t) { setValue(t); }
	EncapsulatedValue(const char * s) 	{ setValue(s); }
	EncapsulatedValue(cObject *obj) 	{ setValue(obj); }
	virtual ~EncapsulatedValue() {}
	//@}

	/** @name Setters */
	//@{
	virtual void setValue(long l) 				{ this->type=LONG; this->l = l; }
	virtual void setValue(unsigned long ul) 	{ this->type=ULONG; this->ul = ul; }
	virtual void setValue(double d) 			{ this->type=DOUBLE; this->d = d; }
	virtual void setValue(const SimTime& t) 	{ this->type=SIMTIME; this->t = t; }
	virtual void setValue(const char * s) 		{ this->type=STRING; this->s = s; }
	virtual void setValue(cObject * obj) 		{ this->type=OBJECT; this->obj = obj; }
	//@}

	/** @name Getters; use getValueType to determine which datatype getter to call. */
	/** Returns the data type of the stored value. */
	virtual ValueType getValueType() const { return type; }

	virtual long 			longValue() const 			{return l;}
	virtual unsigned long 	unsignedLongValue() const 	{return ul;}
	virtual double 			doubleValue() const 		{return d;}
	virtual SimTime 		simtimeValue() const 		{return t;}
	virtual const char * 	stringValue() const 		{return s;}
	virtual cObject * 		objectValue() const 		{return obj;}
	//@}
};

/*
 * Contains the statistic name and value that will be checked and used by the
 * dynamic result recorders.
 * Patterned after cTimestampedValue
 */
class ENVIR_API DynamicResultValue : public EncapsulatedValue
{
private:
	static CommonStringPool namesPool;

	const char * statisticName;

public:
	/** @name Constructors and Destructor */
	//@{
	DynamicResultValue() : EncapsulatedValue() {}
	DynamicResultValue(const char * statname, long l) : EncapsulatedValue(l) { setStatisticName(statname); }
	DynamicResultValue(const char * statname, unsigned long ul) : EncapsulatedValue(ul) { setStatisticName(statname); }
	DynamicResultValue(const char * statname, double d) : EncapsulatedValue(d) { setStatisticName(statname); }
	DynamicResultValue(const char * statname, const SimTime& t) : EncapsulatedValue(t) { setStatisticName(statname); }
	DynamicResultValue(const char * statname, const char * s) : EncapsulatedValue(s) { setStatisticName(statname); }
	DynamicResultValue(const char * statname, cObject *obj) : EncapsulatedValue(obj) { setStatisticName(statname); }
	virtual ~DynamicResultValue() {}
	//@}

	/** @name Setters */
	//@{
	virtual void setStatisticName(const char * statname) { ASSERT(statname != NULL); this->statisticName = namesPool.get(statname); }
	//@}

	/** @name Getters */
	//@{
	virtual const char * getStatisticName() const { return statisticName; }
	//@}
};

// Type definitions
// taken from http://www.gotapi.com/ccpp under the maps constructor example
struct StringComparator {
	bool operator()( const char* s1, const char* s2 ) const {
		return strcmp( s1, s2 ) < 0;
	}
};

typedef std::map<const char *, void *, StringComparator> DynamicResultsMap;
typedef std::set<const char *> ResultNames;

/*
 * Base class for dynamic recorders.
 */
class ENVIR_API DynamicResultRecorder : public ResultRecorder
{
private:
	static CommonStringPool resultNamesPool;

	PatternMatcher matcher;

	DynamicResultsMap results_map;

protected:
	/** @name Results Collection Accessors and Manipulators */
	//@{
	/*
	 * Returns the names of the results in the results collection.  Can then be used
	 * to "iterate" over the results collection.
	 */
	ResultNames getResultNames() const;

	/*
	 * If either the result name or the value are NULL then the results collection
	 * is not modified.
	 */
	void setResultValue(const char * result_name, void * result_value);

	/*
	 * Returns NULL if no value is set for the result name or if the result name
	 * is NULL.
	 */
	void * getResultValue(const char * result_name) const;

	/*
	 * Removes the entry for the result from the results collection.  Returns the
	 * result value pointer, relinquishing responsibility for it.
	 */
	void * removeResultValue(const char * result_name);

	/*
	 * Determines whether a result entry for the indicated result name exists
	 * or does not exist.
	 */
	bool resultEntryExists(const char * result_name) const;

	/*
	 * If the result name matches the pattern and a result entry does not exist
	 * for it, invokes makeResultValue() to get a void pointer to the result
	 * value and inserts it into the results collection.  Returns true if an
	 * entry was created and false if it was not (i.e. the result name doesn't
	 * match the pattern or an entry already exists).
	 */
	//bool initializeResultEntry(const char * result_name);

	/*
	 * Subclasses should implement to allocate and initialize their specific
	 * result value type and then return it as a void pointer.  Invoked by
	 * the receiveSignal([...] cObject *).  Provides the result name the result
	 * value will correspond to if that happens to be necessary/useful.
	 */
	virtual void * initializeResultValue(const char * result_name) { return NULL; }

	/*
	 * Subclasses should implement to appropriately cast the void pointer and
	 * deallocate the memory.  Invoked by the destructor.
	 */
	virtual void deleteResultValue(void * value) {}
	//@}

	/*
	 * Returns the name that should be used for the vector or scalar.
	 */
	virtual std::string getResultName(const char * result_name) const;

	virtual std::string getPostfixedModeForm(const char * result_name) const;

	/*
	 * Subclasses should implement to appropriately handle recording
	 * of the result.  Invoked by finish().
	 */
	virtual void recordResult(const char * result_name, void * result_value) {}

	virtual void handleValue(const char * r, simtime_t_cref t, long l) =0;
	virtual void handleValue(const char * r, simtime_t_cref t, unsigned long ul) =0;
	virtual void handleValue(const char * r, simtime_t_cref t, double d) =0;
	virtual void handleValue(const char * r, simtime_t_cref t, const SimTime& v) =0;
	virtual void handleValue(const char * r, simtime_t_cref t, const char * s) =0;
	virtual void handleValue(const char * r, simtime_t_cref t, cObject * obj) =0;

	/*
	 * Determines if the specified string matches the pattern.
	 */
	virtual bool matchesPattern(const char * line);

public:
	/*
	 * Iterates over the result entries and invokes deleteResultValue().
	 */
	virtual ~DynamicResultRecorder();

	/*
	 * Iterates over all of the result entries and invokes recordResult().
	 */
	virtual void finish(ResultFilter * prev);

	/*
	 * Delegates to ResultRecord::init() and then extracts the pattern attribute from the
	 * component's statistic property corresponding to the statisticName.
	 */
	virtual void init(cComponent *component, const char *statisticName, const char *recordingMode);

	// throws error
	virtual void receiveSignal(ResultFilter *prev, simtime_t_cref t, long l);
	virtual void receiveSignal(ResultFilter *prev, simtime_t_cref t, unsigned long l);
	virtual void receiveSignal(ResultFilter *prev, simtime_t_cref t, double d);
	virtual void receiveSignal(ResultFilter *prev, simtime_t_cref t, const SimTime& v);
	virtual void receiveSignal(ResultFilter *prev, simtime_t_cref t, const char *s);

	/*
	 * Checks that the object is a DynamicResultValue, verifies that it's
	 * statistic name matches the pattern, makes a result entry if it does
	 * not already exist, and calls handleValue() according to the object's data
	 * type.
	 */
	virtual void receiveSignal(ResultFilter *prev, simtime_t_cref t, cObject *obj);

	//TODO override getStatisticAttributes so as to suppress the pattern attribute?
};

/*
 * Base class for dynamic numeric recorders.
 */
class ENVIR_API NumericDynamicResultRecorder : public DynamicResultRecorder
{
private:
	double default_initial_result_value;

protected:
//	// makes a double pointer entry in the collection map if it doesn't
//	// already exist (if a double isn't needed subclasses should override this function)
//	// the double has the value returned by defaultResultValue
//	// returns true if an entry was created, and false if it already existed
//	virtual bool makeResultCollectionIfNecessary(const char * r);

	/** @name Overridden Results Collection Accessors and Manipulators */
	//@{
	/*
	 * By default creates a double pointer and sets it to the default initial result
	 * value (set in the constructor).  Subclasses should override to handle different
	 * result value types.
	 */
	virtual void * initializeResultValue(const char * result_name);

	/*
	 * By default treats the result value as a double.  Subclasses should override
	 * to treat different result value types.
	 */
	virtual void deleteResultValue(void * value);

	/*
	 * By default treats the result value as a double and records it as a scalar.
	 * Subclasses should override to treat different result value types.
	 */
	virtual void recordResult(const char * result_name, void * result_value);
	//@}

	virtual void collect(const char * r, simtime_t_cref t, double d) =0;

	// delegates to collect
	virtual void handleValue(const char * r, simtime_t_cref t, long l);
	virtual void handleValue(const char * r, simtime_t_cref t, unsigned long ul);
	virtual void handleValue(const char * r, simtime_t_cref t, double d);
	virtual void handleValue(const char * r, simtime_t_cref t, const SimTime& v);
	virtual void handleValue(const char * r, simtime_t_cref t, const char * s);
	virtual void handleValue(const char * r, simtime_t_cref t, cObject * obj);

public:
	/*
	 * Sets the default initial result value (if using the default double result
	 * value type) to 0 (zero).
	 */
	NumericDynamicResultRecorder() : default_initial_result_value(0) {}

	/*
	 * Sets the default initial result value (if using the default double result
	 * value type) to the specified value.
	 */
	NumericDynamicResultRecorder(double d) : default_initial_result_value(d) {}
};

#endif /* DYNAMICRESULTRECORDER_H_ */
