/*
 * DebugDef.h
 *
 *  Created on: Jun 14, 2010
 *      Author: Kevin Black
 */

#ifndef DEBUGDEF_H_
#define DEBUGDEF_H_

#define FUN_BEGIN "<function begin>"
#define FUN_END "<function end>"

#define DEBUG
#ifdef DEBUG
	#include <iostream>
	//#define EnableDebugging(VALUE) bool debug_class = VALUE;
	#define LOG_DEBUG(STREAM_SEQ) if (DEBUG_CLASS) { LOG_DEBUG_LN(STREAM_SEQ) }
	// may optionally print to the simulation EV

	#define LOG_DEBUG_WHERE if (DEBUG_CLASS) { std::string file = __FILE__; int slash_pos = file.rfind("/") + 1; int dot_pos = file.find("."); \
		std::string classname = file.substr(slash_pos, dot_pos - slash_pos); \
		std::cout << classname << "::" << __FUNCTION__ << "::" << __LINE__ << " "; }

	#define LOG_DEBUG_APPEND(STREAM_SEQ) if (DEBUG_CLASS) { std::cout << STREAM_SEQ; }

	#define LOG_DEBUG_LN(STREAM_SEQ) if (DEBUG_CLASS) { LOG_DEBUG_WHERE LOG_DEBUG_APPEND(STREAM_SEQ<<std::endl) }

	#define LOG_DEBUG_FUN_BEGIN(STREAM_SEQ) LOG_DEBUG_LN(FUN_BEGIN<<" "<<STREAM_SEQ)
	#define LOG_DEBUG_FUN_END(STREAM_SEQ) LOG_DEBUG_LN(FUN_END<<" "<<STREAM_SEQ)
	#define PAUSE_DEBUG(STREAM_SEQ) LOG_DEBUG_WHERE LOG_DEBUG_APPEND(STREAM_SEQ) if (DEBUG_CLASS) { char dummy; cin >> dummy; }
	#define DEBUG_BLOCK(CODE) if (DEBUG_CLASS) { CODE; }
#else
	//#define EnableDebugging(VALUE)
	#define LOG_DEBUG(STREAM_SEQ)
	#define LOG_DEBUG_WHERE
	#define LOG_DEBUG_APPEND(STREAM_SEQ)
	#define LOG_DEBUG_LN(STREAM_SEQ)
	#define LOG_DEBUG_FUN_BEGIN
	#define LOG_DEBUG_FUN_END
	#define PAUSE_DEBUG(STREAM_SEQ)
	#define DEBUG_BLOCK(CODE)
#endif /* DEBUG */

#endif /* DEBUGDEF_H_ */
