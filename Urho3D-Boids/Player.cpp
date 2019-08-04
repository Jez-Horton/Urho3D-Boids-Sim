#include "Player.h"
#include "Character.h"
Player::Player()
{
	pRigidBody = nullptr;
	pCollisionShape = nullptr;
	offset = Vector3(0.0f, -3.0f, 10.0f);
	score = 0;//Base score variable
	health = 100;//Base health variable
}

Player::~Player()
{

}

void Player::initialise(ResourceCache * pRes, Scene * pScene, Node* camera)
{
	///Player Nodes and setting the local position
	playerNode = pScene->CreateChild("Player");
	playerNode->SetPosition(Vector3(0.0f, 20.0f, 0.0f));
	playerNode->SetScale(1.5f);
	playerNode->SetRotation(Quaternion(0.0f, 0.0f, 150.0f));
	//Player Object creation, meshes and textures (using a bland Jack.xml texture as a placeholder same as a teapot)
	pObject = playerNode->CreateComponent<StaticModel>();
	pObject->SetModel(pRes->GetResource<Model>("Models/teapot.mdl"));
	pObject->SetMaterial(pRes->GetResource<Material>("Materials/Jack.xml"));
	pObject->SetCastShadows(true);
	///Creating the player collider and rigidbodies
	pRigidBody = playerNode->CreateComponent<RigidBody>();
	pRigidBody->SetMass(1.0f);
	pRigidBody->SetUseGravity(false);
	pRigidBody->SetPosition(Vector3(0.0f, 25.0f, -100.0f));
	pRigidBody->SetTrigger(true);
	pCollisionShape = playerNode->CreateComponent<CollisionShape>();
	pCollisionShape->SetBox(Vector3::ONE * 4, Vector3(0.0f, .5f, 0.0f));
	///Init the missile
	playerMissile.Initialise(pRes, pScene, camera);
}

void Player::update(Node* camera)
{
	pRigidBody->SetLinearFactor(Vector3::ZERO);
	pRigidBody->SetAngularFactor(Vector3::ZERO);

	playerMissile.Update(camera, playerNode);
}

void Player::shoot(Node* camera)
{
	playerMissile.Shoot(playerNode->GetDirection(), camera, playerNode);
}
