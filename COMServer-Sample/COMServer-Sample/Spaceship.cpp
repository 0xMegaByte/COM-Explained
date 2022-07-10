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

#include "Spaceship.h"
#include "ServerLocks.h"


Spaceship::Spaceship() : 
    m_refCount(0),
    m_currentSpeed(0),
    m_maximumSpeed(SPEED_LIMIT),
    m_lightspeedState(false)
{
    m_DestinationName = SysAllocString(L"Unknown");
    ServerLock();
    printf("Server>> Spaceship object constructed.\n");
}

Spaceship::~Spaceship()
{
    ServerUnlock();
    if (m_DestinationName)
        SysFreeString(m_DestinationName);

    printf("Server>> Spaceship object destructed.\n");
}

HRESULT __stdcall Spaceship::QueryInterface(REFIID riid, void** pInterface)
{
    if (riid == IID_IUnknown)
    {
        *pInterface = (IUnknown*)(IEngine*)this;
        printf("Server>> handed out IUnknown\n");

    }
    else if (riid == IID_IEngine)
    {
        *pInterface = (IEngine*)this;
        printf("Server>> handed out IEngine\n");
    }
    else if (riid == IID_IStatus)
    {
        *pInterface = (IStatus*)this;
        printf("Server>> handed out IStatus\n");
    }
    else if (riid == IID_ICreateSpaceship)
    {
        *pInterface = (ICreateSpaceship*)this;
        printf("Server>> handed out ICreateSpaceship\n");
    }
    else
    {
        *pInterface = NULL;
        return E_NOINTERFACE;
    }

    ((IUnknown*)*pInterface)->AddRef();
    return S_OK;
}

DWORD __stdcall Spaceship::AddRef()
{
    ++m_refCount;
    return m_refCount;
}

DWORD __stdcall Spaceship::Release()
{
    if (!--m_refCount)
    {
        delete this;
        return 0;
    }
    else
        return m_refCount;
}

HRESULT __stdcall Spaceship::GoLightSpeed()
{
    while (this->m_currentSpeed < this->m_maximumSpeed)
    {
        this->SpeedUp();
    }
    this->m_lightspeedState = true;

    return S_OK;
}

HRESULT __stdcall Spaceship::GetLightSpeedState(boolean* pblightspeedState)
{
    *pblightspeedState = this->m_lightspeedState;
    return S_OK;
}

HRESULT __stdcall Spaceship::SpeedUp()
{
    this->m_currentSpeed += 1000;

    return S_OK;
}

HRESULT __stdcall Spaceship::SpeedDown()
{
    this->m_currentSpeed -= 1000;

    return S_OK;
}

HRESULT __stdcall Spaceship::GetCurrentSpeed(int* currentSpeed)
{
    *currentSpeed = m_currentSpeed;
    return S_OK;
}

HRESULT __stdcall Spaceship::ShowStatus()
{
    printf("-------Spaceship Stats------\n");
    printf("\tDestination: %ls\n", this->m_DestinationName);
    printf("\tCurrent speed: %d\n", this->m_currentSpeed);
    printf("\tSpeed limit: %d\n", this->m_maximumSpeed);
    printf("\tLightspeed state: %s\n", (m_lightspeedState ? "active" : "not active"));
    printf("----------------------------\n");

    return S_OK;
}

HRESULT __stdcall Spaceship::GetDestination(BSTR* destName)
{
    *destName = SysAllocString(this->m_DestinationName);
    
    return S_OK;
}

HRESULT __stdcall Spaceship::SetDestination(BSTR destName)
{
    SysReAllocString(&m_DestinationName, destName);
    return S_OK;
}

HRESULT __stdcall Spaceship::SetMaximumSpeed(int maximumSpeed)
{
    if (maximumSpeed < SPEED_LIMIT)
        m_maximumSpeed = maximumSpeed;
    else
        return E_UNEXPECTED;
    return S_OK;
}
