#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Light.h"
#include "MonoBehaviour.h"
#include "ParticleSystem.h"
#include "Terrain.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Animator.h"
#include "Player.h"
#include "CameraScript.h"
#include "Enemy.h"
#include "StalkerEnemy.h"
#include "BruserEnemy.h"
#include "Font.h"
#include "Shop.h"
#include "Button.h"
#include "Gun.h"
#include "MainMenu.h"

GameObject::GameObject() : Object(OBJECT_TYPE::GAMEOBJECT)
{

}

GameObject::~GameObject()
{

}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Awake();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Start();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Update();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->LateUpdate();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->FinalUpdate();
	}
}

shared_ptr<Component> GameObject::GetFixedComponent(COMPONENT_TYPE type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);
	return _components[index];
}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::TRANSFORM);
	return static_pointer_cast<Transform>(component);
}

shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::MESH_RENDERER);
	return static_pointer_cast<MeshRenderer>(component);
}

shared_ptr<Camera> GameObject::GetCamera()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::CAMERA);
	return static_pointer_cast<Camera>(component);
}

shared_ptr<Light> GameObject::GetLight()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::LIGHT);
	return static_pointer_cast<Light>(component);
}

shared_ptr<ParticleSystem> GameObject::GetParticleSystem()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::PARTICLE_SYSTEM);
	return static_pointer_cast<ParticleSystem>(component);
}

shared_ptr<Terrain> GameObject::GetTerrain()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::TERRAIN);
	return static_pointer_cast<Terrain>(component);
}

shared_ptr<BaseCollider> GameObject::GetBaseCollider()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::BASECOLLIDER);
	return static_pointer_cast<BaseCollider>(component);
}

shared_ptr<BoxCollider> GameObject::GetBoxCollider()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::BOXCOLLIDER);
	return static_pointer_cast<BoxCollider>(component);
}

shared_ptr<SphereCollider> GameObject::GetSphereCollider()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::SPHERECOLLIDER);
	return static_pointer_cast<SphereCollider>(component);
}

shared_ptr<Animator> GameObject::GetAnimator()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::ANIMATOR);
	return static_pointer_cast<Animator>(component);
}

shared_ptr<Player> GameObject::GetPlayer()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::PLAYER);
	return static_pointer_cast<Player>(component);
}

shared_ptr<Bullet> GameObject::GetBullet()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::BULLET);
	return static_pointer_cast<Bullet>(component);
}

shared_ptr<Enemy> GameObject::GetEnemy()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::ENEMY);
	return static_pointer_cast<Enemy>(component);
}

shared_ptr<StalkerEnemy> GameObject::GetStalkerEnemy()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::STALKERENEMY);
	return static_pointer_cast<StalkerEnemy>(component);
}

shared_ptr<BruserEnemy> GameObject::GetBruserEnemy()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::BRUSERENEMY);
	return static_pointer_cast<BruserEnemy>(component);
}

shared_ptr<CameraScript> GameObject::GetCameraScript()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::CAMERASCRIPT);
	return static_pointer_cast<CameraScript>(component);
}

shared_ptr<Font> GameObject::GetFont()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::FONT);
	return static_pointer_cast<Font>(component);
}

shared_ptr<Shop> GameObject::GetShop()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::SHOP);
	return static_pointer_cast<Shop>(component);
}

shared_ptr<Button> GameObject::GetButton()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::BUTTON);
	return static_pointer_cast<Button>(component);
}

shared_ptr<Gun> GameObject::GetGun()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::GUN);
	return static_pointer_cast<Gun>(component);
}

shared_ptr<MuzzleFlash> GameObject::GetMuzzleFlash()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::MUZZLEFLASH);
	return static_pointer_cast<MuzzleFlash>(component);
}

shared_ptr<MainMenu> GameObject::GetMainMenu()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::MAINMENU);
	return static_pointer_cast<MainMenu>(component);
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
}