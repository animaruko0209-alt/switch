#include <iostream>

enum class EnemyState
{
    Idle,
    Attacking,
    Defending,
    Fleeing
};

class Enemy
{
    EnemyState state;

    void Update()
    {
        switch (state)
        {
        case EnemyState::Idle:
            // Handle idle state
            break;
        case EnemyState::Attacking:
            // Handle attacking state
            break;
        case EnemyState::Defending:
            // Handle defending state
            break;
        case EnemyState::Fleeing:
            // Handle fleeing state
            break;
        default:
            // Handle unknown state
            break;
        }
	}

};


int main()
{
    std::cout << "Hello World!\n";
}
