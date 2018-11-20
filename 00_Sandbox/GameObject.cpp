#include "GameObject.h"

GameObject::GameObject(vector3 location)
{

	thisMesh = new MyMesh();
	Location = location;
	fSize = 5;
	movement = vector3(0);
	constVel = vector3(0);
	thisMesh->GenerateCube(fSize, C_RED);
	thisBody = new MyRigidBody({ GetMin(),GetMax() });
	MyMeshManager* MANAGER = MyMeshManager::GetInstance();
}

vector3 GameObject::GetMin()
{
	return (Location-fSize);
}

vector3 GameObject::GetMax()
{
	return(Location + fSize);;
}

void GameObject::Display()
{
	Simplex::matrix4 LOC = glm::translate(IDENTITY_M4, Location);

	MANAGER->AddMeshToRenderList(thisMesh, IDENTITY_M4);
}

void GameObject::Update()
{
	if(movement!=vector3(0))
	Location+=movement;//Add deltatime later - Love chris
	movement = vector3(0);
	movement += constVel;
	thisBody = new MyRigidBody({ GetMin(),GetMax() });
	
}

void GameObject::AddMovement(vector3 mov)
{
	movement += mov;
}

