#pragma once
#ifndef INVOKING_FORGE_H_
#define INVOKING_FORGE_H_

#include <list>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

/// <summary>
/// Fragua de invocacion
/// </summary>
class InvokingForge {
private:
	std::list<std::unordered_map<std::string, std::function<void()>>> invokerContainers;
	static std::unique_ptr<InvokingForge> instance;
	static bool initialised;
	/// <summary>
	/// Crea la instancia de la fragua de invocacion
	/// </summary>
	InvokingForge();
public:
	/// <summary>
	/// Inicializa la fragua de invocacion
	/// </summary>
	/// <returns>Booleano que indica si se ha podido iniciar</returns>
	static bool Init();
	/// <summary>
	/// Devuelve la instancia a la fragua de invocacion
	/// </summary>
	/// <returns>Puntero a la fragua de invocacion. nullptr si no se ha inicializado</returns>
	static InvokingForge* GetInstance();
	/// <summary>
	/// Elimina todos los invocadores de la fragua
	/// </summary>
	void shutDown();
	/// <summary>
	/// Registra un invocador en la fragua, se llama desde el constructor de Invoker
	/// </summary>
	/// <returns>Puntero al mapa de callbacks correspondiente a la nueva fragua</returns>
	std::unordered_map<std::string, std::function<void()>>& registerInvoker();
};

#endif // !INVOKING_FORGE_H_