#pragma once
#include <filesystem> //filepath
#include <vector> //vec2 variables
#include "GameObject.h" //GameObject inheritance
#include "Component.h" //Component inheritance
#include "vec2.h"
#include "vec3.h"

class ParticleEmitter : public Component
{
protected:
    class Particle : public GameObject
    {
    public:
        Particle(const std::filesystem::path& spriteFile);
        void Revive(vec2 positions, vec3 velocitys, double lifes);
        void Update(double dt) override;
        void Draw(mat3<float> matrix) override;
        bool IsAlive() { return life > 0; }
    private:
        double life;
    };
public:
    ParticleEmitter(double lifetime);
    virtual ~ParticleEmitter();
    void AddParticle(Particle* particleData);
    void Emit(int number, vec2 position, vec2 emitterVelocity, vec2 emitVector, float spread);
private:
    std::vector<Particle*> particleMemoryPool;
    int particleIndexToUse;
    double lifetime;

    float GetRandom(float min, float max);
};