#pragma once

enum class GameObjectType 
{
    Player,
    Wall,
    Guest,
    Food,
    WorkBenches,
    WorkBenchRange,
    Particle,
    Thief,
    Count,
};

enum class WorkBenchType
{
    Normal,
    PickUp,
    Counter,
    Table,
    TrashCan,
    Drinks,
    Fryer,
    Icecream,
};