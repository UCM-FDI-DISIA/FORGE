#pragma once
#ifndef FORGE_IMPORT_H_
#define FORGE_IMPORT_H_

/// <summary>
/// Macro que identifica las funciones que el juego querra importar en el motor
/// </summary>
#define FORGE_IMPORT extern "C" __declspec(dllexport)

#endif // !FORGE_IMPORT_H_