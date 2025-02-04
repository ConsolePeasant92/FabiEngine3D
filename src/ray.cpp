#include "ray.hpp"

Ray::Ray(const fvec3 & position, const fvec3 & direction)
	:
	_position(position),
	_direction(direction)
{

}

const fvec3 & Ray::getPosition() const
{
	return _position;
}

const fvec3 & Ray::getDirection() const
{
	return _direction;
}
