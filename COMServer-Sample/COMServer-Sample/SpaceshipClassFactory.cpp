/*
Copyright (C) 2022 Matan Shitrit (0xMegaByte)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include "SpaceshipClassFactory.h"
#include "Spaceship.h"

SpaceshipClassFactory::SpaceshipClassFactory() : m_refCount(0)
{
	//printf("\nSpaceshipClassFactory constractor called\n");
}

SpaceshipClassFactory::~SpaceshipClassFactory()
{
	//printf("SpaceshipClassFactory destractor called\n");
}

HRESULT __stdcall SpaceshipClassFactory::QueryInterface(REFIID riid, void** pInterface)
{
	if (riid == IID_IUnknown)
		*pInterface = (IUnknown*)this;
	else if (riid == IID_IClassFactory)
		*pInterface = (IClassFactory*)this;
	else
	{
		*pInterface = NULL;
		return E_NOINTERFACE;
	}
	((IUnknown*)(*pInterface))->AddRef();
	return S_OK;
}

DWORD __stdcall SpaceshipClassFactory::AddRef()
{
	return ++m_refCount;
}

DWORD __stdcall SpaceshipClassFactory::Release()
{
	if ( --m_refCount == 0 )
	{
		return 0;
	}

	return m_refCount;
}

HRESULT __stdcall SpaceshipClassFactory::LockServer(BOOL Lock)
{
	if (Lock)
		ServerLock();
	else
		ServerUnlock();

	return S_OK;
}

HRESULT __stdcall SpaceshipClassFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void** ppv)
{
	if (pUnkOuter)
		return CLASS_E_NOAGGREGATION;

	Spaceship* pSpaceShip = new Spaceship();
	if (!pSpaceShip)
		return E_OUTOFMEMORY;
		
	HRESULT hr = pSpaceShip->QueryInterface(riid, ppv);
	if (FAILED(hr))
		delete pSpaceShip;
	
	return hr;

}
