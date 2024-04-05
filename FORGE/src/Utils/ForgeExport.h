#pragma once
#ifndef FORGE_EXPORTS_H_
#define FORGE_EXPORTS_H_

#ifdef _FORGE
#define FORGE_API __declspec(dllexport)
#else
#define FORGE_API
#endif
#ifdef _FORGE
#define FORGE_API_VAR __declspec(dllexport)
#else
#define FORGE_API_VAR __declspec(dllimport)
#endif

#endif // !FORGE_EXPORTS_H_