#include "GameParticles.h" //GameParticles

//MoneyEmitter
MoneyEmitter::MoneyEmitter() : ParticleEmitter(1.5)
{
	for (int i = 0; i < NumParticles; i++)
	{
		ParticleEmitter::AddParticle(new Money{ "assets/images/particles/money.spt" });
	}
}

//SparkleEmitter
SparkleEmitter::SparkleEmitter() : ParticleEmitter(1.5)
{
	for (int i = 0; i < NumParticles; i++)
	{
		ParticleEmitter::AddParticle(new Sparkle{ "assets/images/particles/particle_sparkle.spt" });
	}
}

//DashEmitter
DashEmitter::DashEmitter() : ParticleEmitter(1.5)
{
	for (int i = 0; i < NumParticles; i++)
	{
		ParticleEmitter::AddParticle(new Dash{ "assets/images/particles/particle_sparkle.spt" });
	}
}