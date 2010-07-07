/*
 * dynamicresultrecorders.cc
 *
 *  Created on: Jul 1, 2010
 *      Author: Kevin Black
 *
 * The implementation of the Dynamic Result Recorders is patterned
 * off of the implementation of the regular result recorders in
 * resultrecorders.h
 */

#include "dynamicresultrecorders.h"

Register_ResultRecorder("dvector", DynamicVectorRecorder);
Register_ResultRecorder("dcount", DynamicCountRecorder);
Register_ResultRecorder("dlast", DynamicLastValueRecorder);
Register_ResultRecorder("dsum", DynamicSumRecorder);
Register_ResultRecorder("dmean", DynamicMeanRecorder);
Register_ResultRecorder("dmin", DynamicMinRecorder);
Register_ResultRecorder("dmax", DynamicMaxRecorder);
Register_ResultRecorder("dtimeavg", DynamicTimeAverageRecorder);
Register_ResultRecorder("dstats", DynamicStatsRecorder);
Register_ResultRecorder("dhistogram", DynamicHistogramRecorder);

#define DEBUG_CLASS true

//---

void DynamicVectorRecorder::deleteResultValue(void * value)
{
	VectorRef * result_value_ptr = static_cast<VectorRef *>(value);
	deleteSafe(result_value_ptr);
}

void * DynamicVectorRecorder::initializeResultValue(const char * result_name)
{
	VectorRef * vref_ptr = new VectorRef();
	vref_ptr->handle = ev.registerOutputVector(getComponent()->getFullPath().c_str(), getResultName(result_name).c_str());
	ASSERT(vref_ptr->handle != NULL);

	opp_string_map attributes = getStatisticAttributes();
	bool title_set = false;
	for (opp_string_map::iterator it = attributes.begin(); it != attributes.end(); ++it)
	{
		if (!strcmp(it->first.c_str(),"title") )
		{
			ev.setVectorAttribute(vref_ptr->handle, it->first.c_str(), getPostfixedModeForm(result_name).c_str());
			title_set = true;
		}
		else
		{
			ev.setVectorAttribute(vref_ptr->handle, it->first.c_str(), it->second.c_str());
		}
	}

	if (!title_set)
	{
		ev.setVectorAttribute(vref_ptr->handle, "title", getPostfixedModeForm(result_name).c_str());
	}

	return static_cast<void *>(vref_ptr);
}

//bool DynamicVectorRecorder::makeResultCollectionIfNecessary(const char * result_name)
//{
//	ASSERT(result_name != NULL);
//
//	VectorRef * result_value_ptr = static_cast<VectorRef *>(getResultValue(result_name));
//	if (result_value_ptr == NULL)
//	{
//		// make a vector reference and store it in the map
//		result_value_ptr = new VectorRef();
//		result_value_ptr->handle = ev.registerOutputVector(getComponent()->getFullPath().c_str(), result_name);
//		ASSERT(result_value_ptr->handle != NULL);
//
//		opp_string_map attributes = getStatisticAttributes();
//		for (opp_string_map::iterator it = attributes.begin(); it != attributes.end(); ++it)
//		{
//			ev.setVectorAttribute(result_value_ptr->handle, it->first.c_str(), it->second.c_str());
//		}
//
//		setResultValue(result_name, (void*) result_value_ptr);
//		return true;
//	}
//	return false;
//}

void DynamicVectorRecorder::collect(const char * result_name, simtime_t_cref t, double value)
{
	DEBUG_BLOCK(ASSERT(resultEntryExists(result_name)));

	VectorRef * result_value_ptr = static_cast<VectorRef *>(getResultValue(result_name));

    if (t < result_value_ptr->lastTime)
    {
        throw cRuntimeError("%s: Cannot record data with an earlier timestamp (t=%s) "
                            "than the previously recorded value (t=%s)",
                            getClassName(), SIMTIME_STR(t), SIMTIME_STR(result_value_ptr->lastTime));
    }

    result_value_ptr->lastTime = t;
    ev.recordInOutputVector(result_value_ptr->handle, t, value);

// Debug hook
//    bool recorded = ev.recordInOutputVector(result_value_ptr->handle, t, value);
//    if (!recorded)
//    {
//    	recorded = false;
//    }
}

//---

void * DynamicCountRecorder::initializeResultValue(const char * result_name)
{
	return static_cast<void *>(new uint64(0));
}

void DynamicCountRecorder::recordResult(const char * result_name, void * result_value)
{
    opp_string_map attributes = getStatisticAttributes();
    ev.recordScalar(getComponent(), getResultName(result_name).c_str(),
    		static_cast<double>(*(static_cast<uint64 *>(result_value))), &attributes);
}

void DynamicCountRecorder::deleteResultValue(void * value)
{
	uint64 * count_ptr = static_cast<uint64 *>(value);
	deleteSafe(count_ptr);
}

void DynamicCountRecorder::incrementCount(const char * result_name)
{
	DEBUG_BLOCK(ASSERT(resultEntryExists(result_name)));

	uint64 * count_ptr = static_cast<uint64 *>(getResultValue(result_name));
	ASSERT(*count_ptr < INT64_MAX);
	(*count_ptr)++;
}

//---

void DynamicLastValueRecorder::collect(const char * result_name, simtime_t_cref t, double value)
{
	DEBUG_BLOCK(ASSERT(resultEntryExists(result_name)));

	double * last_value_ptr = static_cast<double *>(getResultValue(result_name));
	(*last_value_ptr) = value;
}

//---

void DynamicSumRecorder::collect(const char * result_name, simtime_t_cref t, double value)
{
	DEBUG_BLOCK(ASSERT(resultEntryExists(result_name)));

	double * sum_ptr = static_cast<double *>(getResultValue(result_name));
	(*sum_ptr) += value;
}

//---

void * DynamicMeanRecorder::initializeResultValue(const char * result_name)
{
	return static_cast<void *>(new MeanData());
}

void DynamicMeanRecorder::recordResult(const char * result_name, void * result_value)
{
	MeanData * mean_ptr = static_cast<MeanData *>(result_value);
	double mean = mean_ptr->sum / mean_ptr->count;  // note: this is NaN if count==0

	opp_string_map attributes = getStatisticAttributes();
	ev.recordScalar(getComponent(), getResultName(result_name).c_str(), mean, &attributes);
}

void DynamicMeanRecorder::deleteResultValue(void * value)
{
	MeanData * mean_ptr = static_cast<MeanData *>(value);
	deleteSafe(mean_ptr);
}

//bool DynamicMeanRecorder::makeResultCollectionIfNecessary(const char * result_name)
//{
//	ASSERT(result_name != NULL);
//
//	if (getResultValue(result_name) == NULL)
//	{
//		setResultValue(result_name, (void *) new MeanData());
//		return true;
//	}
//	return false;
//}

void DynamicMeanRecorder::collect(const char * result_name, simtime_t_cref t, double value)
{
	DEBUG_BLOCK(ASSERT(resultEntryExists(result_name)));

	MeanData * mean_ptr = static_cast<MeanData *>(getResultValue(result_name));
	(mean_ptr->count)++;
	(mean_ptr->sum) += value;
}

//---

void DynamicMinRecorder::recordResult(const char * result_name, void * result_value)
{
	double min = *(static_cast<double *>(result_value));
	opp_string_map attributes = getStatisticAttributes();
	ev.recordScalar(getComponent(), getResultName(result_name).c_str(),
			isPositiveInfinity(min) ? NaN : min, &attributes);
}

void DynamicMinRecorder::collect(const char * result_name, simtime_t_cref t, double value)
{
	DEBUG_BLOCK(ASSERT(resultEntryExists(result_name)));

	double * min_ptr = static_cast<double *>(getResultValue(result_name));
	if (value < *min_ptr)
	{
		(*min_ptr) = value;
	}
}

//---

void DynamicMaxRecorder::recordResult(const char * result_name, void * result_value)
{
	double max = *(static_cast<double *>(result_value));
    opp_string_map attributes = getStatisticAttributes();
    ev.recordScalar(getComponent(), getResultName(result_name).c_str(),
    		isNegativeInfinity(max) ? NaN : max, &attributes);
}

void DynamicMaxRecorder::collect(const char * result_name, simtime_t_cref t, double value)
{
	DEBUG_BLOCK(ASSERT(resultEntryExists(result_name)));

	double * max_ptr = static_cast<double *>(getResultValue(result_name));
	if (*max_ptr < value)
	{
		(*max_ptr) = value;
	}
}

//---

void * DynamicTimeAverageRecorder::initializeResultValue(const char * result_name)
{
	return static_cast<void *>(new TimeAverageData());
}

void DynamicTimeAverageRecorder::recordResult(const char * result_name, void * result_value)
{
	TimeAverageData * tavg_ptr = static_cast<TimeAverageData *>(result_value);

	bool empty = (tavg_ptr->startTime < SIMTIME_ZERO);
	simtime_t t = simulation.getSimTime();
	collect(result_name, t, NaN); // to get the last interval counted in; the value is just a dummy
	double interval = SIMTIME_DBL(t - tavg_ptr->startTime);

	opp_string_map attributes = getStatisticAttributes();
	ev.recordScalar(getComponent(), getResultName(result_name).c_str(),
			empty ? NaN : (tavg_ptr->weightedSum / interval), &attributes);
}

void DynamicTimeAverageRecorder::deleteResultValue(void * result_value)
{
	TimeAverageData * tavg_ptr = static_cast<TimeAverageData *>(result_value);
	deleteSafe(tavg_ptr);
}

//bool DynamicTimeAverageRecorder::makeResultCollectionIfNecessary(const char * result_name)
//{
//	ASSERT(result_name != NULL);
//
//	if (getResultValue(result_name) == NULL)
//	{
//		setResultValue(result_name, (void *) new TimeAverageData());
//		return true;
//	}
//	return false;
//}

void DynamicTimeAverageRecorder::collect(const char * result_name, simtime_t_cref t, double value)
{
	DEBUG_BLOCK(ASSERT(resultEntryExists(result_name)));

	TimeAverageData * tavg_ptr = static_cast<TimeAverageData *>(getResultValue(result_name));

    if (tavg_ptr->startTime < SIMTIME_ZERO) // uninitialized
    {
        tavg_ptr->startTime = t;
    }
    else
    {
        tavg_ptr->weightedSum += tavg_ptr->lastValue * SIMTIME_DBL(t - tavg_ptr->lastTime);
    }
    tavg_ptr->lastTime = t;
    tavg_ptr->lastValue = value;
}

//---

void DynamicStatisticsRecorder::recordResult(const char * result_name, void * result_value)
{
    opp_string_map attributes = getStatisticAttributes();
    ev.recordStatistic(getComponent(), getResultName(result_name).c_str(),
    		static_cast<cStatistic *>(result_value), &attributes);
}

void DynamicStatisticsRecorder::deleteResultValue(void * value)
{
	cStatistic * stat_ptr = static_cast<cStatistic *>(value);
	drop(stat_ptr);
	deleteSafe(stat_ptr);
}

void DynamicStatisticsRecorder::collect(const char * result_name, simtime_t_cref t, double value)
{
	cStatistic * stat_ptr = static_cast<cStatistic *>(getResultValue(result_name));
	stat_ptr->collect(value);
}

void * DynamicStatsRecorder::initializeResultValue(const char * result_name)
{
	cStatistic * stat_ptr = new cStdDev();
	take(stat_ptr);
	return static_cast<void *>(stat_ptr);
}

//bool DynamicStatsRecorder::makeResultCollectionIfNecessary(const char * result_name)
//{
//	ASSERT(result_name != NULL);
//
//	if (getResultValue(result_name) == NULL)
//	{
//		cStatistic * stat_ptr = new cStdDev();
//		take(stat_ptr);
//		setResultValue(result_name, (void *) stat_ptr);
//		return true;
//	}
//	return false;
//}
//StatsRecorder::StatsRecorder() : StatisticsRecorder(new cStdDev())
//{
//}

void * DynamicHistogramRecorder::initializeResultValue(const char * result_name)
{
	cStatistic * stat_ptr = new cHistogram();
	take(stat_ptr);
	return static_cast<void *>(stat_ptr);
}

//bool DynamicHistogramRecorder::makeResultCollectionIfNecessary(const char * result_name)
//{
//	ASSERT(result_name != NULL);
//
//	if (getResultValue(result_name) == NULL)
//	{
//		cStatistic * stat_ptr = new cHistogram();
//		take(stat_ptr);
//		setResultValue(result_name, (void *) stat_ptr);
//		return true;
//	}
//	return false;
//}

//HistogramRecorder::HistogramRecorder() : StatisticsRecorder(new cHistogram())
//{
//}

//---

//class RecValueVariable : public Expression::Variable
//{
//  private:
//    ExpressionRecorder *owner;
//  public:
//    RecValueVariable(ExpressionRecorder *recorder) {owner = recorder;}
//    virtual Functor *dup() const {return new RecValueVariable(owner);}
//    virtual const char *getName() const {return "<lastsignalvalue>";}
//    virtual char getReturnType() const {return Expression::Value::DBL;}
//    virtual Expression::Value evaluate(Expression::Value args[], int numargs) {return owner->lastValue;}
//};
//
////XXX currently unused
//class RecTimeVariable : public Expression::Variable
//{
//  public:
//    virtual Functor *dup() const {return new RecTimeVariable();}
//    virtual const char *getName() const {return "<simtime>";}
//    virtual char getReturnType() const {return Expression::Value::DBL;}
//    virtual Expression::Value evaluate(Expression::Value args[], int numargs) {return SIMTIME_DBL(simulation.getSimTime());}
//};
//
//Expression::Functor *ExpressionRecorder::makeValueVariable()
//{
//    return new RecValueVariable(this);
//}
//
//Expression::Functor *ExpressionRecorder::makeTimeVariable()
//{
//    return new RecTimeVariable();
//}
//
//void ExpressionRecorder::finish(ResultFilter *prev)
//{
//    opp_string_map attributes = getStatisticAttributes();
//    ev.recordScalar(getComponent(), getResultName().c_str(), expr.doubleValue(), &attributes);
//}

