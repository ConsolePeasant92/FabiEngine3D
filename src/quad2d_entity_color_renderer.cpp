#include "quad2d_entity_color_renderer.hpp"
#include "configuration.hpp"
#include "text2d_entity.hpp"

void Quad2dEntityColorRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_diffuseMap", 0);

	glEnable(GL_BLEND);
}

void Quad2dEntityColorRenderer::unbind()
{
	glDisable(GL_BLEND);

	_shaderBuffer->unbind();
}

void Quad2dEntityColorRenderer::render(const shared_ptr<Quad2dEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	if(entity->isCentered())
	{
		if(((entity->getPosition().x - (entity->getSize().x * 0.5f)) > entity->getMaxPosition().x) ||
		   ((entity->getPosition().x + (entity->getSize().x * 0.5f)) < entity->getMinPosition().x) ||
		   ((entity->getPosition().y - (entity->getSize().y * 0.5f)) > entity->getMaxPosition().y) ||
		   ((entity->getPosition().y + (entity->getSize().y * 0.5f)) < entity->getMinPosition().y))
		{
			return;
		}
	}
	else
	{
		if((entity->getPosition().x > entity->getMaxPosition().x) ||
		   ((entity->getPosition().x + entity->getSize().x) < entity->getMinPosition().x) ||
		   (entity->getPosition().y > entity->getMaxPosition().y) ||
		   ((entity->getPosition().y + entity->getSize().y) < entity->getMinPosition().y))
		{
			return;
		}
	}

	_shaderBuffer->uploadUniform("u_uvMultiplier", entity->getUvMultiplier());
	_shaderBuffer->uploadUniform("u_uvOffset", entity->getUvOffset());
	_shaderBuffer->uploadUniform("u_transformation", entity->getTransformation());
	_shaderBuffer->uploadUniform("u_isHorizontallyFlipped", entity->isFlippedHorizonally());
	_shaderBuffer->uploadUniform("u_isVerticallyFlipped", entity->isVerticallyFlipped());
	_shaderBuffer->uploadUniform("u_color", entity->getColor());
	_shaderBuffer->uploadUniform("u_windowSize", fvec2(Config::getInst().getWindowSize()));
	_shaderBuffer->uploadUniform("u_minPosition", entity->getMinPosition());
	_shaderBuffer->uploadUniform("u_maxPosition", entity->getMaxPosition());
	_shaderBuffer->uploadUniform("u_opacity", entity->getOpacity());
	_shaderBuffer->uploadUniform("u_textureRepeat", static_cast<int>(entity->getTextureRepeat()));
	_shaderBuffer->uploadUniform("u_hasDiffuseMap", (entity->getDiffuseTextureBuffer() != nullptr));
	_shaderBuffer->uploadUniform("u_wireframeColor", entity->getWireframeColor());
	_shaderBuffer->uploadUniform("u_isWireframed", entity->isWireframed());

	if(entity->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity->getDiffuseTextureBuffer()->getId());
	}

	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());
	_renderStorage->increaseTriangleCount(entity->getVertexBuffer()->getVertexCount() / 3);

	glBindVertexArray(0);

	if(entity->getDiffuseTextureBuffer() != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}