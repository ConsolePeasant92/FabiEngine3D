#pragma once

#include "base_renderer.hpp"
#include "quad3d.hpp"

class Quad3dColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(shared_ptr<Quad3d> quad3d);
};