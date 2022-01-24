#include "model_entity_shadow_renderer.hpp"
#include "render_bus.hpp"

void ModelEntityShadowRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_lightSpaceMatrix", _renderBus->getShadowMatrix());
	_shader->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void ModelEntityShadowRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);

	_shader->unbind();
}

void ModelEntityShadowRenderer::render(const shared_ptr<ModelEntity> entity)
{
	if(entity->isVisible() && entity->isShadowed())
	{
		_shader->uploadUniform("u_minHeight", entity->getMinHeight());
		_shader->uploadUniform("u_maxHeight", entity->getMaxHeight());
		_shader->uploadUniform("u_minTextureOpacity", MIN_TEXTURE_OPACITY);

		for(const auto& partId : entity->getPartIDs())
		{
			_shader->uploadUniform("u_transformationMatrix", entity->getTransformationMatrix(partId));
			_shader->uploadUniform("u_textureRepeat", entity->getTextureRepeat(partId));

			if(entity->isFaceCulled(partId))
			{
				glEnable(GL_CULL_FACE);
			}

			if(entity->hasDiffuseMap(partId))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, entity->getDiffuseMap(partId)->getId());
			}

			glBindVertexArray(entity->getMesh(partId)->getVaoID());

			glDrawArrays(GL_TRIANGLES, 0, entity->getMesh(partId)->getVertexCount());

			glBindVertexArray(0);

			if(entity->hasDiffuseMap(partId))
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if(entity->isFaceCulled(partId))
			{
				glDisable(GL_CULL_FACE);
			}
		}
	}
}