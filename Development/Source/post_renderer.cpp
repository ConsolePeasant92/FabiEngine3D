#include "post_renderer.hpp"
#include "render_bus.hpp"

void PostRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Fragment shader uniforms
	_shader.uploadUniform("u_nearZ", _renderBus.getNearZ());
	_shader.uploadUniform("u_farZ", _renderBus.getFarZ());
	_shader.uploadUniform("u_isBloomEnabled", _renderBus.isBloomEnabled());
	_shader.uploadUniform("u_isDofEnabled", _renderBus.isDofEnabled());
	_shader.uploadUniform("u_isDofDynamic", _renderBus.isDofDynamic());
	_shader.uploadUniform("u_isLensFlareEnabled", _renderBus.isLensFlareEnabled());
	_shader.uploadUniform("u_dofMaxDistance", _renderBus.getDofMaxDistance());
	_shader.uploadUniform("u_dofBlurDistance", _renderBus.getDofBlurDistance());
	_shader.uploadUniform("u_lensFlareAlpha", _renderBus.getLensFlareAlpha());
	_shader.uploadUniform("u_lensFlareIntensity", _renderBus.getLensFlareIntensity());
	_shader.uploadUniform("u_flareSourcePositionClipspace", _renderBus.getFlareSourcePositionClipspace());
	_shader.uploadUniform("u_flareSourcePosition", _renderBus.getFlareSourcePosition());
	_shader.uploadUniform("u_cameraPosition", _renderBus.getCameraPosition());

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PostRenderer::unbind()
{
	glDisable(GL_BLEND);
	_shader.unbind();
}

void PostRenderer::render(const GuiEntity* entity)
{
	if (entity->isVisible())
	{
		// Shader uniforms
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());
		_shader.uploadUniform("u_mirrorHor", entity->isMirroredHorizonally());
		_shader.uploadUniform("u_mirrorVer", entity->isMirroredVertically());

		// Texture uniforms
		_shader.uploadUniform("u_sampler_scene", 0);
		_shader.uploadUniform("u_sampler_bloom", 1);
		_shader.uploadUniform("u_sampler_depth", 2);
		_shader.uploadUniform("u_sampler_blur", 3);
		_shader.uploadUniform("u_sampler_flare", 4);
		
		// Bind
		glBindVertexArray(entity->getOglBuffer()->getVAO());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getSceneMap());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getBloomMap());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getSceneDepthMap());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getBlurMap());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, _renderBus.getLensFlareMap());

		// Render
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}