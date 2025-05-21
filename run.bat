setlocal
PATH=%PATH%;C:\winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2\mingw64\bin
C:\winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2\mingw64\bin\g++ ^
    -g -DSFML_STATIC levels/winScreen.cpp levels/HSR.cpp levels/mainMenu.cpp levels/levelSelect.cpp levels/bb10.cpp levels/death.cpp levels/settings.cpp levels/14-21.cpp classes/hammerPowerComp.cpp classes/hitByHammerComp.cpp classes/orbitComp.cpp classes/Definitions.cpp classes/soundManager.cpp classes/sfxComp.cpp classes/hammerComp.cpp classes/enemyDamageComp.cpp classes/spriteComp.cpp classes/sceneManager.cpp classes/platSpawnerManager.cpp classes/constantMoveComp.cpp classes/movingPlatComp.cpp classes/GD_Trn.cpp classes/enemyComp.cpp classes/ladderComp.cpp classes/playerMoveComp.cpp classes/physicsComp.cpp classes/GD_Component.cpp classes/Scene.cpp classes/objectPool.cpp classes/ObjectFactory.cpp classes/GD_ModularObject.cpp classes/GD_2DBlockObject.cpp classes/GD_GameObject.cpp main.cpp -o run.exe ^
    -I"C:\SFML-3.0.0\include" ^
    -L"C:\SFML-3.0.0\lib" -lopenal32 ^
    -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
run.exe