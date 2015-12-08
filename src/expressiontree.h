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
// class CPushCExpression
//
class CPushCExpression : public IExpression
{
public:// Constructors
	inline CPushCExpression(int nArgument = 0)
		: m_nArgument(nArgument),
		  m_nOffset(1)
	{}
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
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////

#endif // EXPRESSION_TREE_H