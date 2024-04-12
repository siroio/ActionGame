#include "MainCamera.h"
#include <GameObject.h>
#include <GameObjectManager.h>
#include <Components/Camera.h>
#include <Components/AudioListener.h>

#include "../../Constant/GameObjectName.h"
#include "../../Component/Camera/CameraRotator.h"
#include "../../Component/Camera/CameraController.h"

using namespace Glib;

void MainCamera::Create(const Vector3& offset, const float distance)
{
    auto cameraParent = GameObjectManager::Instantiate("Camera Parent");
    auto cameraChild = GameObjectManager::Instantiate("Camera Child");
    auto camera = GameObjectManager::Instantiate(ObjectName::Camera);
    camera->AddComponent<AudioListener>();
    camera->Transform()->Parent(cameraChild->Transform());
    cameraChild->Transform()->Parent(cameraParent->Transform());
    camera->AddComponent<Camera>();
    cameraParent->AddComponent<CameraRotator>();
    CameraController::Parameter param{};
    param.Offset = offset;
    param.Distance = distance;
    auto controller = cameraParent->AddComponent<CameraController>(param);
}
