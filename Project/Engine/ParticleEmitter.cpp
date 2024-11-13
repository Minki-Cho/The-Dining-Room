#include "ParticleEmitter.h" //ParticleEmitter
#include "Engine.h" //GetGSComponent, GetLogger
#include "GameObjectManager.h" //gameObjectManager

//ParticleEmitter
ParticleEmitter::ParticleEmitter(double lifetime) : lifetime(lifetime), particleIndexToUse(0) {}

ParticleEmitter::~ParticleEmitter()
{
	particleMemoryPool.clear();
}

void ParticleEmitter::AddParticle(Particle* particleData)
{
	particleMemoryPool.push_back(particleData);
	Engine::GetGameStateManager().GetGSComponent<GameObjectManager>()->Add(particleData);
}

void ParticleEmitter::Emit(int number, vec2 position, vec2 emitterVelocity, vec2 emitVector, float spread)
{
	for (int i = 0; i < number; i++)
	{
		if (particleMemoryPool[particleIndexToUse]->IsAlive() == true)
		{
			Engine::GetLogger().LogError("Overwriting a particle!");
		}
		emitVector *= GetRandom(0.8f, 1.2f);
		particleMemoryPool[particleIndexToUse]->Revive(position, mat3<float>::build_translation(emitterVelocity) * mat3<float>::build_rotation(GetRandom(-spread / 2, spread / 2)) * vec3 { emitVector.x, emitVector.y, 1.f }, lifetime);
		particleIndexToUse++;
	}
	if (particleIndexToUse >= particleMemoryPool.size())
		particleIndexToUse = 0;
}

//Particle
ParticleEmitter::Particle::Particle(const std::filesystem::path& spriteFile) : GameObject(vec2{}), life(0)
{
	AddGOComponent(new Sprite(spriteFile, this));
}

void ParticleEmitter::Particle::Revive(vec2 positions, vec3 velocitys, double lifes)
{
	SetPosition(positions);
	SetVelocity(vec2{ velocitys.x, velocitys.y });
	(*this).life = lifes;
	GetGOComponent<Sprite>()->PlayAnimation(0);
}

void ParticleEmitter::Particle::Update(double dt)
{
	if (IsAlive() == true)
	{
		life -= dt;
		GameObject::Update(dt);
	}
}

void ParticleEmitter::Particle::Draw(mat3<float> matrix)
{
	if (IsAlive() == true)
	{
		GetGOComponent<Sprite>()->Draw(GetMatrix() * matrix);
	}
}

float ParticleEmitter::GetRandom(float min, float max)
{
	return min + rand() / (RAND_MAX / (max - min));
}