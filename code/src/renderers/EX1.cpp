#include "EX1.h"

EX1::EX1(int width, int height) : Renderer(width, height)
{
    
}

void EX1::render(float dt)
{
    const GLfloat color[] = { (float)sin(ImGui::GetTime()), (float)cos(ImGui::GetTime()/2), 0.5f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, color);
}
