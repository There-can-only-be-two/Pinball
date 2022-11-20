#include <stdlib.h>
#include "Application.h"
#include "Globals.h"

#include "ModuleDebug.h"
#include <chrono>
using namespace std::chrono;
#include <thread>

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main(int argc, char ** argv)
{
	LOG("Starting game '%s'...", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;

	while (state != MAIN_EXIT)
	{
		high_resolution_clock::time_point startTime = high_resolution_clock::now();

		switch (state)
		{
		case MAIN_CREATION:

			LOG("-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;
		}

		//FPS CONTROL

		high_resolution_clock::time_point endTime = high_resolution_clock::now();
		App->debug->timePerCycle = duration_cast<microseconds>(endTime - startTime);

		//Frames per microseconds of the desiredFPS
		App->debug->desiredFPSmic = (int)((1.0f / (float)App->debug->desiredFPS) * 1E6);

		//Sleep if the time is less than the desiredFPSmic
		if (App->debug->timePerCycle < std::chrono::microseconds(App->debug->desiredFPSmic))
		{
			std::this_thread::sleep_for(std::chrono::microseconds(std::chrono::microseconds(App->debug->desiredFPSmic) - App->debug->timePerCycle));
		}

		//Calculate the time with the delay
		endTime = high_resolution_clock::now();
		App->debug->elapsedFrame = duration_cast<microseconds>(endTime - startTime);

	}

	delete App;
	LOG("Exiting game '%s'...\n", TITLE);
	return main_return;
}