#include "TransformComponent.h"
#include <iostream>

TransformComponent::TransformComponent() {
	_name = "Transform";
}

void TransformComponent::Init(std::unordered_map<std::string, std::string>& param) {
	std::vector<std::string> aux = GetWords(param.at("posicion"));
	position.x = std::stof(aux[0]);
	position.y = std::stof(aux[1]);
	position.z = std::stof(aux[2]);
	aux.clear();

	aux = GetWords(param.at("escalaT"));
	scale.x = std::stof(aux[0]);
	scale.y = std::stof(aux[1]);
	scale.z = std::stof(aux[2]);

	aux.clear();
	aux = GetWords(param.at("rotacion"));
	rotation.x = std::stof(aux[0]);
	rotation.y = std::stof(aux[1]);
	rotation.z = std::stof(aux[2]);
	aux.clear();
}

//GETTERS
Ogre::Vector3* TransformComponent::GetPosition() { return &position; }
Ogre::Vector3* TransformComponent::GetRotation() { return &rotation; }
Ogre::Vector3* TransformComponent::GetScale() { return &scale; }

//SETTERS
void TransformComponent::SetPosition(Ogre::Vector3 v_) { position = v_; }
void TransformComponent::SetPosition(float x_, float y_, float z_) { position = Ogre::Vector3(x_, y_, z_); }

void TransformComponent::SetRotation(Ogre::Vector3 v_) { rotation = v_; }
void TransformComponent::SetRotation(float x_, float y_, float z_) { rotation = Ogre::Vector3(x_, y_, z_); }

void TransformComponent::SetScale(Ogre::Vector3 v_) { scale = v_; }
void TransformComponent::SetScale(float x_, float y_, float z_) { scale = Ogre::Vector3(x_, y_, z_); }