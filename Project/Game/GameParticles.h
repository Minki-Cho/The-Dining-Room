#pragma once
#include "../Engine/ParticleEmitter.h"
#include "GameObjectTypes.h"

class MoneyEmitter : public ParticleEmitter {
public:
    MoneyEmitter();
private:
    class Money : public ParticleEmitter::Particle {
    public:
        Money(std::string spriteFile) : ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Money Particle"; }
    };
    static constexpr int NumParticles = 30;
};

class SparkleEmitter : public ParticleEmitter {
public:
    SparkleEmitter();
private:
    class Sparkle : public ParticleEmitter::Particle {
    public:
        Sparkle(std::string spriteFile) : ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Sparkle Particle"; }
    };
    static constexpr int NumParticles = 30;
};

class DashEmitter : public ParticleEmitter {
public:
    DashEmitter();
private:
    class Dash : public ParticleEmitter::Particle {
    public:
        Dash(std::string spriteFile) : ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Dash Particle"; }
    };
    static constexpr int NumParticles = 7;
};