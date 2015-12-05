#ifndef OPERATION_H
#define OPERATION_H

////////////////////////////////////////////////////////////////////////////////
//
// Includes
//

// STD Includes
#include <map>
#include <string>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////

enum class EOpCode : char
{
	LABEL,
	PUSHR,
	PUSHC,
	HALT,
	JUMP,
	JUMPZ,
	JUMPI,
	CALL,
	ENTER,
	MARK,
	RETURN,
	POP,
	DUP,
	SLIDE,
	LOADC,
	LOAD,
	LOADA,
	LOADR,
	LOADRC,
	STORE,
	STOREA,
	STORER,
	ALLOC,
	MALLOC,
	NEW,
	AND,
	OR,
	EQ,
	NEQ,
	GR,
	GEQ,
	LE,
	LEQ,
	ADD,
	SUB,
	MUL,
	DIV,
	NEG,
	IN,
	OUT,
	NOP
};

////////////////////////////////////////////////////////////////////////////////
//
// class COperation
//
class COperation
{
public:// Constructors
	COperation();
	~COperation();

public:// Interface Methodes
	void Init();

	std::string const& GetName(EOpCode eOpCode) const;
	EOpCode GetOpCode(std::string const& strOperation) const
	{
		return m_mapStringToCode.at(strOperation);
	}

private:// Members
	std::map<std::string, EOpCode> m_mapStringToCode;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////


#endif // OPERATION_H