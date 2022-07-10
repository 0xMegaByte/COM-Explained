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
#include "Utils.h"

#define PRINT_AND_EXIT_HR( hr ) _com_error err(hr); \
 wprintf(L"failed!\nClient>> ERROR: %ls (0x%X)\n",err.ErrorMessage(),hr); goto cleanup
#define PRINT_SUCESS printf("success!\n")

void PrintSpaceship(IStatus* pIStatus, IEngine* pIEngine)
{
	if (pIStatus && pIEngine)
	{
		BSTR	DefaultDest = NULL;
		boolean bLightspeedStatus;
		int		nCurrentSpeed = -1;

		printf("-------Spaceship Stats------\n");
		pIStatus->GetDestination(&DefaultDest);
		if (DefaultDest)
		{
			printf("\tDestination: %ls\n", DefaultDest);
			SysFreeString(DefaultDest);
		}
		pIEngine->GetCurrentSpeed(&nCurrentSpeed);
		printf("\tCurrent speed: %d\n", nCurrentSpeed);

		pIEngine->GetLightSpeedState(&bLightspeedStatus);
		printf("\tLightspeed state: %s\n", (bLightspeedStatus ? "active" : "not active"));
		printf("----------------------------\n");
	}
}

int main()
{
	HRESULT				hr = E_UNEXPECTED;
	BSTR				DestName = NULL;
	IClassFactory* pIClassFactory = NULL;
	ICreateSpaceship* pICreateSpaceship = NULL;
	IEngine* pIEngine = NULL;
	IStatus* pIStatus = NULL;
	int					nCurrentSpeed = -1;

	PrintCOMClient();

	printf("Client>> Spaceship client initilizing...");
	if (FAILED(hr = CoInitialize(NULL)))
	{
		PRINT_AND_EXIT_HR(hr);
	}
	else
	{
		PRINT_SUCESS;


		printf("Client>> Get spaceship class factory interface...");

		if (FAILED(hr = CoGetClassObject(CLSID_SpaceShip, CLSCTX_LOCAL_SERVER, NULL, IID_IClassFactory, (void**)&pIClassFactory)))
		{
			PRINT_AND_EXIT_HR(hr);
		}
		PRINT_SUCESS;

		printf("Client>> Create the spaceship object and get back the ICreateSpaceship interface...");

		if (FAILED(hr = pIClassFactory->CreateInstance(NULL, IID_ICreateSpaceship, (void**)&pICreateSpaceship)))
		{
			PRINT_AND_EXIT_HR(hr);
		}

		PRINT_SUCESS;
		//query IStatus and IEngine interfaces
		printf("Client>> Querying IStatus...");
		if (FAILED(hr = pICreateSpaceship->QueryInterface(IID_IStatus, (void**)&pIStatus)))
		{
			PRINT_AND_EXIT_HR(hr);
		}
		PRINT_SUCESS;
		printf("Client>> Querying IEngine...");
		if (FAILED(hr = pICreateSpaceship->QueryInterface(IID_IEngine, (void**)&pIEngine)))
		{
			PRINT_AND_EXIT_HR(hr);
		}

		if (pIStatus && pIEngine)
		{
			PRINT_SUCESS;

			PrintSpaceship(pIStatus, pIEngine);

#pragma Setting up spaceship values
			//Set spaceship destination
			printf("Client>> Setting up spaceship destination...");
			DestName = SysAllocString(OLESTR("Mars"));
			if (FAILED(hr = pICreateSpaceship->SetDestination(DestName)))
			{
				PRINT_AND_EXIT_HR(hr);
			}
			PRINT_SUCESS;
			if (DestName)
				SysFreeString(DestName);

			printf("Client>> Speeding up...");
			if (FAILED(hr = pIEngine->SpeedUp()))
			{
				PRINT_AND_EXIT_HR(hr);
			}
			PRINT_SUCESS;

			pIEngine->GetCurrentSpeed(&nCurrentSpeed);
			printf("Client>> Current speed: %d\n", nCurrentSpeed);
#pragma endregion

			PrintSpaceship(pIStatus, pIEngine);
			printf("Client>> Going lightspeed...");
			if (FAILED(hr = pIEngine->GoLightSpeed()))
			{
				PRINT_AND_EXIT_HR(hr);
			}
			PRINT_SUCESS;
			PrintSpaceship(pIStatus, pIEngine);
			goto cleanup;
		cleanup:
			{
				printf("Client>> Cleaning...");
				if (pIClassFactory)
					pIClassFactory->Release();
				if (pICreateSpaceship)
					pICreateSpaceship->Release();
				if (pIEngine)
					pIEngine->Release();
				if (pIStatus)
					pIStatus->Release();

				PRINT_SUCESS;
			}

			CoUninitialize();
		}
	}
}
