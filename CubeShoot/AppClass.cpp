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


	uint uInstances = 80;

	m_bFPC = true;

	int nSquare = static_cast<int>(std::sqrt(uInstances));
	m_uObjects = nSquare * nSquare;
	uint uIndex = -1;
	for (int i = 0; i < nSquare; i++)
	{
		for (int j = 1; j < nSquare+1; j++)
		{
			uIndex++;
			char name[7] = { 'p','l','a','t','e', j+48 };//gives each plate a unique id
			m_pEntityMngr->AddEntity("Minecraft\\Plate.obj",name, 0);
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

	//makes the gun - needs to be repositioned in update
	m_pEntityMngr->AddEntity("Minecraft\\gun.obj", "gun", 3);

	
	m_pEntityMngr->Update();


}
void Application::Update(void)
{
	

	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	
	//makes the gun appear in camera view 
	m_pEntityMngr->SetModelMatrix(m_pCameraMngr->GetCamera(m_pCameraMngr->GetActiveCamera())->GetCameraSpace()*glm::scale(IDENTITY_M4, glm::vec3(.5f, .5f, .5f)) * glm::translate(vector3(.3f, -1.f, -.9f))*glm::rotate((float)PI, vector3(0, 1, 0)), m_pEntityMngr->GetEntityIndex("gun"));


	//Update Entity Manager
	m_pEntityMngr->Update();
	
	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);

	//ends the game 
	if (m_pEntityMngr->endGame == true) 
	{
		m_bRunning = false;
	}
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
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