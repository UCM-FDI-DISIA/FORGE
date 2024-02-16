#pragma once
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <iostream>
#include <array>
#include <vector>
#include "../components/Component.h"
#include "../data/constants.h"

using namespace std;

class Entity {
protected:
	bool alive;
	Scene* gStt;
	grpId group;
	std::vector<Component*> currCmps;
	std::array<Component*, maxComponentId> cmps;
public:
	// Constructor
	Entity() : gStt(nullptr), cmps(), currCmps(), alive(true), group(grpId::_grp_GENERAL) {
		currCmps.reserve(maxComponentId);
	}
	// Destructor
	virtual ~Entity() { 
		for (auto cmp = currCmps.rbegin(); cmp != currCmps.rend(); ++cmp) {
			delete (*cmp);
			*cmp = nullptr;
		}

		for (Component* cpm : cmps) {
			cpm = nullptr;
		}
	}
	// Asigna el Manager del GameObject
	inline void setContext(Scene* _gStt, grpId _group) { gStt = _gStt; group = _group; }
	// Inicializa el GameObject tras tener el contexto
	virtual void initGameObject() {}
	// Devuelve si el GameObject est� vivo
	inline bool isAlive() { return alive; }
	// Asigna si el GameObject est� vivo o no
	inline void setAlive(bool _alive) { alive = _alive; }
	// A�ade el Component dicho al GameObject, devuelve un puntero a ese Component
	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&& ...args) {
		T* c = new T(std::forward<Ts>(args)...);
		removeComponent<T>();
		currCmps.push_back(c);
		cmps[T::id] = c;
		c->setContext(this, gStt);
		c->initComponent();
		return c;
	}
	// Elimina el Component dicho del GameObject
	template<typename T>
	inline void removeComponent() {
		constexpr cmpId_type cId = T::id;

		if (cmps[cId] != nullptr) {
			auto iter = std::find(currCmps.begin(),
				currCmps.end(),
				cmps[cId]);
			currCmps.erase(iter);
			delete cmps[cId];
			cmps[cId] = nullptr;
		}
	}
	// Devuelve el Compoment pedido del GameObject
	template<typename T>
	inline T* getComponent() {
		return static_cast<T*>(cmps[T::id]);
	}
	// Devuelve si el GameObject tiene el Component pedido
	template<typename T>
	inline bool hasComponent() {
		return cmps[T::id] != nullptr;
	}
	// Devuelve el grupo al que pertenece el gameObject
	inline grpId getGroup() {
		return group;
	}
	// Actualiza el GameObject
	virtual void update() {
		for (Component* cmp : currCmps) {
			cmp->update();
		}
	}
	// Dibuja el GameObject en pantalla
	virtual void render() const {
		for (Component* cmp : currCmps) {
			cmp->render();
		}
	}
	// Maneja los eventos del GameObject
	virtual void handleInput() {
		for (Component* cmp : currCmps) {
			cmp->handleInput();
		}
	}
};
#endif
