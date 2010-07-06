/*
 * DeleteSafeDefs.h
 *
 *  Created on: Jun 21, 2010
 *      Author: Kevin Black
 */

#ifndef DELETESAFEDEFS_H_
#define DELETESAFEDEFS_H_

#define deleteSafe(PNTR) if (PNTR) { delete PNTR; PNTR = NULL; }
#define deleteSafeArray(PNTR) if (PNTR) { delete [] PNTR; PNTR = NULL; }
#define cancelAndDeleteSafe(MSG_PNTR) if (MSG_PNTR) { cancelAndDelete(MSG_PNTR); MSG_PNTR = NULL; }
#define deleteSafeIf(PNTR, COND) if (COND) { deleteSafe(PNTR) }
#define deleteSafeArrayIf(PNTR, COND) if (COND) { deleteSafeArray(PNTR) }

#endif /* DELETESAFEDEFS_H_ */
