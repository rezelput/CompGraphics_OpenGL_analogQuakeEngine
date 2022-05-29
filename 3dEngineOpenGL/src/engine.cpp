#include <stdlib.h>

#include "engine.h"
#include "HiResTimer.h"
#include "camera.h"
#include "world.h"


void CEngine::CheckInput(float deltaTime)
{
	static float buttonDelta = 0.0f;

	int mouseDeltaX, mouseDeltaY;	// положение мышки

	// уменьшить количество времени до следующего возможного распознанного нажатия кнопки
	buttonDelta -= deltaTime;

	if (buttonDelta < 0.0f)
		buttonDelta = 0.0f;

	// обновит ьполучить последние движения мыши
	inputSystem->Update();

	//
	inputSystem->GetMouseMovement(mouseDeltaX, mouseDeltaY);
	OnMouseMove(mouseDeltaX, mouseDeltaY);

	if (inputSystem->KeyDown(SDLK_w))
		OnKeyDown(SDLK_UP);
	if (inputSystem->KeyDown(SDLK_s))
		OnKeyDown(SDLK_DOWN);
	if (inputSystem->KeyDown(SDLK_a))
		OnKeyDown(SDLK_LEFT);
	if (inputSystem->KeyDown(SDLK_d))
		OnKeyDown(SDLK_RIGHT);
	if (inputSystem->KeyDown(SDLK_f))
		OnKeyDown(SDLK_f);
	if (inputSystem->KeyDown(SDLK_g))
		OnKeyDown(SDLK_g);
	if (inputSystem->KeyDown(SDLK_PLUS))
		OnKeyDown(SDLK_PLUS);
	if (inputSystem->KeyDown(SDLK_MINUS))
		OnKeyDown(SDLK_MINUS);
	if (inputSystem->KeyDown(SDLK_ESCAPE))
		OnKeyDown(SDLK_ESCAPE);
	if (inputSystem->ButtonDown(SDL_BUTTON_LEFT))
	{
		if (buttonDelta == 0.0f)
		{
			OnMouseDownL(0,0);
			buttonDelta = 0.5f;
		}
	}
}


void CEngine::GameCycle(float deltaTime)
{
	CCamera *camera = OnGetCamera();	// get the camera
	CWorld *world = OnGetWorld();		// get the world

	if (useInput)
		CheckInput(deltaTime);

	// подгрузить фреймы opengl (clear, identity)
	OnPrepare();

	// подготовить объекты и выполнить столкновения
	world->Prepare();

	// перемещение и ориентирвоание камеры в пространстве
	camera->Animate(deltaTime);

	// так же объекты
	world->Animate(deltaTime);

	// прорисовка объектов
	world->Draw(camera);

	// 
	SwapBuffers();
}


int CEngine::EnterMessageLoop()
{
	//	Message loop
	SDL_Event event;
	timer = new CHiResTimer;

	timer->Init();

	for (;;)
	{	
		GameCycle(timer->GetElapsedSeconds(1));
		//timer->LockFPS(50);
		while (SDL_PollEvent(&event))
		{
			WndProcOGL(event);
		}
	}

	delete timer;

	return 0;
}
