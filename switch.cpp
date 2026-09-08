#include <iostream>

enum class GameScene
{
    StartUp,
    Title,
    MainMenu,
    InGame,
    Result
};

class Enemy
{
    GameScene state;

    void Update()
    {
        switch (state)
        {
        case GameScene::StartUp:

            break;
        case GameScene::Title:

            break;
        case GameScene::MainMenu:

            break;
        case GameScene::InGame:

            break;
		case GameScene::Result:

			break;
        }
	}

};


int main()
{


}
