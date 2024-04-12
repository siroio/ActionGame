#include "CameraUtility.h"
#include <Components/Transform.h>
#include <Vector2.h>
#include <Vector3.h>

Vector3 CameraUtility::ConvertToCameraView(const Glib::WeakPtr<Glib::Transform>& camera, const Vector2& input)
{
    Vector3 direction = camera->Forward() * input.y;
    direction += camera->Right() * input.x;
    direction.y = 0;
    return direction.Normalized();
}
