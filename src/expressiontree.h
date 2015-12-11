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

private:// Members

};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CHaltExpression
//
class CHaltExpression : public IExpression
{
public:// Constructors
	inline CHaltExpression()
		: m_nOffset(1)
	{}
	inline ~CHaltExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		CInterrupt pInterrupt(CInterrupt::EndProcess, "END PROOCESS");
		throw(pInterrupt);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CPushCExpression
//
class CPushCExpression : public IExpression
{
public:// Constructors
	inline CPushCExpression(int nArgument = 0)
		: m_nArgument(nArgument),
		m_nOffset(1)
	{}
	inline CPushCExpression(char* pBuffer)
	{
		m_nArgument = *((int*) pBuffer);
		m_nOffset = 5;
	}
	inline ~CPushCExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		pStack->Push(m_nArgument);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
	int m_nArgument;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CPopExpression
//
class CPopExpression : public IExpression
{
public:// Constructors
	inline CPopExpression()
		: m_nOffset(1)
	{}
	inline ~CPopExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		pStack->Pop();

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CDupExpression
//
class CDupExpression : public IExpression
{
public:// Constructors
	inline CDupExpression()
		: m_nOffset(1)
	{}
	inline ~CDupExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		pStack->Push(pStack->Top());

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CExchExpression
//
class CExchExpression : public IExpression
{
public:// Constructors
	inline CExchExpression()
		: m_nOffset(1)
	{}
	inline ~CExchExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nTop1 = pStack->Pop();
		int nTop2 = pStack->Pop();

		pStack->Push(nTop1);
		pStack->Push(nTop2);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CInExpression
//
class CInExpression : public IExpression
{
public:// Constructors
	inline CInExpression()
		: m_nOffset(1)
	{}
	inline ~CInExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		int nInValue = 0;
		std::shared_ptr<CStack> pStack = pContext->GetStack();

		std::cin >> nInValue;

		pStack->Push(nInValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class COutExpression
//
class COutExpression : public IExpression
{
public:// Constructors
	inline COutExpression()
		: m_nOffset(1)
	{}
	inline ~COutExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		std::cout << std::endl << pStack->Top();

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CJumpExpression
//
class CJumpExpression : public IExpression
{
public:// Constructors
	inline CJumpExpression(int nOffset)
		: m_nOffset(nOffset)
	{}
	inline CJumpExpression(char* pBuffer)
	{
		m_nOffset = *((int*) pBuffer);
	}
	inline ~CJumpExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nCurrIP = pContext->IP();
	
		return m_nOffset - nCurrIP;
	}

protected:// Helper Functions


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
	inline CJZExpression(int nOffset)
		: m_nOffset(nOffset)
	{}
	inline CJZExpression(char* pBuffer)
	{
		m_nOffset = *((int*) pBuffer);
	}
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

protected:// Helper Functions


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
	inline CJNZExpression(int nOffset)
		: m_nOffset(nOffset)
	{}
	inline CJNZExpression(char* pBuffer)
	{
		m_nOffset = *((int*) pBuffer);
	}
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

protected:// Helper Functions


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
	inline CEQExpression()
		: m_nOffset(1)
	{}
	inline ~CEQExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue == nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CNEExpression
//
class CNEExpression : public IExpression
{
public:// Constructors
	inline CNEExpression()
		: m_nOffset(1)
	{}
	inline ~CNEExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue != nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CGTExpression
//
class CGTExpression : public IExpression
{
public:// Constructors
	inline CGTExpression()
		: m_nOffset(1)
	{}
	inline ~CGTExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue > nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CGEExpression
//
class CGEExpression : public IExpression
{
public:// Constructors
	inline CGEExpression()
		: m_nOffset(1)
	{}
	inline ~CGEExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue >= nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CLTExpression
//
class CLTExpression : public IExpression
{
public:// Constructors
	inline CLTExpression()
		: m_nOffset(1)
	{}
	inline ~CLTExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue < nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CLEExpression
//
class CLEExpression : public IExpression
{
public:// Constructors
	inline CLEExpression()
		: m_nOffset(1)
	{}
	inline ~CLEExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue <= nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CNotExpression
//
class CNotExpression : public IExpression
{
public:// Constructors
	inline CNotExpression()
		: m_nOffset(1)
	{}
	inline ~CNotExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nValue = pStack->Pop();
		pStack->Push(~nValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CAndExpression
//
class CAndExpression : public IExpression
{
public:// Constructors
	inline CAndExpression()
		: m_nOffset(1)
	{}
	inline ~CAndExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue & nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class COrExpression
//
class COrExpression : public IExpression
{
public:// Constructors
	inline COrExpression()
		: m_nOffset(1)
	{}
	inline ~COrExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue | nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CNegExpression
//
class CNegExpression : public IExpression
{
public:// Constructors
	inline CNegExpression()
		: m_nOffset(1)
	{}
	inline ~CNegExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nValue = pStack->Pop();
		pStack->Push(-nValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CAddExpression
//
class CAddExpression : public IExpression
{
public:// Constructors
	inline CAddExpression()
		: m_nOffset(1)
	{}
	inline ~CAddExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue + nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CSubExpression
//
class CSubExpression : public IExpression
{
public:// Constructors
	inline CSubExpression()
		: m_nOffset(1)
	{}
	inline ~CSubExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue - nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CMulExpression
//
class CMulExpression : public IExpression
{
public:// Constructors
	inline CMulExpression()
		: m_nOffset(1)
	{}
	inline ~CMulExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue * nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CDivExpression
//
class CDivExpression : public IExpression
{
public:// Constructors
	inline CDivExpression()
		: m_nOffset(1)
	{}
	inline ~CDivExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue / nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CModExpression
//
class CModExpression : public IExpression
{
public:// Constructors
	inline CModExpression()
		: m_nOffset(1)
	{}
	inline ~CModExpression() = default;

public:// Interface Methodes
	int Eval(std::shared_ptr<CContext> pContext)
	{
		std::shared_ptr<CStack> pStack = pContext->GetStack();
		int nLValue = pStack->Pop();
		int nRValue = pStack->Pop();
		pStack->Push(nLValue % nRValue);

		return m_nOffset;
	}

protected:// Helper Functions


private:// Members
	int m_nOffset;
};
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////

#endif // EXPRESSION_TREE_H