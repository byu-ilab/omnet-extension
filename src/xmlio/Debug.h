//	Debug.h

#if !defined( DEBUG )
#define DEBUG(message) \
do {\
if (debug) cerr << message << endl;\
} while (false)

#endif
