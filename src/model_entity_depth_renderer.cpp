#include "model_entity_depth_renderer.hpp"

void ModelEntityDepthRenderer::bind()
{
	_shader.bind();

	_shader.uploadUniform("u_viewMatrix", _renderBus.getViewMatrix());
	_shader.uploadUniform("u_projectionMatrix", _renderBus.getProjectionMatrix());
	_shader.uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void ModelEntityDepthRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);

	_shader.unbind();
}

void ModelEntityDepthRenderer::render(const shared_ptr<ModelEntity> entity, float clippingY, bool isUnderWater)
{
	if(entity->isVisible())
	{
		// Enable face culling
		if(entity->isFaceCulled())
		{
			glEnable(GL_CULL_FACE);
		}

		// Shader uniforms
		_shader.uploadUniform("u_minHeight", entity->getMinHeight());
		_shader.uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader.uploadUniform("u_clippingY", clippingY);
		_shader.uploadUniform("u_isUnderWater", isUnderWater);
		_shader.uploadUniform("u_viewMatrix", (entity->isFrozen() ? mat44(mat33(_renderBus.getViewMatrix())) : _renderBus.getViewMatrix()));
		_shader.uploadUniform("u_minTextureTransparency", MIN_TEXTURE_TRANSPARENCY);

		// Iterate through parts
		for(const auto& partID : entity->getPartIDs())
		{
			// Temporary values
			const auto buffer = entity->getRenderBuffer(partID);

			// Shader uniforms
			_shader.uploadUniform("u_transformationMatrix", entity->getTransformationMatrix(partID));

			// Bind textures
			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partID));
			}

			// Bind buffer
			glBindVertexArray(buffer->getVAO());

			// Render
			glDrawArrays(GL_TRIANGLES, 0, buffer->getVertexCount());

			// Unbind buffer
			glBindVertexArray(0);

			// Unbind textures
			if(entity->hasDiffuseMap(partID))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		// Disable face culling
		if(entity->isFaceCulled())
		{
			glDisable(GL_CULL_FACE);
		}
	}
}