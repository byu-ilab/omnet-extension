// Author: Kevin Black

#ifndef SIMUNITS_H_
#define SIMUNITS_H_

#include <math.h>
#include <string>
#include <omnetpp.h>
// units reasonably supported by a 64 bit integer

#define kB_2_const ((uint64) 1<<10)
#define MB_2_const ((uint64) 1<<20)
#define GB_2_const ((uint64) 1<<30)
#define TB_2_const ((uint64) 1<<40)

#define kB_10_const ((uint64) pow(10,3))
#define MB_10_const ((uint64) pow(10,6))
#define GB_10_const ((uint64) pow(10,9))
#define TB_10_const ((uint64) pow(10,12))

#define KiB_const ((uint64) 1<<10)
#define MiB_const ((uint64) 1<<20)
#define GiB_const ((uint64) 1<<30)
#define TiB_const ((uint64) 1<<40)

enum ByteUnitType { unittype_base2, unittype_base10, unittype_bibyte };
enum ByteUnit { unit_B, unit_kB, unit_KiB, unit_MB, unit_MiB, unit_GB, unit_GiB, unit_TB, unit_TiB };

ByteUnit determineByteUnit(uint64 num_bytes, ByteUnitType type);

uint64 getByteUnitConstant(uint64 num_bytes, ByteUnitType type);

uint64 getByteUnitConstant(ByteUnit unit, ByteUnitType type);

double getMultiplicativeFactor(ByteUnit current_unit, ByteUnitType current_type,
		ByteUnit target_unit, ByteUnitType target_type);

double getDivisibleFactor(ByteUnit current_unit, ByteUnitType current_type,
		ByteUnit target_unit, ByteUnitType target_type);

std::string getByteUnitAsString(ByteUnit unit);

std::string getByteUnitTypeAsString(ByteUnitType type);

#endif /* SIMUNITS_H_ */
