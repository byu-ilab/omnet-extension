/*
 * dynamicresultrecorders.h
 *
 *  Created on: Jul 1, 2010
 *      Author: Kevin Black
 *
 * Patterned on the result recorders in resultrecorders.h and .cc
 */

#ifndef DYNAMICRESULTRECORDERS_H_
#define DYNAMICRESULTRECORDERS_H_

#include "dynamicresultrecorder.h"
#include "omnetppextension.h"
#include <envirdefs.h>

/**
 * Listener for recording a signal to an output vector.
 * Patterned after the regular VectorRecorder
 */
class ENVIR_API DynamicVectorRecorder : public NumericDynamicResultRecorder
{
    protected:
		//enum VectorMode { ALL, PEAKS, CHANGE };

		struct VectorRef
		{
			void *handle;        // identifies output vector for the output vector manager
			simtime_t lastTime;  // to ensure increasing timestamp order

			VectorRef() { handle = NULL; lastTime = -1; }
		};

    protected:
        virtual void collect(const char * r, simtime_t_cref t, double value);
        //virtual bool makeResultCollectionIfNecessary(const char * r);

        virtual void * initializeResultValue(const char * result_name);

        virtual void deleteResultValue(void * value);

        /*
         * To negate the default action of NumericDynamicResultRecorder
         */
        virtual void recordResult(const char * result_name, void * result_value) {}
};

/**
 * Listener for recording the count of signal values. Signal values do not need
 * to be numeric to be counted.
 * Patterned after the regular CountRecorder
 */
class ENVIR_API DynamicCountRecorder : public DynamicResultRecorder
{
	protected:
		virtual void * initializeResultValue(const char * result_name);
		virtual void recordResult(const char * result_name, void * result_value);
		virtual void deleteResultValue(void * value);
		virtual void incrementCount(const char * result_name);

		virtual void handleValue(const char * r, simtime_t_cref t, long l) 			 { incrementCount(r); }
		virtual void handleValue(const char * r, simtime_t_cref t, unsigned long ul) { incrementCount(r); }
		virtual void handleValue(const char * r, simtime_t_cref t, double d) 		 { incrementCount(r); }
		virtual void handleValue(const char * r, simtime_t_cref t, const SimTime& v) { incrementCount(r); }
		virtual void handleValue(const char * r, simtime_t_cref t, const char * s)   { incrementCount(r); }
		virtual void handleValue(const char * r, simtime_t_cref t, cObject * obj) 	 { incrementCount(r); }
};

/**
 * Listener for recording the last signal value
 * Patterned after the regular LastValueRecorder
 */
class ENVIR_API DynamicLastValueRecorder : public NumericDynamicResultRecorder
{
    protected:
        virtual void collect(const char * r, simtime_t_cref t, double value);
};

/**
 * Listener for recording the sum of signal values
 * Patterned after the regular SumRecorder
 */
class ENVIR_API DynamicSumRecorder : public NumericDynamicResultRecorder
{
    protected:
        virtual void collect(const char * r, simtime_t_cref t, double value);
};

/**
 * Listener for recording the mean of signal values
 * Patterned after the regular MeanRecorder
 */
class ENVIR_API DynamicMeanRecorder : public NumericDynamicResultRecorder
{
    protected:
		struct MeanData
		{
			long count;
			double sum;

			MeanData() { count = 0; sum = 0; }
		};

    protected:
		//virtual bool makeResultCollectionIfNecessary(const char * result_name);
		virtual void * initializeResultValue(const char * result_name);
		virtual void recordResult(const char * result_name, void * result_value);
		virtual void deleteResultValue(void * value);
        virtual void collect(const char * r, simtime_t_cref t, double value);
};

/**
 * Listener for recording the minimum of signal values
 * Pattered after the regular MinRecorder
 */
class ENVIR_API DynamicMinRecorder : public NumericDynamicResultRecorder
{
    protected:
		virtual void recordResult(const char * result_name, void * result_value);
		//virtual double initialResultValue() { return POSITIVE_INFINITY; }
        virtual void collect(const char * r, simtime_t_cref t, double value);

    public:
        DynamicMinRecorder() : NumericDynamicResultRecorder(POSITIVE_INFINITY) {}
};

/**
 * Listener for recording the maximum of signal values
 * Patterned after the regular MaxRecorder
 */
class ENVIR_API DynamicMaxRecorder : public NumericDynamicResultRecorder
{
    protected:
		virtual void recordResult(const char * result_name, void * result_value);
		//virtual double initialResultValue() { return NEGATIVE_INFINITY; }
        virtual void collect(const char * r, simtime_t_cref t, double value);

    public:
        DynamicMaxRecorder() : NumericDynamicResultRecorder(NEGATIVE_INFINITY) {}
};

/**
 * Listener for recording the time average of signal values
 * Patterned after the regular TimeAverageRecorder
 */
class ENVIR_API DynamicTimeAverageRecorder : public NumericDynamicResultRecorder
{
    protected:
		struct TimeAverageData
		{
			simtime_t startTime;
			simtime_t lastTime;
			double lastValue;
			double weightedSum;

			TimeAverageData() { startTime = lastTime = -1; lastValue = weightedSum = 0; }
		};

    protected:
		//virtual bool makeResultCollectionIfNecessary(const char * result_name);
		virtual void * initializeResultValue(const char * result_name);
		virtual void recordResult(const char * result_name, void * result_value);
		virtual void deleteResultValue(void * value);
        virtual void collect(const char * r, simtime_t_cref t, double value);
};

/**
 * Listener for recording signal values via a cStatistic
 * Patterned after the regular StatisticsRecorder
 */
class ENVIR_API DynamicStatisticsRecorder : public NumericDynamicResultRecorder, protected cObject /*so it can own the statistic object*/
{
    //protected:
    //    cStatistic *statistic;

    protected:
        virtual void recordResult(const char * result_name, void * result_value);
        virtual void deleteResultValue(void * value);
        virtual void collect(const char * r, simtime_t_cref t, double value);

    //public:
        //DynamicStatisticsRecorder(cStatistic *stat) {statistic = stat; take(statistic);}
        //virtual ~StatisticsRecorder() {drop(statistic); delete statistic;}
        //virtual void finish(ResultFilter *prev);
};

class ENVIR_API DynamicStatsRecorder : public DynamicStatisticsRecorder
{
	protected:
		virtual void * initializeResultValue(const char * result_name);
		//virtual bool makeResultCollectionIfNecessary(const char * result_name);
//    public:
//        DynamicStatsRecorder();
};

class ENVIR_API DynamicHistogramRecorder : public DynamicStatisticsRecorder
{
	protected:
		virtual void * initializeResultValue(const char * result_name);
		//virtual bool makeResultCollectionIfNecessary(const char * result_name);

//    public:
//        DynamicHistogramRecorder();
};

// We shouldn't need a dynamic expression recorder inasmuch as it is not a
// statistics collector (per se)
///**
// * Result recorder that remembers the last value of a signal,
// * and in finish() it evaluates an expression and saves the result.
// */
////TODO: make variants that eat 2 signals, and N signals
//class ENVIR_API DynamicExpressionRecorder : public NumericDynamicResultRecorder
//{
//    protected:
//        Expression expr;
//    public:
//        // current values, valid inside process() only
//        double lastValue;
//    protected:
//        virtual void collect(simtime_t_cref t, double value) {lastValue = value;}
//    public:
//        ExpressionRecorder() {lastValue=NaN;}
//        virtual std::string str() const {return expr.str()+" (ExpressionRecorder)";}
//        virtual Expression& getExpression() {return expr;}
//        virtual Expression::Functor *makeValueVariable();
//        virtual Expression::Functor *makeTimeVariable();
//        virtual void finish(ResultFilter *prev);
//};


#endif /* DYNAMICRESULTRECORDERS_H_ */
