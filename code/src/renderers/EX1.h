#pragma once
#include "Renderer.h"

class EX1 :
    public Renderer
{
    public:
        EX1(int width, int height);
        ~EX1();

protected:
    void render(float dt) override;
};

