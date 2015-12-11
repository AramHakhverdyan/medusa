////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#include "module.h"
#include "parser.h"

// STD Includes
#include <fstream>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace medusa {
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// class CModule
//

// Constructors
CModule::CModule(std::string const& strModulePath)
{
	parser::CParser parser;
	m_pBuffer = parser.Parse(strModulePath);

	std::ifstream inFile(strModulePath, std::ifstream::binary);
	std::filebuf* pFileBuf = inFile.rdbuf();

	int nSize = pFileBuf->pubseekoff(0, inFile.end, inFile.in);
	pFileBuf->pubseekpos(0, inFile.in);

	char* pBuffer = new (std::nothrow) char[nSize];
	pFileBuf->sgetn(pBuffer, nSize);

	inFile.close();
	std::cout.write(pBuffer, nSize);

	bool bFlag = false;
	COperations operations;
	std::string strIdent = "";
	std::pair<COperations::ECode, int> pairOpCodeArgument(COperations::ECode::NOP, 0);
	for (int i = 0; i < nSize; ++i)
	{
		if (pBuffer[i] != ' ' && pBuffer[i] != '\n'
			&& pBuffer[i] != '\t' && pBuffer[i] != '\r'
			&& pBuffer[i] != ';')
		{
			strIdent.push_back(pBuffer[i]);
		}
		else
		{
			if (strIdent == "")
			{
				if (pBuffer[i] == ';')
				{
					while (pBuffer[i] != '\n')
						++i;
				}
			}
			else
			{
				if ((strIdent[0] < '0') || (strIdent[0] > '9'))
				{
					pairOpCodeArgument.first = operations.GetOpCode(strIdent);

					int nArgument = 0;
					std::string strArgument = "";
					for (++i; i < nSize; ++i)
					{
						if (pBuffer[i] == '\n' || pBuffer[i] == '\r')
						{
							if (strArgument != "")
								nArgument = std::stoi(strArgument);

							break;
						}

						strArgument.push_back(pBuffer[i]);
					}

					pairOpCodeArgument.second = nArgument;
				}
				// interrupt


				m_arrPairOpCodeArgument.push_back(pairOpCodeArgument);

				strIdent = "";
				pairOpCodeArgument.first = COperations::ECode::NOP;
				pairOpCodeArgument.second = 0;
			}
		}
	}
	if (strIdent != "")
	{
		pairOpCodeArgument.first = operations.GetOpCode(strIdent);
		pairOpCodeArgument.second = 0;

		m_arrPairOpCodeArgument.push_back(pairOpCodeArgument);
	}

	delete[] pBuffer;
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CModuleManager
//

// Interface Methodes
std::shared_ptr<CModule> CModuleManager::Load(std::string const& strModulePath)
{
	auto mapIterator = m_mapPathToModule.find(strModulePath);
	if (mapIterator == m_mapPathToModule.cend())
	{
		std::shared_ptr<CModule> pModule(new (std::nothrow) CModule(strModulePath));
		if (pModule == nullptr)
		{
			CInterrupt interrupt(CInterrupt::LoadModule, "Unable to create the module from the >> " + strModulePath);
			throw(interrupt);
		}

		m_mapPathToModule.emplace(strModulePath, pModule);

		return pModule;
	}

	if (mapIterator->second == nullptr)
		m_mapPathToModule.erase(mapIterator);

	return mapIterator->second;
}

// Helper Functions


////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
} // namespace medusa
////////////////////////////////////////////////////////////////////////////////