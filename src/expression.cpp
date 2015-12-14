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
namespace expr {
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// class CExpressionBuilder
//
std::shared_ptr<IExpression> CExpressionBuilder::BuildExpression(int const nOffset)
{
	char* pChar = m_pModule->GetBuffer(nOffset);

	COperations::ECode eOpCode = (COperations::ECode) ((int)(*pChar));
	std::shared_ptr<IExpression> pExpression;

	switch (eOpCode)
	{
	case medusa::COperations::ECode::NOP:
		break;
	case medusa::COperations::ECode::HALT:
		pExpression = std::shared_ptr<IExpression>(new CHaltExpression());
		break;
	case medusa::COperations::ECode::PUSHC:
		pExpression = std::shared_ptr<IExpression>(new CPushCExpression(++pChar));
		break;
	case medusa::COperations::ECode::PUSHA:
		pExpression = std::shared_ptr<IExpression>(new CPushAExpression(++pChar));
		break;
	case medusa::COperations::ECode::PUSHR:
		pExpression = std::shared_ptr<IExpression>(new CPushRExpression(++pChar));
		break;
	case medusa::COperations::ECode::POP:
		pExpression = std::shared_ptr<IExpression>(new CPopExpression());
		break;
	case medusa::COperations::ECode::POPA:
		pExpression = std::shared_ptr<IExpression>(new CPopAExpression(++pChar));
		break;
	case medusa::COperations::ECode::POPR:
		pExpression = std::shared_ptr<IExpression>(new CPopRExpression(++pChar));
		break;
	case medusa::COperations::ECode::DUP:
		pExpression = std::shared_ptr<IExpression>(new CDupExpression());
		break;
	case medusa::COperations::ECode::EXCH:
		pExpression = std::shared_ptr<IExpression>(new CExchExpression());
		break;
	case medusa::COperations::ECode::IN:
		pExpression = std::shared_ptr<IExpression>(new CInExpression());
		break;
	case medusa::COperations::ECode::OUT:
		pExpression = std::shared_ptr<IExpression>(new COutExpression());
		break;
	case medusa::COperations::ECode::LABEL:
		break;
	case medusa::COperations::ECode::JUMP:
		pExpression = std::shared_ptr<IExpression>(new CJumpExpression(++pChar));
		break;
	case medusa::COperations::ECode::JZ:
		pExpression = std::shared_ptr<IExpression>(new CJZExpression(++pChar));
		break;
	case medusa::COperations::ECode::JNZ:
		pExpression = std::shared_ptr<IExpression>(new CJNZExpression(++pChar));
		break;
	case medusa::COperations::ECode::EQ:
		pExpression = std::shared_ptr<IExpression>(new CEQExpression());
		break;
	case medusa::COperations::ECode::NE:
		pExpression = std::shared_ptr<IExpression>(new CNEExpression());
		break;
	case medusa::COperations::ECode::GT:
		pExpression = std::shared_ptr<IExpression>(new CGTExpression());
		break;
	case medusa::COperations::ECode::GE:
		pExpression = std::shared_ptr<IExpression>(new CGEExpression());
		break;
	case medusa::COperations::ECode::LT:
		pExpression = std::shared_ptr<IExpression>(new CLTExpression());
		break;
	case medusa::COperations::ECode::LE:
		pExpression = std::shared_ptr<IExpression>(new CLEExpression());
		break;
	case medusa::COperations::ECode::NOT:
		pExpression = std::shared_ptr<IExpression>(new CNotExpression());
		break;
	case medusa::COperations::ECode::AND:
		pExpression = std::shared_ptr<IExpression>(new CAndExpression());
		break;
	case medusa::COperations::ECode::OR:
		pExpression = std::shared_ptr<IExpression>(new COrExpression());
		break;
	case medusa::COperations::ECode::NEG:
		pExpression = std::shared_ptr<IExpression>(new CNegExpression());
		break;
	case medusa::COperations::ECode::ADD:
		pExpression = std::shared_ptr<IExpression>(new CAddExpression());
		break;
	case medusa::COperations::ECode::SUB:
		pExpression = std::shared_ptr<IExpression>(new CSubExpression());
		break;
	case medusa::COperations::ECode::MUL:
		pExpression = std::shared_ptr<IExpression>(new CMulExpression());
		break;
	case medusa::COperations::ECode::DIV:
		pExpression = std::shared_ptr<IExpression>(new CDivExpression());
		break;
	case medusa::COperations::ECode::MOD:
		pExpression = std::shared_ptr<IExpression>(new CModExpression());
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
} // namespace expr
////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////
