/*
 * EnforceSingleClassInstanceDefs.h
 *
 *  Created on: Jul 15, 2010
 *      Author: Kevin Black
 */

#ifndef ENFORCESINGLECLASSINSTANCEDEFS_H_
#define ENFORCESINGLECLASSINSTANCEDEFS_H_

#define Enforce_Single_Class_Instance_Declarations(CLASSNAME) \
private: \
	static CLASSNAME __instance; \
public: \
	static CLASSNAME * getInstance(); \
protected: \
	CLASSNAME(); \
	virtual ~CLASSNAME();

#define Enforce_Single_Class_Instance_Definitions(CLASSNAME) \
CLASSNAME CLASSNAME::__instance; \
CLASSNAME * CLASSNAME::getInstance() \
{ \
	return &__instance; \
}

#endif /* ENFORCESINGLECLASSINSTANCEDEFS_H_ */
