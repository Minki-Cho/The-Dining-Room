#include "Input.h"
#include "Engine.h"
#include "ImGuiHelper.h"

//InputKey
InputKey::InputKey(Keyboard button) : button(button) {};

bool InputKey::IsKeyDown() const
{
	return Engine::GetInput().IsKeyDown(button);
}

bool InputKey::IsKeyReleased() const
{
	return Engine::GetInput().IsKeyReleased(button);
}

InputKey::Keyboard SDLKeyToCS230Key(SDL_Keycode button)
{
	if (button == SDLK_RETURN)
	{
		return InputKey::Keyboard::Enter;
	}
	else if (button == SDLK_ESCAPE)
	{
		return InputKey::Keyboard::Escape;
	}
	else if (button == SDLK_SPACE)
	{
		return InputKey::Keyboard::Space;
	}
	else if (button == SDLK_BACKSPACE)
	{
		return InputKey::Keyboard::BackSpace;
	}
	else if (button == SDLK_LSHIFT || button == SDLK_RSHIFT)
	{
		return InputKey::Keyboard::Shift;
	}
	else if (button == SDLK_LEFT)
	{
		return InputKey::Keyboard::Left;
	}
	else if (button == SDLK_RIGHT)
	{
		return InputKey::Keyboard::Right;
	}
	else if (button == SDLK_UP)
	{
		return InputKey::Keyboard::Up;
	}
	else if (button == SDLK_DOWN)
	{
		return InputKey::Keyboard::Down;
	}
	else if (button >= SDLK_a && button <= SDLK_z)
	{
		int offset = static_cast<int>(button) - static_cast<int>(SDLK_a);
		return static_cast<InputKey::Keyboard>(static_cast<int>(InputKey::Keyboard::A) + offset);
	}
	return InputKey::Keyboard::None;

	
}

//Input
Input::Input()
{
	isKeyDownList.resize(static_cast<int>(InputKey::Keyboard::Count));
	wasKeyDownList.resize(static_cast<int>(InputKey::Keyboard::Count));
}

void Input::Update()
{
	wasKeyDownList = isKeyDownList;

	if (fullScreen)
		SDL_SetWindowFullscreen(Engine::GetWindow().GetWindowPtr(), SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		SDL_SetWindowFullscreen(Engine::GetWindow().GetWindowPtr(), 0);

	while (SDL_PollEvent(&event))
	{
		ImGuiHelper::FeedEvent(event);
		if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)) [[unlikely]]
		{
			isDone = true;
			//SDL_Quit();
		}
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
		{
			mousePos.x = static_cast<float>(event.motion.x);
			mousePos.y = static_cast<float>(event.motion.y);
		}
		break;
		case SDL_MOUSEBUTTONDOWN:
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				isMouseDown = true;
				break;
			}
			case SDL_BUTTON_RIGHT:
				break;
			}
		}
		break;
		case SDL_MOUSEBUTTONUP:
		{
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				isMouseUp = true;
				break;
			}
			case SDL_BUTTON_RIGHT:
				break;
			}
		}
		break;
		case SDL_KEYDOWN:
		{
			InputKey::Keyboard pressed = SDLKeyToCS230Key(event.key.keysym.sym);
			if (pressed != InputKey::Keyboard::None)
			{
				if (pressed != InputKey::Keyboard::Enter)
				{
					pause = false;
				}
				Engine::GetInput().SetKeyDown(pressed, true);
				Engine::GetLogger().LogDebug("on_key_pressed");
			}
			pause = false;
		}
		break;
		case SDL_KEYUP:
		{
			InputKey::Keyboard released = SDLKeyToCS230Key(event.key.keysym.sym);
			if (released != InputKey::Keyboard::None)
			{
				Engine::GetInput().SetKeyDown(released, false);
				Engine::GetLogger().LogDebug("on_key_released");
			}
		}
		break;
		case SDL_WINDOWEVENT:
		{
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			{
				pause = true;
				Engine::GetWindow().on_window_resized();
				break;
			}
			case SDL_WINDOWEVENT_MOVED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
			case SDL_WINDOWEVENT_HIDDEN:
			{
				pause = true;
				break;
			}
			default:
			{
				break;
			}
			}
		}
		}
	}

	if (isMouseDown == true && isMouseUp == true)
	{
		isMousePressed = true;
		isMouseDown = false;
		isMouseUp = false;
	}
	else
		isMousePressed = false;
}

bool Input::IsKeyDown(InputKey::Keyboard key) const
{
	return isKeyDownList[static_cast<int>(key)];
}

bool Input::IsKeyReleased(InputKey::Keyboard key) const
{
	if (!isKeyDownList[static_cast<int>(key)] && wasKeyDownList[static_cast<int>(key)])
	{
		return true;
	}
	return false;
}

void Input::SetKeyDown(InputKey::Keyboard key, bool value)
{
	isKeyDownList[static_cast<int>(key)] = value;
}
