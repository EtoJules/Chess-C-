#include "Window.h"
#include "Desk.h"
#include "Chess.h"
#include "ChangeSceneButton.h"
#include "ExitButton.h"
#include "DeskController.h"

int main()
{
    Engine::Scene mainMenuScene;
    Engine::Scene gameScene;

    ChangeSceneButton *newGameButton = new ChangeSceneButton("New Game");
    ChangeSceneButton *goToMenuButton = new ChangeSceneButton("Menu");
    ExitButton *exitButton = new ExitButton("Exit");

    Desk *desk = new Desk();
    std::vector<Chess*> chessArr;
    for (int i = 0; i < 32; ++i)
    {
        Chess *temp = new Chess(king, white);
        chessArr.push_back(temp);
    }
    
    DeskController *controller = new DeskController(desk, chessArr);

    newGameButton->setPosition(500, 100);
    goToMenuButton->setPosition(-1, -1);
    exitButton->setPosition(570, 400);

    mainMenuScene.addObject(newGameButton);
    mainMenuScene.addObject(exitButton);

    gameScene.addObject(goToMenuButton);
    gameScene.addObject(desk);
    gameScene.addObject(controller);
    
    for (int i = 0; i < chessArr.size(); ++i)
    {
        gameScene.addObject(chessArr.at(i));
    }
    
    goToMenuButton->setChangeToScene(mainMenuScene);
    newGameButton->setChangeToScene(gameScene);
    
    Engine::Window::get().switchScene(mainMenuScene);
    Engine::Window::get().startGameLoop();
    return 0;
}