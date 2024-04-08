#pragma once
#ifndef FORGE_EXPORT_H_
#define FORGE_EXPORT_H_

#ifdef _FORGE
/// <summary>
/// Macro que marca las funciones exporta el motor
/// </summary>
#define FORGE_API __declspec(dllexport)
#else
/// <summary>
/// Macro que marca las funciones exporta el motor
/// </summary>
#define FORGE_API
#endif
#ifdef _FORGE
/// <summary>
/// Macro que marca las variables exporta el motor
/// </summary>
#define FORGE_API_VAR __declspec(dllexport)
#else
/// <summary>
/// Macro que marca las variables exporta el motor
/// </summary>
#define FORGE_API_VAR __declspec(dllimport)
#endif

#endif // !FORGE_EXPORT_H_