#include "shadow_renderer.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

void ShadowRenderer::bind()
{	
	// Bind shader
	_shader.bind();

	// Shader uniforms
	_shader.uploadUniform("u_lightSpaceMatrix", _renderBus.getShadowMatrix());

	// Clipping (minY & maxY)
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	// Depth testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP_NV);
	glDepthFunc(GL_LEQUAL);
}

void ShadowRenderer::unbind()
{
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_CLAMP_NV);
	_shader.unbind();
}

void ShadowRenderer::render(const shared_ptr<ModelEntity> entity)
{
	if (entity->isVisible() && !entity->getRenderBuffers().empty())
	{
		// Face culling
		if (entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// Shader uniforms
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getTranslation().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_sampler_diffuseMap", 0);

		// Bind & render
		unsigned int index = 0;
		for (const auto& buffer : entity->getRenderBuffers())
		{
			// Model matrix
			_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix(index));

			// Diffuse map transparency
			if (entity->isTransparent() && entity->hasDiffuseMap())
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(index));
			}

			// Bind
			glBindVertexArray(buffer->getVAO());

			// Render
			if (buffer->isInstanced())
			{
				_shader.uploadUniform("u_isInstanced", true);
				glDrawArraysInstanced(GL_TRIANGLES, 0, buffer->getVertexCount(), buffer->getInstancedOffsetCount());
			}
			else
			{
				_shader.uploadUniform("u_isInstanced", false);
				glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());
			}

			index++;
		}

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);

		// Face culling
		if (entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}
	}
}

void ShadowRenderer::render(const shared_ptr<BillboardEntity> entity)
{
	if (entity->isVisible() && entity->isShadowed())
	{
		// Shader uniforms
		_shader.uploadUniform("u_isAlphaObject", entity->isTransparent());
		_shader.uploadUniform("u_currentY", entity->getTranslation().y);
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_sampler_diffuseMap", 0);

		// Model matrix
		_shader.uploadUniform("u_modelMatrix", entity->getModelMatrix());

		// Diffuse map transparency
		if (entity->isTransparent() && entity->hasDiffuseMap())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap());
		}

		// Bind
		glBindVertexArray(entity->getRenderBuffer()->getVAO());

		// Render
		_shader.uploadUniform("u_isInstanced", false);
		glDrawArrays(GL_TRIANGLES, 0, entity->getRenderBuffer()->getVertexCount());

		// Unbind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
}