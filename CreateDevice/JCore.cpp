#include "JCore.h"

bool JCore::CoreInit()
{
    return false;
}

bool JCore::CoreFrame()
{
    return false;
}

bool JCore::CoreRender()
{
    return false;
}

bool JCore::CoreRelease()
{
    return false;
}

bool JCore::Init()
{
    Init();
    return false;
}

bool JCore::Frame()
{
    Frame();
    return false;
}

bool JCore::Render()
{
    Render();
    return false;
}

bool JCore::Release()
{
    Release();
    return false;
}

bool JCore::GameRun()
{
    // 
    CoreInit();
    //
    while(WinRun())
    {
        CoreFrame();
        CoreRender();
    }
    CoreRelease();
    return true;
}
