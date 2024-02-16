#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_
#include <SDL.h>
#include "ecs.h"
#include "../sdlutils/SDLUtils.h"

class Entity;
class Scene;

class Component {
protected:
	Entity* gObj;
	Scene* gStt;
public:
	// Constructora
	Component() : gObj(nullptr), gStt(nullptr) {}
	// Destructora
	virtual ~Component() {}
	// Asigna el GameObject y el Manager del Component
	inline void setContext(Entity* _gObj, Scene* _gStt) {
		gObj = _gObj;
		gStt = _gStt;
	}
	// Inicializa el Component si es necesario
	virtual void initComponent() {}
	// Actualiza el Component
	virtual void update() {}
	// Dibuja el Component en pantalla
	virtual void render() const {}
	// Maneja los eventos del Component
	virtual void handleInput() {}
};

#endif // !COMPONENT_H_
