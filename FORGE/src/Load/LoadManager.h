#pragma once
#ifndef LOAD_MANAGER_H_
#define LOAD_MANAGER_H_
#include <string>
class LuaForge;
class LoadManager {
private:
	LuaForge* luaForge;
public:
	/// <summary>
	/// Inicializa todas las cargas del motor
	/// </summary>
	/// <param name="assetsFile">Ruta del archivo en el que se indican los assets a cargar</param>
	/// <param name="scenesFile">Nombre del archivo de escenas dentro de Assets/scenes</param>
	LoadManager(std::string assetsFile, std::string scenesFile);
	/// <summary>
	/// Cierra las referencias a los archivos de carga
	/// </summary>
	~LoadManager();
};

#endif // !LOAD_MANAGER_H_