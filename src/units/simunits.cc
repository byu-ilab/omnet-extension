/*
 * simunits.cc
 *
 *  Created on: Jul 2, 2010
 *      Author: Kevin Black
 */

#include "simunits.h"

ByteUnit determineByteUnit(unsigned long num_bytes, ByteUnitType type)
{
	if (type == unittype_base2)
	{
		if (num_bytes < kB_2_const)
		{
			return unit_B;
		}

		if (num_bytes < MB_2_const)
		{
			return unit_kB;
		}

		if (num_bytes < GB_2_const)
		{
			return unit_MB;
		}

		if (num_bytes < TB_2_const)
		{
			return unit_GB;
		}

		return unit_TB;
	}
	else if (type == unittype_base10)
	{
		if (num_bytes < kB_10_const)
		{
			return unit_B;
		}

		if (num_bytes < MB_10_const)
		{
			return unit_kB;
		}

		if (num_bytes < GB_10_const)
		{
			return unit_MB;
		}

		if (num_bytes < TB_10_const)
		{
			return unit_GB;
		}

		return unit_TB;
	}
	else if (type == unittype_bibyte)
	{
		if (num_bytes < KiB_const)
		{
			return unit_B;
		}
		else if (num_bytes < MiB_const)
		{
			return unit_KiB;
		}
		else if (num_bytes < GiB_const)
		{
			return unit_MiB;
		}
		else if (num_bytes < TiB_const)
		{
			return unit_GiB;
		}

		return unit_TiB;
	}
	return unit_B;
}

long getByteUnitConstant(unsigned long num_bytes, ByteUnitType type)
{
	return getByteUnitConstant(determineByteUnit(num_bytes, type), type);
}

long getByteUnitConstant(ByteUnit unit, ByteUnitType type)
{
	switch(unit)
	{
	case unit_B: return 1;
	case unit_kB:
		if (type == unittype_base2) { return kB_2_const; }
		else if (type == unittype_base10) { return kB_10_const; }
		break;
	case unit_KiB: return KiB_const;
	case unit_MB:
		if (type == unittype_base2) { return MB_2_const; }
		else if (type == unittype_base10) { return MB_10_const; }
		break;
	case unit_MiB: return MiB_const;
	case unit_GB:
		if (type == unittype_base2) { return GB_2_const; }
		else if (type == unittype_base10) { return GB_10_const; }
		break;
	case unit_GiB: return GiB_const;
	case unit_TB:
		if (type == unittype_base2) { return TB_2_const; }
		else if (type == unittype_base10) { return TB_10_const; }
		break;
	case unit_TiB: return TiB_const;
	default:
		break;
	}
	return 0;
}

double getMultiplicativeFactor(ByteUnit current_unit, ByteUnitType current_type,
		ByteUnit target_unit, ByteUnitType target_type)
{
	double current_unit_constant = (double) getByteUnitConstant(current_unit, current_type);
	double target_unit_constant = (double) getByteUnitConstant(target_unit, target_type);

	return current_unit_constant / target_unit_constant;
}

double getDivisibleFactor(ByteUnit current_unit, ByteUnitType current_type,
		ByteUnit target_unit, ByteUnitType target_type)
{
	double current_unit_constant = (double) getByteUnitConstant(current_unit, current_type);
	double target_unit_constant = (double) getByteUnitConstant(target_unit, target_type);

	return target_unit_constant / current_unit_constant;
}

std::string getByteUnitAsString(ByteUnit unit)
{
	switch(unit)
	{
	case unit_B: return "B";
	case unit_kB: return "kB";
	case unit_KiB: return "KiB";
	case unit_MB: return "MB";
	case unit_MiB: return "MiB";
	case unit_GB: return "GB";
	case unit_GiB: return "GiB";
	case unit_TB: return "TB";
	case unit_TiB: return "TiB";
	default:
		return "";
	}
}

std::string getByteUnitTypeAsString(ByteUnitType type)
{
	switch(type)
	{
	case unittype_base2: return "base 2";
	case unittype_base10: return "base 10";
	case unittype_bibyte: return "bi byte";
	default:
		return "";
	}
}
