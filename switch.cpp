#include <iostream>
#include <conio.h>   // Windows: _kbhit, _getch
#include <random>
#include <chrono>
#include <thread>

enum class GameScene { StartUp, Title, MainMenu, InGame, Result };

const char* SceneName(GameScene s)
{
    switch (s)
    {
    case GameScene::StartUp:  return "StartUp";
    case GameScene::Title:    return "Title";
    case GameScene::MainMenu: return "MainMenu";
    case GameScene::InGame:   return "InGame";
    case GameScene::Result:   return "Result";
    default: return "Unknown";
    }
}

void cls() { std::system("cls"); }

int main()
{
    GameScene state = GameScene::StartUp;
    std::mt19937 rng(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, 10); // 1..10 のうち 1 が出れば終了（1/10）

    int inGameFrames = 0;
    bool quit = false;

    while (!quit)
    {
        switch (state)
        {
        case GameScene::StartUp:
            cls();
            std::cout << "=== StartUp ===\n初期化中...\n";
            // 必要ならここで初期化処理
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            state = GameScene::Title;
            break;

        case GameScene::Title:
            cls();
            std::cout << "=== Title ===\n";
            std::cout << "ゲームへようこそ。\n";
            std::cout << "AnyKey -> MainMenu\tEsc -> 終了\n";
            {
                int ch = _getch();
                if (ch == 27) quit = true;
                else state = GameScene::MainMenu;
            }
            break;

        case GameScene::MainMenu:
            cls();
            std::cout << "=== MainMenu ===\n";
            std::cout << "1: Start Game\n";
            std::cout << "Esc: 終了\n";
            {
                int ch = _getch();
                if (ch == '1')
                {
                    inGameFrames = 0;
                    state = GameScene::InGame;
                }
                else if (ch == 27) quit = true;
                // 他キーは無視してメニュー表示に戻る
            }
            break;

        case GameScene::InGame:
            // 自動進行する簡易ゲーム（フレームごとに 1/10 の確率で終了）
            cls();
            ++inGameFrames;
            std::cout << "=== InGame ===\n";
            std::cout << "フレーム: " << inGameFrames << "\n";
            std::cout << "進行中... (Escで終了, スペースで即 Result)\n";

            // 入力チェック（非ブロッキング)
            if (_kbhit())
            {
                int ch = _getch();
                if (ch == 27) { quit = true; break; }
                if (ch == ' ') { state = GameScene::Result; break; } // デバッグ用に即終了
            }

            // 1/10 の確率で Result に遷移
            if (dist(rng) == 1)
            {
                state = GameScene::Result;
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            break;

        case GameScene::Result:
            cls();
            std::cout << "=== Result ===\n";
            std::cout << "InGame を抜けるまでにかかったフレーム数: " << inGameFrames << "\n";
            std::cout << "Space -> Title\tEsc -> 終了\n";
            {
                int ch = _getch();
                if (ch == 27) quit = true;
                else if (ch == ' ') state = GameScene::Title;
                else state = GameScene::Title; // 他キーでもタイトルへ戻す
            }
            break;
        }
    }

    cls();
    std::cout << "終了しました\n";
    return 0;
}
