#pragma once
#include "Component.h"
class RigidBody;
class Move : public Component {
public:
	static const std::string id;	
	/// <summary>
	/// Constructora por defecto del component Move
	/// </summary>
	Move();
	/// <summary>
	/// Se llama en la creacion del componente Move
	/// </summary>
	/// <param name="data">Bloque con la informacion guardada para el componente</param>
	void initComponent(ComponentData* data) override;
	/// <summary>
	/// Actualiza la logica del componente, llamandose en cada iteracion del bucle principal
	/// </summary>
	void update() override;

	private:
		float movement = 10.0f;
		RigidBody* rb;

};