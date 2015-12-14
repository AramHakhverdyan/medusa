#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#ifndef CONTEXT_H
#	include "context.h"
#endif

// STD Includes
#include <iostream>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////
namespace expr {
////////////////////////////////////////////////////////////////////////////////																		


////////////////////////////////////////////////////////////////////////////////
//
// interface IExpression
//
class IExpression
{
public:// Constructors
	inline IExpression() = default;
	virtual ~IExpression() = default;

public:// Interface Methodes
	virtual int Eval(std::shared_ptr<CContext> pContext) = 0;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CHaltExpression
//
class CHaltExpression : public IExpression
{
public:// Constructors
	inline CHaltExpression() = default;
	inline ~CHaltExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		CInterrupt pInterrupt(CInterrupt::EndProcess, "END PROOCESS");
		throw(pInterrupt);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CPushCExpression
//
class CPushCExpression : public IExpression
{
public:// Constructors
	inline CPushCExpression(char const* pBuffer)
	{
		m_nArgument = *((int*) pBuffer);
	}
	inline ~CPushCExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		pStack->Push(m_nArgument);

		return 5;
	}

private:// Members
	int m_nArgument;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CPushAExpression
//
class CPushAExpression : public IExpression
{
public:// Constructors
	inline CPushAExpression(char const* pBuffer)
	{
		if (*pBuffer == 'I')
			m_eRegistr = ERegistr::IP;
		else if (*pBuffer == 'S')
			m_eRegistr = ERegistr::SP;
		else
			m_eRegistr = ERegistr::FP;

		m_nOffset = *((int*) (pBuffer + 2));
	}
	inline ~CPushAExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nRegistr = 0;
		switch (m_eRegistr)
		{
		case ERegistr::IP:
			nRegistr = pContext->IP();
			break;
		case ERegistr::SP:
			nRegistr = pContext->SP();
			break;
		case ERegistr::FP:
			nRegistr = pContext->FP();
			break;
		}

		int nArgument = (*pStack)[nRegistr + m_nOffset];
		pStack->Push(nArgument);

		return 7;
	}

private:// Native Types
	enum class ERegistr : char
	{
		IP,
		SP,
		FP
	};

private:// Members
	int m_nOffset;
	ERegistr m_eRegistr;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CPushRExpression
//
class CPushRExpression : public IExpression
{
public:// Constructors
	inline CPushRExpression(char const* pBuffer)
	{
		if (*pBuffer == 'I')
			m_eRegistr = ERegistr::IP;
		else if (*pBuffer == 'S')
			m_eRegistr = ERegistr::SP;
		else
			m_eRegistr = ERegistr::FP;
	}
	inline ~CPushRExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nRegistr = 0;
		switch (m_eRegistr)
		{
		case ERegistr::IP:
			nRegistr = pContext->IP();
			break;
		case ERegistr::SP:
			nRegistr = pContext->SP();
			break;
		case ERegistr::FP:
			nRegistr = pContext->FP();
			break;
		}

		int nArgument = (*pStack)[nRegistr];
		pStack->Push(nArgument);

		return 3;
	}

private:// Native Types
	enum class ERegistr : char
	{
		IP,
		SP,
		FP
	};

private:// Members
	ERegistr m_eRegistr;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CPopExpression
//
class CPopExpression : public IExpression
{
public:// Constructors
	inline CPopExpression() = default;
	inline ~CPopExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		pStack->Pop();

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CPopAExpression
//
class CPopAExpression : public IExpression
{
public:// Constructors
	inline CPopAExpression(char const* pBuffer)
	{
		if (*pBuffer == 'I')
			m_eRegistr = ERegistr::IP;
		else if (*pBuffer == 'S')
			m_eRegistr = ERegistr::SP;
		else
			m_eRegistr = ERegistr::FP;

		m_nOffset = *((int*) (pBuffer + 2));
	}
	inline ~CPopAExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nRegistr = 0;
		switch (m_eRegistr)
		{
		case ERegistr::IP:
			nRegistr = pContext->IP();
			break;
		case ERegistr::SP:
			nRegistr = pContext->SP();
			break;
		case ERegistr::FP:
			nRegistr = pContext->FP();
			break;
		}

		int nArgument = pStack->Pop();
		(*pStack)[nRegistr + m_nOffset] = nArgument;

		return 7;
	}

private:// Native Types
	enum class ERegistr : char
	{
		IP,
		SP,
		FP
	};

private:// Members
	int m_nOffset;
	ERegistr m_eRegistr;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CPopRExpression
//
class CPopRExpression : public IExpression
{
public:// Constructors
	inline CPopRExpression(char const* pBuffer)
	{
		if (*pBuffer == 'I')
			m_eRegistr = ERegistr::IP;
		else if (*pBuffer == 'S')
			m_eRegistr = ERegistr::SP;
		else
			m_eRegistr = ERegistr::FP;
	}
	inline ~CPopRExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nArgument = pStack->Pop();

		switch (m_eRegistr)
		{
		case ERegistr::IP:
			pContext->IP() = nArgument;
			break;
		case ERegistr::SP:
			pContext->SP() = nArgument;
			break;
		case ERegistr::FP:
			pContext->FP() = nArgument;
			break;
		}

		return 3;
	}

private:// Native Types
	enum class ERegistr : char
	{
		IP,
		SP,
		FP
	};

private:// Members
	ERegistr m_eRegistr;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CDupExpression
//
class CDupExpression : public IExpression
{
public:// Constructors
	inline CDupExpression() = default;
	inline ~CDupExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		pStack->Push(pStack->Top());

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CExchExpression
//
class CExchExpression : public IExpression
{
public:// Constructors
	inline CExchExpression() = default;
	inline ~CExchExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nTop1 = pStack->Pop();
		int nTop2 = pStack->Pop();

		pStack->Push(nTop1);
		pStack->Push(nTop2);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CInExpression
//
class CInExpression : public IExpression
{
public:// Constructors
	inline CInExpression() = default;
	inline ~CInExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		int nInValue = 0;
		std::shared_ptr<CStack> pStack = pContext->GetStack();

		std::cin >> nInValue;

		pStack->Push(nInValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class COutExpression
//
class COutExpression : public IExpression
{
public:// Constructors
	inline COutExpression() = default;
	inline ~COutExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		std::cout << std::endl << pStack->Top();

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CJumpExpression
//
class CJumpExpression : public IExpression
{
public:// Constructors
	inline CJumpExpression(char const* pBuffer)
		: m_nOffset(*((int*) pBuffer))
	{}
	inline ~CJumpExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nCurrIP = pContext->IP();
	
		return m_nOffset - nCurrIP;
	}

private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CJZExpression
//
class CJZExpression : public IExpression
{
public:// Constructors
	inline CJZExpression(char const* pBuffer)
		: m_nOffset(*((int*) pBuffer))
	{}
	inline ~CJZExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nCurrIP = pContext->IP();
		if (pStack->Top() == 0)
			return m_nOffset - nCurrIP;

		return 5;
	}

private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CJNZExpression
//
class CJNZExpression : public IExpression
{
public:// Constructors
	inline CJNZExpression(char const* pBuffer)
		: m_nOffset(*((int*) pBuffer))
	{}
	inline ~CJNZExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nCurrIP = pContext->IP();
		if (pStack->Top() != 0)
			return m_nOffset - nCurrIP;

		return 5;
	}

private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CEQExpression
//
class CEQExpression : public IExpression
{
public:// Constructors
	inline CEQExpression() = default;
	inline ~CEQExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue == nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CNEExpression
//
class CNEExpression : public IExpression
{
public:// Constructors
	inline CNEExpression() = default;
	inline ~CNEExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue != nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CGTExpression
//
class CGTExpression : public IExpression
{
public:// Constructors
	inline CGTExpression() = default;
	inline ~CGTExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue > nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CGEExpression
//
class CGEExpression : public IExpression
{
public:// Constructors
	inline CGEExpression() = default;
	inline ~CGEExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue >= nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CLTExpression
//
class CLTExpression : public IExpression
{
public:// Constructors
	inline CLTExpression() = default;
	inline ~CLTExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue < nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CLEExpression
//
class CLEExpression : public IExpression
{
public:// Constructors
	inline CLEExpression() = default;
	inline ~CLEExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue <= nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CNotExpression
//
class CNotExpression : public IExpression
{
public:// Constructors
	inline CNotExpression() = default;
	inline ~CNotExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nValue = pStack->Pop();
		pStack->Push(~nValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CAndExpression
//
class CAndExpression : public IExpression
{
public:// Constructors
	inline CAndExpression() = default;
	inline ~CAndExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue & nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class COrExpression
//
class COrExpression : public IExpression
{
public:// Constructors
	inline COrExpression() = default;
	inline ~COrExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue | nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CNegExpression
//
class CNegExpression : public IExpression
{
public:// Constructors
	inline CNegExpression() = default;
	inline ~CNegExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nValue = pStack->Pop();
		pStack->Push(-nValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CAddExpression
//
class CAddExpression : public IExpression
{
public:// Constructors
	inline CAddExpression() = default;
	inline ~CAddExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue + nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CSubExpression
//
class CSubExpression : public IExpression
{
public:// Constructors
	inline CSubExpression() = default;
	inline ~CSubExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue - nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CMulExpression
//
class CMulExpression : public IExpression
{
public:// Constructors
	inline CMulExpression() = default;
	inline ~CMulExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue * nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CDivExpression
//
class CDivExpression : public IExpression
{
public:// Constructors
	inline CDivExpression() = default;
	inline ~CDivExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue / nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CModExpression
//
class CModExpression : public IExpression
{
public:// Constructors
	inline CModExpression() = default;
	inline ~CModExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue % nRValue);

		return 1;
	}
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace expr
////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////

#endif // EXPRESSION_TREE_H