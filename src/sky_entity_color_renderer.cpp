#include "sky_entity_color_renderer.hpp"

void SkyEntityColorRenderer::bind()
{
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_viewMatrix", Matrix44(Matrix33(_renderBus.getViewMatrix())));
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_mixValue", _renderBus.getSkyMixValue());
	_shader.uploadUniform("u_mainCubeMap", 0);
	_shader.uploadUniform("u_mixCubeMap", 1);

	// Enable depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void SkyEntityColorRenderer::unbind()
{
	// Disable depth
	glDisable(GL_DEPTH_TEST);

	// Unbind shader
	_shader.unbind();
}

void SkyEntityColorRenderer::render(const shared_ptr<SkyEntity> mainEntity, const shared_ptr<SkyEntity> mixEntity)
{
	if(mainEntity->isVisible())
	{
		// Enable wireframe
		if(mainEntity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		// Shader uniforms
		_shader.uploadUniform("u_isWireframed", (mainEntity->isWireframed() || _renderBus.isWireframeRenderingEnabled()));
		_shader.uploadUniform("u_rotationMatrix", mainEntity->getRotationMatrix());
		_shader.uploadUniform("u_mainLightness", mainEntity->getLightness());
		_shader.uploadUniform("u_mainColor", mainEntity->getColor());
		if(mixEntity != nullptr)
		{
			_shader.uploadUniform("u_mixLightness", mixEntity->getLightness());
			_shader.uploadUniform("u_mixColor", mixEntity->getColor());
		}

		// Bind textures
		if(mainEntity->hasCubeMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, mainEntity->getDiffuseMap());
		}
		if((mixEntity != nullptr) && mixEntity->hasCubeMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, mixEntity->getDiffuseMap());
		}

		// Bind buffer
		glBindVertexArray(mainEntity->getRenderBuffer()->getVAO());

		// Render buffer
		glDrawArrays(GL_TRIANGLES, 0, mainEntity->getRenderBuffer()->getVertexCount());
		_renderBus.increaseTriangleCount(mainEntity->getRenderBuffer()->getVertexCount() / 3);

		// Unbind buffer
		glBindVertexArray(0);

		// Unbind textures
		if(mainEntity->hasCubeMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
		if((mixEntity != nullptr) && mixEntity->hasCubeMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}

		// Disable wireframe
		if(mainEntity->isWireframed())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}