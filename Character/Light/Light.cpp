#include "Light.h"
#include <GameObject.h>
#include <GameObjectManager.h>
#include <Components/DirectionalLight.h>
#include <Vector3.h>
#include <Color.h>

#include "../../Constant/GameObjectName.h"

using namespace Glib;

GameObjectPtr Light::Spawn(const Vector3& euler, const Color& ambient, const Color& diffuse, const Color& specular)
{
    auto directionalLight = GameObjectManager::Instantiate(ObjectName::Light);
    auto light = directionalLight->AddComponent<DirectionalLight>();
    light->Ambient(ambient);
    light->Diffuse(diffuse);
    light->Specular(specular);
    light->GameObject()->Transform()->EulerAngles(euler);
    return directionalLight;
}
