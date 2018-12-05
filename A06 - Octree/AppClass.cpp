#include "AppClass.h"
using namespace Simplex;
int timer = 0;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 0.0f, 100.0f), //Position
		vector3(0.0f, 0.0f, 99.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

#ifdef DEBUG
	uint uInstances = 80;
#else
	uint uInstances = 1849;
#endif
	int nSquare = static_cast<int>(std::sqrt(uInstances));
	m_uObjects = nSquare * nSquare;
	uint uIndex = -1;
	for (int i = 0; i < nSquare; i++)
	{
		for (int j = 1; j < nSquare+1; j++)
		{
			uIndex++;
			char name[7] = { 'p','l','a','t','e', j };//gives each plate a unique id
			m_pEntityMngr->AddEntity("Minecraft\\Plate.obj",name, true);
			std::cout << m_pEntityMngr->GetEntityCount() << "\n";
			vector3 v3Position;
			//dynamically places the plates 
			if(j + i * nSquare>30)
			v3Position = vector3(((j%10)-5)*3,4*3,0);
			else if (j+i*nSquare>20)
		    v3Position = vector3(((j % 10) - 5)*3, 3*3, 0);
			else if (j + i * nSquare>10)
		    v3Position = vector3(((j % 10) - 5)*3, 2*3, 0);
			else
		    v3Position = vector3(((j % 10) - 5)*3, 1*3, 0);

			matrix4 m4Position = glm::translate(v3Position);
			m_pEntityMngr->SetModelMatrix(m4Position);
		}
	}

	//makes the gun - needs to be repositioned but it work
	//m_pEntityMngr->AddEntity("Minecraft\\gun.obj", "gun", true);

	m_pEntityMngr->Update();


}
void Application::Update(void)
{
	timer++;
	
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	//update octant collision
	
	//Update Entity Manager
	m_pEntityMngr->Update();
	/*if (timer == 60)
	{
		m_pEntityMngr->AddEntity("Minecraft\\banzaibill.obj", "bullet0", false);
		
		m_pEntityMngr->SetModelMatrix(m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("bullet0"))->GetModelMatrix()*glm::translate(vector3(0,0,60))*glm::scale(IDENTITY_M4, glm::vec3(.5f, .5f, .5f)), m_pEntityMngr->GetEntityIndex("bullet0"));
		//scales bullet 
		m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("bullet0"))->velocity = vector3(0, 0, -1);
	}*/
	
	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	//display octree
	//m_pRoot->Display(C_YELLOW);
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui,
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release GUI
	ShutdownGUI();
}