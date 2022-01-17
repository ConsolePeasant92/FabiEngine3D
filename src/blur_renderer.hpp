#pragma once

#include "base_renderer.hpp"
#include "quad_entity.hpp"
#include "capture_buffer.hpp"
#include "blur_direction.hpp"

class BlurRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::inject;

	void inject(shared_ptr<CaptureBuffer> captor);
	void bind();
	void unbind();

	const shared_ptr<TextureBuffer> blurTexture(const shared_ptr<Quad2dEntity> entity,
												shared_ptr<TextureBuffer> texture, unsigned int blurCount,
												float intensity, BlurDirection direction);

private:
	void _render(const shared_ptr<Quad2dEntity> entity, shared_ptr<TextureBuffer> texture);

	shared_ptr<CaptureBuffer> _captor = nullptr;
};