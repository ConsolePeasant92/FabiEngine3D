#pragma once

#include "base_renderer.hpp"
#include "sky_entity.hpp"

class SkyColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void render(const shared_ptr<Sky> entity);
};