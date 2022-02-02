#include "aabb_entity_color_renderer.hpp"

using std::min;
using std::max;

void AabbEntityColorRenderer::bind()
{
	_shader->bind();

	_shader->uploadUniform("u_cameraView", _camera->getView());
	_shader->uploadUniform("u_cameraProjection", _camera->getProjection());
	_shader->uploadUniform("u_cameraPosition", _camera->getPosition());
	_shader->uploadUniform("u_minFogDistance", _renderStorage->getMinFogDistance());
	_shader->uploadUniform("u_maxFogDistance", _renderStorage->getMaxFogDistance());
	_shader->uploadUniform("u_fogThickness", _renderStorage->getFogThickness());
	_shader->uploadUniform("u_fogColor", _renderStorage->getFogColor());
	_shader->uploadUniform("u_isFogEnabled", _renderStorage->isFogEnabled());

	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_CLIP_DISTANCE1);
	glEnable(GL_CLIP_DISTANCE2);
	glEnable(GL_CLIP_DISTANCE3);
	glEnable(GL_CLIP_DISTANCE4);
	glEnable(GL_CLIP_DISTANCE5);
	glEnable(GL_DEPTH_TEST);
}

void AabbEntityColorRenderer::unbind()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CLIP_DISTANCE0);
	glDisable(GL_CLIP_DISTANCE1);
	glDisable(GL_CLIP_DISTANCE2);
	glDisable(GL_CLIP_DISTANCE3);
	glDisable(GL_CLIP_DISTANCE4);
	glDisable(GL_CLIP_DISTANCE5);

	_shader->unbind();
}

void AabbEntityColorRenderer::render(const shared_ptr<AabbEntity> entity)
{
	if(!entity->isVisible())
	{
		return;
	}

	_shader->uploadUniform("u_transformation", entity->getTransformation());
	_shader->uploadUniform("u_color", entity->getColor());
	_shader->uploadUniform("u_minX", _renderStorage->getMinPosition().x);
	_shader->uploadUniform("u_maxX", _renderStorage->getMaxPosition().x);
	_shader->uploadUniform("u_minY", _renderStorage->getMinPosition().y);
	_shader->uploadUniform("u_maxY", _renderStorage->getMaxPosition().y);
	_shader->uploadUniform("u_minZ", _renderStorage->getMinPosition().z);
	_shader->uploadUniform("u_maxZ", _renderStorage->getMaxPosition().z);

	glBindVertexArray(entity->getMesh()->getVaoId());

	glDrawArrays(GL_LINE_STRIP, 0, entity->getMesh()->getVertexCount());
	_renderStorage->increaseTriangleCount(entity->getMesh()->getVertexCount() / 3);

	glBindVertexArray(0);
}