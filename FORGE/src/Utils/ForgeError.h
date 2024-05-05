#pragma once
#ifndef FORGE_ERROR_H_
#define FORGE_ERROR_H_

#ifdef _DEBUG
#include <iostream>
/// <summary>
/// Escribe un mensaje por la salida de errores
/// </summary>
/// <param name="message">Mensaje que se va a mostrar por la salida de errores</param>
#define reportError(message) std::cerr << "FORGE ERROR: " << message << "\n"
#else
#define reportError(message)
#endif
/// <summary>
/// Escribe un mensaje por la salida de errores y hace return de la funcion actual con el valor indicado
/// </summary>
/// <param name="value">Valor que se va a devolver desde la funcion actual</param>
/// <param name="message">Mensaje que se va a mostrar por la salida de errores</param>
#define throwError(value, message) reportError(message); return value

#endif //!FORGE_ERROR_H_