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

#pragma once
#include "stdafx.h"
#include "ServerLocks.h"


class SpaceshipClassFactory : public IClassFactory
{
public:
	SpaceshipClassFactory();
	virtual ~SpaceshipClassFactory();

	//IUnknown
	HRESULT __stdcall QueryInterface(REFIID riid, void** pInterface);
	DWORD __stdcall AddRef();
	DWORD __stdcall Release();

	// IClassFactory
	HRESULT __stdcall LockServer(BOOL Lock);
	HRESULT __stdcall CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void** ppv);

private:

	ULONG m_refCount;
};

