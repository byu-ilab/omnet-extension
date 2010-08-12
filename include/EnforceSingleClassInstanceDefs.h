/*
 * EnforceSingleClassInstanceDefs.h
 *
 *  Created on: Jul 15, 2010
 *      Author: Kevin Black
 *
 * @todo rename to SingletonDefs.h
 */

#ifndef ENFORCESINGLECLASSINSTANCEDEFS_H_
#define ENFORCESINGLECLASSINSTANCEDEFS_H_

#define Singleton_Declarations(CLASSNAME) \
private: \
	static CLASSNAME __instance; \
public: \
	static CLASSNAME * getInstance(); \
protected: \
	CLASSNAME(); \
	virtual ~CLASSNAME();

#define Singleton_Definitions(CLASSNAME) \
CLASSNAME CLASSNAME::__instance; \
CLASSNAME * CLASSNAME::getInstance() \
{ \
	return &__instance; \
}

#endif /* ENFORCESINGLECLASSINSTANCEDEFS_H_ */
