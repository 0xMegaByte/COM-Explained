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

#include <iostream>
#include "..\\..\\IDL\\SpaceshipLocalServer_TypeInfo.h"
#include "..\\..\\IDL\\SpaceshipLocalServer_TypeInfo_i.c"
#include "SpaceshipClassFactory.h"
#include "stdafx.h"
#include <comdef.h>

#define PRINT_AND_EXIT_HR( hr ) _com_error err(hr); \
 wprintf(L"failed!\nServer>> ERROR: %ls (0x%X)\n",err.ErrorMessage(),hr); return 0
#define PRINT_SUCESS printf("success!\n")

DWORD g_dwLocks;
int main()
{
	HRESULT hr = E_UNEXPECTED;
	DWORD dwRegId = NULL;

	PrintCOMServer();

	//Initiate COM object;
	printf("Server>> Spaceship local server initializing...");

	if (FAILED(hr = CoInitialize(NULL)))
	{
		PRINT_AND_EXIT_HR(hr);
	}
	else 
	{
		PRINT_SUCESS;
		ITypeLib* pTLib = NULL;
		
		//change path to the generate exe's TLB file location
		if (FAILED(hr = LoadTypeLibEx(L"C:\\COM-Sample\\COMServer-Sample.tlb", REGKIND_REGISTER, &pTLib)))
		{
			PRINT_AND_EXIT_HR(hr);
		}
		
		if(pTLib)
			pTLib->Release();
		

		printf("Server>> Registring CLSID_Spaceship classes...");

		SpaceshipClassFactory _SpaceshipClassFactory;
		if (FAILED(hr = CoRegisterClassObject(
			CLSID_SpaceShip,
			(IClassFactory*)&_SpaceshipClassFactory,
			CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &dwRegId)))
		{
			PRINT_AND_EXIT_HR(hr);
		}
		else
		{
			PRINT_SUCESS;
			printf("Server>> Ready to recieve remote calls!\n");
			MSG message;
			while (GetMessageW(&message, NULL, NULL, NULL))
			{
				TranslateMessage(&message);
				DispatchMessageW(&message);

			}

			if (FAILED(hr = CoRevokeClassObject(dwRegId)))
			{
				printf("Server>> Failed to revoke registered classes! (0x%X)\n", hr);
				return 0;
			}
		}

		CoUninitialize(); //Uninitialize COM library
	}
	printf("Server>> Closed.");
	return 0;
}
