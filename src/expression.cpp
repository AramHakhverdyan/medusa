////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#include "expression.h"

// STD Includes

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// class CExpression
//
std::shared_ptr<IExpression> CExpressionBuilder::BuildExpression(int const nOffset)
{
	COperations::ECode eOpCode = m_pModule->GetOpCode(nOffset);
	std::shared_ptr<IExpression> pExpression;
	IExpression* pExpr = nullptr;
	int nArgument = m_pModule->GetArgument(nOffset);

	switch (eOpCode)
	{
	case medusa::COperations::ECode::LABEL:
		break;
	case medusa::COperations::ECode::PUSHR:
		break;
	case medusa::COperations::ECode::PUSHC:
		pExpression = std::shared_ptr<IExpression>(new CPushCExpression(nArgument));
		break;
	case medusa::COperations::ECode::HALT:
		pExpression = std::shared_ptr<IExpression>(new CHaltExpression());
		break;
	case medusa::COperations::ECode::JUMP:
		break;
	case medusa::COperations::ECode::JUMPZ:
		break;
	case medusa::COperations::ECode::JUMPI:
		break;
	case medusa::COperations::ECode::CALL:
		break;
	case medusa::COperations::ECode::ENTER:
		break;
	case medusa::COperations::ECode::MARK:
		break;
	case medusa::COperations::ECode::RETURN:
		break;
	case medusa::COperations::ECode::POP:
		break;
	case medusa::COperations::ECode::DUP:
		break;
	case medusa::COperations::ECode::SLIDE:
		break;
	case medusa::COperations::ECode::LOADC:
		break;
	case medusa::COperations::ECode::LOAD:
		break;
	case medusa::COperations::ECode::LOADA:
		break;
	case medusa::COperations::ECode::LOADR:
		break;
	case medusa::COperations::ECode::LOADRC:
		break;
	case medusa::COperations::ECode::STORE:
		break;
	case medusa::COperations::ECode::STOREA:
		break;
	case medusa::COperations::ECode::STORER:
		break;
	case medusa::COperations::ECode::ALLOC:
		break;
	case medusa::COperations::ECode::MALLOC:
		break;
	case medusa::COperations::ECode::NEW:
		break;
	case medusa::COperations::ECode::AND:
		break;
	case medusa::COperations::ECode::OR:
		break;
	case medusa::COperations::ECode::EQ:
		break;
	case medusa::COperations::ECode::NEQ:
		break;
	case medusa::COperations::ECode::GR:
		break;
	case medusa::COperations::ECode::GEQ:
		break;
	case medusa::COperations::ECode::LE:
		break;
	case medusa::COperations::ECode::LEQ:
		break;
	case medusa::COperations::ECode::ADD:
		pExpression = std::shared_ptr<IExpression>(new CAddExpression());
		break;
	case medusa::COperations::ECode::SUB:
		break;
	case medusa::COperations::ECode::MUL:
		break;
	case medusa::COperations::ECode::DIV:
		break;
	case medusa::COperations::ECode::NEG:
		break;
	case medusa::COperations::ECode::IN:
		break;
	case medusa::COperations::ECode::OUT:
		pExpression = std::shared_ptr<IExpression>(new COutExpression());
		break;
	case medusa::COperations::ECode::NOP:
		break;
	default:
		break;
	}

	return pExpression;
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CExpressionManager
//

// Interface Methodes
std::shared_ptr<IExpression> CExpressionManager::GetExpression(int const nOffset)
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

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////
