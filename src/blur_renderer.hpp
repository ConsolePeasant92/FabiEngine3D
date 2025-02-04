#pragma once

#include "base_renderer.hpp"
#include "quad2d.hpp"
#include "capture_buffer.hpp"
#include "blur_direction_type.hpp"

class BlurRenderer final : public BaseRenderer
{
public:
	using BaseRenderer::inject;

	void inject(shared_ptr<CaptureBuffer> captureBuffer);
	void bind();
	void unbind();

	const shared_ptr<TextureBuffer> getBlurredTexture(shared_ptr<Quad2d> quad2d, shared_ptr<TextureBuffer> texture, int blurCount, float intensity, BlurDirectionType direction);

private:
	void _render(shared_ptr<Quad2d> quad2d, shared_ptr<TextureBuffer> texture);

	shared_ptr<CaptureBuffer> _captureBuffer = nullptr;
};