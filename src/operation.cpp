////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#include "operations.h"

// STD Includes
#include <vector>
#include <initializer_list>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class COperations
//

// Interface Methodes
void COperations::Init()
{
	std::initializer_list<std::string> strInitList = {
		"NOP",

		"HALT",

		"PUSHC",
		"PUSHA",
		"PUSHR",

		"POP",
		"POPA",
		"POPR",

		"DUP",
		"EXCH",

		"IN",
		"OUT",

		"LABEL",

		"JUMP",
		"JZ",
		"JNZ",

		"EQ",
		"NE",
		"GT",
		"GE",
		"LT",
		"LE",

		"NOT",
		"AND",
		"OR",

		"NEG",
		"ADD",
		"SUB",
		"MUL",
		"DIV",
		"MOD"
	};

	std::vector<std::string> arrString(strInitList);

	for (int i = 0; i < arrString.size(); ++i)
	{
		m_mapStringToOpCode.emplace(arrString[i], (ECode)i);
	}

}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////