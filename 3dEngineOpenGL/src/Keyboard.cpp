#include "Keyboard.h"


//true
bool CKeyboard::KeyDown(SDLKey key)
{
  return m_keys[key];
}


//false
bool CKeyboard::KeyUp(SDLKey key)
{
  return !(m_keys[key]);
}


//�������� ���������
bool CKeyboard::Update()
{
  m_keys = SDL_GetKeyState(NULL);		
  return true;
}
