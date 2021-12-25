#pragma once

#include "base_renderer.hpp"
#include "image_entity.hpp"

class DofRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	void bind() override;
	void unbind() override;
	void render(const shared_ptr<ImageEntity> entity);
};