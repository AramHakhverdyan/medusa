////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#include "operation.h"

// STD Includes
#include <vector>
#include <initializer_list>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Implementation class COperation
//
medusa::COperation::COperation()
	: m_mapStringToCode()
{
	Init();
}

medusa::COperation::~COperation()
{}

void medusa::COperation::Init()
{
	std::initializer_list<std::string> strInitList = {
		"LABEL",
		"PUSHR",
		"PUSHC",
		"HALT",
		"JUMP",
		"JUMPZ",
		"JUMPI",
		"CALL",
		"ENTER",
		"MARK",
		"RETURN",
		"POP",
		"DUP",
		"SLIDE",
		"LOADC",
		"LOAD",
		"LOADA",
		"LOADR",
		"LOADRC",
		"STORE",
		"STOREA",
		"STORER",
		"ALLOC",
		"MALLOC",
		"NEW",
		"AND",
		"OR",
		"EQ",
		"NEQ",
		"GR",
		"GEQ",
		"LE",
		"LEQ",
		"ADD",
		"SUB",
		"MUL",
		"DIV",
		"NEG",
		"IN",
		"OUT",
		"NOP"
	};

	std::vector<std::string> arrString(strInitList);

	for (int i = 0; i < arrString.size(); ++i)
	{
		m_mapStringToCode.emplace(arrString[i], (EOpCode)i);
	}

}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////