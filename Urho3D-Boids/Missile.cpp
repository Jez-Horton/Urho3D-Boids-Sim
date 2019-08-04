#include "Missile.h"

Missile::Missile()
{
	//playerNode = nullptr;
	pRigidBody = nullptr;
	pCollisionShape = nullptr;

	timer = 0.0f;
	active = false;
}

Missile::~Missile()
{
}

void Missile::Initialise(ResourceCache * pRes, Scene * pScene, Node* camera)
{
	//Setting the missile Node
	ballisticNode = pScene->CreateChild("missile");
	ballisticNode->SetPosition(Vector3(0.0f, 10.0f, 50.0f));
	ballisticNode->SetRotation(Quaternion(0.0f, 180.0f, 0.0f));
	ballisticNode->SetScale(1.5f);
	//Assigning a model and texture mesh to the missile node 
	pObject = ballisticNode->CreateComponent<StaticModel>();
	pObject->SetModel(pRes->GetResource<Model>("Models/Torus.mdl"));
	pObject->SetMaterial(pRes->GetResource<Material>("Materials/Stone.xml"));
	pObject->SetCastShadows(true);
	//Adding in a collision and rigidbody into the missile
	pRigidBody = ballisticNode->CreateComponent<RigidBody>();
	pRigidBody->SetMass(1.0f);
	pRigidBody->SetUseGravity(false);
	pRigidBody->SetPosition(camera->GetPosition());
	pRigidBody->SetTrigger(true);

	pCollisionShape = ballisticNode->CreateComponent<CollisionShape>();
	pCollisionShape->SetBox(Vector3::ONE);

	pObject->SetEnabled(false);
}

void Missile::Update(Node* camera, Node* player)
{
	if (active)
	{
		pObject->SetEnabled(true);
		timer++;	
	}
	else
	{
		pRigidBody->SetPosition(player->GetPosition() + Vector3(player->GetDirection() * 3));
		pRigidBody->SetLinearVelocity(Vector3::ZERO);
		pObject->SetEnabled(false);
	}

	if (timer == 150)
	{
		active = false;
		pRigidBody->SetPosition(player->GetPosition() + Vector3(player->GetDirection() * 3));
		pRigidBody->SetLinearVelocity(Vector3::ZERO);
		pObject->SetEnabled(false);
		timer = 0; 
	}
}

void Missile::Shoot(Vector3 direction, Node * camera, Node* player)
{
	if (active)
	{
		pRigidBody->SetPosition(player->GetPosition() + Vector3(0.0f, 1.0f, 1.0f));
		pRigidBody->SetLinearVelocity(direction * 200.0f);
		timer++;
	}
	else
	{
		pRigidBody->SetPosition(camera->GetPosition());
		pRigidBody->SetLinearVelocity(Vector3::ZERO);
	}
}


