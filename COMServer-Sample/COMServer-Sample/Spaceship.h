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
#include "..\\..\\IDL\\SpaceshipLocalServer_TypeInfo.h"

const int SPEED_LIMIT = 10000; //
const int DESTINATION_LEN_LIMIT = 50;

class Spaceship : public IStatus, public IEngine, public ICreateSpaceship
{
public:
	Spaceship();
	virtual ~Spaceship();

	//IUnknown
	HRESULT __stdcall QueryInterface(REFIID riid, void** pInterface);
	DWORD __stdcall AddRef();
	DWORD __stdcall Release();


	//IEngine
	//Handle lightspeed functionalities
	HRESULT __stdcall GoLightSpeed();
	HRESULT __stdcall GetLightSpeedState(boolean* pblightspeedState);

	//Handle normal engine state
	HRESULT __stdcall SpeedUp();
	HRESULT __stdcall SpeedDown();
	HRESULT __stdcall GetCurrentSpeed(int* currentSpeed);


	//IStatus
	HRESULT __stdcall ShowStatus();
	HRESULT __stdcall GetDestination(BSTR* destName);

	
	//ICreateSpaceship
	HRESULT __stdcall SetDestination(BSTR destName);
	HRESULT __stdcall SetMaximumSpeed(int maximumSpeed);

private:
	DWORD m_refCount;
	BSTR m_DestinationName;
	bool m_lightspeedState;
	int m_maximumSpeed;
	int m_currentSpeed;

};

