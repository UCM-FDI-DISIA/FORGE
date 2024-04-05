#pragma once
#ifndef FORGE_EXPORTS_H_
#define FORGE_EXPORTS_H_

#ifdef _FORGE
#define FORGE_API __declspec(dllexport)
#else
#define FORGE_API __declspec(dllimport)
#endif

#endif // !FORGE_EXPORTS_H_