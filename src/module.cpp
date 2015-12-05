////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#include "module.h"
#include "operation.h"

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
	std::ifstream inFile(strModulePath, std::ifstream::binary);
	std::filebuf* pFileBuf = inFile.rdbuf();

	int nSize = pFileBuf->pubseekoff(0, inFile.end, inFile.in);
	pFileBuf->pubseekpos(0, inFile.in);

	char* pBuffer = new (std::nothrow) char[nSize];
	pFileBuf->sgetn(pBuffer, nSize);

	inFile.close();
	std::cout.write(pBuffer, nSize);

	bool bFlag = false;
	std::string strIdent = "";
	COperation operation;
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
					EOpCode eOpCode = operation.GetOpCode(strIdent);
					m_arrOpCode.push_back(eOpCode);
					strIdent = "";

					int nArgument = 0;
					for (++i; i < nSize; ++i)
					{
						//if (pBuffer[i] == ' ' || pBuffer[i] == '\t')
						//{
						//	if (strIdent == "")
						//		continue;

						//	nArgument = std::stoi(strIdent);
						//	++i;
						//	break;
						//}

						if (pBuffer[i] == '\n' || pBuffer[i] == '\r')
						{
							++i;
							if (strIdent != "")
								nArgument = std::stoi(strIdent);

							break;
						}

						strIdent.push_back(pBuffer[i]);
					}

					m_arrArgument.push_back(nArgument);
				}
				// interrupt

				strIdent = "";
			}
		}
	}
	if (strIdent != "")
	{
		EOpCode eOpCode = operation.GetOpCode(strIdent);
		m_arrOpCode.push_back(eOpCode);

		m_arrArgument.push_back(0);
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