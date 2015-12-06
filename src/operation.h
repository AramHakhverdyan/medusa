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
	inline COperation();
	inline ~COperation() = default;

public:// Interface Methodes
	void Init();

	std::string const& GetName(EOpCode eOpCode) const;
	inline EOpCode GetOpCode(std::string const& strOperation) const;

private:// Members
	std::map<std::string, EOpCode> m_mapStringToCode;
};
////////////////////////////////////////////////////////////////////////////////

///////////////////////// Implementing inline methods //////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CContext
//

// Constructors
inline COperation::COperation()
	: m_mapStringToCode()
{
	Init();
}

// Interface Methodes
inline EOpCode COperation::GetOpCode(std::string const& strOperation) const
{
	auto mapIterator = m_mapStringToCode.find(strOperation);
	if (mapIterator == m_mapStringToCode.end())
		return EOpCode::NOP;

	return mapIterator->second;
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////


#endif // OPERATION_H