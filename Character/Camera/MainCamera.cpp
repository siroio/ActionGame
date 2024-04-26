#include "MainCamera.h"
#include <GameObject.h>
#include <GameObjectManager.h>
#include <Components/Camera.h>
#include <Components/AudioListener.h>

#include "../../Constant/GameObjectName.h"
#include "../../Component/Camera/CameraRotator.h"
#include "../../Component/Camera/CameraController.h"
#include "../../Component/Camera/CameraObstacleDetection.h"

using namespace Glib;

GameObjectPtr MainCamera::Spawn(const Vector3& offset, const float distance)
{
    auto cameraParent = GameObjectManager::Instantiate(ObjectName::Camera);
    auto cameraChild = GameObjectManager::Instantiate("Camera Child");
    auto camera = GameObjectManager::Instantiate("Camera");
    camera->AddComponent<AudioListener>();
    camera->Transform()->Parent(cameraChild->Transform());
    cameraChild->Transform()->Parent(cameraParent->Transform());
    camera->AddComponent<Camera>();
    cameraParent->AddComponent<CameraRotator>();
    //cameraParent->AddComponent<CameraObstacleDetection>();
    CameraController::Parameter param{};
    param.Offset = offset;
    param.Distance = distance;
    cameraParent->AddComponent<CameraController>(param);
    return cameraParent;
}
