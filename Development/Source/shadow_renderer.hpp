#pragma once

#include "base_renderer.hpp"
#include "model_entity.hpp"
#include "billboard_entity.hpp"

class ShadowRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::BaseRenderer;

	void bind()   override;
	void unbind() override;
	void render(const shared_ptr<ModelEntity> entity);
	void render(const shared_ptr<BillboardEntity> entity);
};