#pragma once
#include "MyMesh.h"
#include "MyRigidBody.h"
#include "MyMeshManager.h"
using namespace Simplex;

class GameObject 
{
public:
	
	float fSize;
	MyMeshManager* MANAGER;
	vector3 Location;
	MyMesh * thisMesh;
	MyRigidBody * thisBody;
	GameObject::GameObject(vector3 location = vector3(0));
	vector3 GameObject::GetMin();
	vector3 GameObject::GetMax();
	void GameObject::Display();
	void GameObject::Update();
	void GameObject::AddMovement(vector3 mov);
	vector3 constVel;
private:
	vector3 movement;//our movements per frame
};
