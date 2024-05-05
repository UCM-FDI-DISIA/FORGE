@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

set INCLUDEDIR=.\include\
set INCLUDEVER=1.1
set INCLUDE=1

::Se compilan las dependencias
cd Dependencies
call BuildDependenciesWinVS.bat
cd ..

::Se compila el motor
msbuild FORGE.sln /t:Main /p:Configuration=Debug /p:Platform=x64
msbuild FORGE.sln /t:Main /p:Configuration=Release /p:Platform=x64

::Comprueba si la carpeta de includes existe y es la ultima version
if exist includever.forge (
    set /p CHKINCLUDEVER=<includever.forge
    if "!CHKINCLUDEVER!"=="%INCLUDEVER%" (
        set INCLUDE=0
    ) else (
        rmdir /q %INCLUDEDIR%
        echo %INCLUDEVER%>includever.forge
    )
) else (
    rmdir /q %INCLUDEDIR%
    echo %INCLUDEVER%>includever.forge
)
::Si no existia o no era la ultma version se crea la carpeta de include
if !INCLUDE! equ 1 (
    echo Creating FORGE include directory.
    cd Dependencies

    cd Lua\src
    set RELATIVEINCLUDEDIR=..\..\..\%INCLUDEDIR%
    xcopy /y "lua.hpp" "!RELATIVEINCLUDEDIR!"
    xcopy /y "lua.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "luaconf.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "lauxlib.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "lualib.h" "!RELATIVEINCLUDEDIR!"
    cd ..\..

    cd LuaBridge\Source\LuaBridge
    set RELATIVEINCLUDEDIR=..\..\..\..\%INCLUDEDIR%LuaBridge\
    xcopy /y "LuaBridge.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y /E ".\detail\" "!RELATIVEINCLUDEDIR!detail\"
    cd ..\..\..

    cd ..

    cd src
    set RELATIVEINCLUDEDIR=..\..\%INCLUDEDIR%

    cd .\Audio\
    xcopy /y "AudioListener.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "AudioSource.h" "!RELATIVEINCLUDEDIR!"
    cd ..

    cd EC
    xcopy /y "Component.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "ComponentData.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Entity.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Factory.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "ForgeFunction.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Scene.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "SceneManager.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Serializer.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Transform.h" "!RELATIVEINCLUDEDIR!"
    cd ..

    cd GUI
    xcopy /y "UIComponent.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Image.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Button.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Text.h" "!RELATIVEINCLUDEDIR!"
    cd ..

    cd Input
    xcopy /y "Input.h" "!RELATIVEINCLUDEDIR!"
    cd ..

    cd Load
    xcopy /y "LuaForge.h" "!RELATIVEINCLUDEDIR!"
    cd ..

    cd Main
    xcopy /y "MainForge.h" "!RELATIVEINCLUDEDIR!"
    cd ..

    cd Physics
    xcopy /y "Collider.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "RigidBody.h" "!RELATIVEINCLUDEDIR!"
    cd ..

    cd Render
    xcopy /y "Animator.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Billboard.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Camera.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Light.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Mesh.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "ParticleSystem.h" "!RELATIVEINCLUDEDIR!"
    cd ..

    cd Utils
    xcopy /y "ForgeError.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "ForgeExport.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "ForgeImport.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Quaternion.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Random.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "TimeForge.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Vector2.h" "!RELATIVEINCLUDEDIR!"
    xcopy /y "Vector3.h" "!RELATIVEINCLUDEDIR!"
    ::xcopy /y "Vector4.h" "!RELATIVEINCLUDEDIR!"
    cd ..

    cd ..
) else (
    echo Latest include directory version detected.
)