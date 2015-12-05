#ifndef EXPRESSION_H
#define EXPRESSION_H

////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#ifndef EXPRESSION_TREE_H
#	include "expressiontree.h"
#endif

#ifndef OPERATION_H
#	include "operation.h"
#endif

// STD Includes
#include <map>
#include <memory>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// class CExpressionBuilder
//
class CExpressionBuilder
{
public:// Constructors
	CExpressionBuilder(std::shared_ptr<CModule> pModule)
		: m_pModule(pModule)
	{
	}
	~CExpressionBuilder()
	{}

public:// Interface Methodes
	std::shared_ptr<IExpression> BuildExpression(int const nOffset)
	{
		EOpCode eOpCode = m_pModule->GetOpCode(nOffset);
		std::shared_ptr<IExpression> pExpression;
		IExpression* pExpr = nullptr;
		int nArgument = m_pModule->GetArgument(nOffset);

		switch (eOpCode)
		{
		case medusa::EOpCode::LABEL:
			break;
		case medusa::EOpCode::PUSHR:
			break;
		case medusa::EOpCode::PUSHC:
			pExpression = std::shared_ptr<IExpression>(new CPushCExpression(nArgument));
			break;
		case medusa::EOpCode::HALT:
			break;
		case medusa::EOpCode::JUMP:
			break;
		case medusa::EOpCode::JUMPZ:
			break;
		case medusa::EOpCode::JUMPI:
			break;
		case medusa::EOpCode::CALL:
			break;
		case medusa::EOpCode::ENTER:
			break;
		case medusa::EOpCode::MARK:
			break;
		case medusa::EOpCode::RETURN:
			break;
		case medusa::EOpCode::POP:
			break;
		case medusa::EOpCode::DUP:
			break;
		case medusa::EOpCode::SLIDE:
			break;
		case medusa::EOpCode::LOADC:
			break;
		case medusa::EOpCode::LOAD:
			break;
		case medusa::EOpCode::LOADA:
			break;
		case medusa::EOpCode::LOADR:
			break;
		case medusa::EOpCode::LOADRC:
			break;
		case medusa::EOpCode::STORE:
			break;
		case medusa::EOpCode::STOREA:
			break;
		case medusa::EOpCode::STORER:
			break;
		case medusa::EOpCode::ALLOC:
			break;
		case medusa::EOpCode::MALLOC:
			break;
		case medusa::EOpCode::NEW:
			break;
		case medusa::EOpCode::AND:
			break;
		case medusa::EOpCode::OR:
			break;
		case medusa::EOpCode::EQ:
			break;
		case medusa::EOpCode::NEQ:
			break;
		case medusa::EOpCode::GR:
			break;
		case medusa::EOpCode::GEQ:
			break;
		case medusa::EOpCode::LE:
			break;
		case medusa::EOpCode::LEQ:
			break;
		case medusa::EOpCode::ADD:
			pExpression = std::shared_ptr<IExpression>(new CAddExpression());
			break;
		case medusa::EOpCode::SUB:
			break;
		case medusa::EOpCode::MUL:
			break;
		case medusa::EOpCode::DIV:
			break;
		case medusa::EOpCode::NEG:
			break;
		case medusa::EOpCode::IN:
			break;
		case medusa::EOpCode::OUT:
			break;
		case medusa::EOpCode::NOP:
			break;
		default:
			break;
		}

		return pExpression;
	}

private:// Members
	std::shared_ptr<CModule> m_pModule;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CExpressionManager
//
class CExpressionManager
{
public:// Constructors
	CExpressionManager(std::shared_ptr<CModule> pModule)
		: m_pExpressionBuilder(new CExpressionBuilder(pModule))
	{}
	~CExpressionManager()
	{}

public:// Interface Methodes
	std::shared_ptr<IExpression> GetExpression(int const nOffset)
	{
		auto mapIterator = m_mapOffsetToExpression.find(nOffset);
		if (mapIterator == m_mapOffsetToExpression.end())
		{
			if (m_pExpressionBuilder != nullptr)
			{
				std::shared_ptr<IExpression> expression = m_pExpressionBuilder->BuildExpression(nOffset);
				m_mapOffsetToExpression.emplace(nOffset, expression);

				return expression;
			}
			// interrupt
		}
		else
		{
			return mapIterator->second;
		}
	}

private:// Members
	std::map< int, std::shared_ptr<IExpression> > m_mapOffsetToExpression;
	std::unique_ptr<CExpressionBuilder> m_pExpressionBuilder;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////

#endif // EXPRESSION_H