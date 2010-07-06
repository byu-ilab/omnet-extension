// Author: Kevin Black

#ifndef SIMUNITS_H_
#define SIMUNITS_H_

#include <math.h>
#include <string>
// units reasonably supported by a 64 bit integer

#define kB_2_const ((long) 1<<10)
#define MB_2_const ((long) 1<<20)
#define GB_2_const ((long) 1<<30)
#define TB_2_const ((long) 1<<40)

#define kB_10_const ((long) pow(10,3))
#define MB_10_const ((long) pow(10,6))
#define GB_10_const ((long) pow(10,9))
#define TB_10_const ((long) pow(10,12))

#define KiB_const ((long) 1<<10)
#define MiB_const ((long) 1<<20)
#define GiB_const ((long) 1<<30)
#define TiB_const ((long) 1<<40)

enum ByteUnitType { unittype_base2, unittype_base10, unittype_bibyte };
enum ByteUnit { unit_B, unit_kB, unit_KiB, unit_MB, unit_MiB, unit_GB, unit_GiB, unit_TB, unit_TiB };

ByteUnit determineByteUnit(unsigned long num_bytes, ByteUnitType type);

long getByteUnitConstant(unsigned long num_bytes, ByteUnitType type);

long getByteUnitConstant(ByteUnit unit, ByteUnitType type);

double getMultiplicativeFactor(ByteUnit current_unit, ByteUnitType current_type,
		ByteUnit target_unit, ByteUnitType target_type);

double getDivisibleFactor(ByteUnit current_unit, ByteUnitType current_type,
		ByteUnit target_unit, ByteUnitType target_type);

std::string getByteUnitAsString(ByteUnit unit);

std::string getByteUnitTypeAsString(ByteUnitType type);

#endif /* SIMUNITS_H_ */
