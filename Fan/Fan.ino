#include "SceneManager.h"

SceneManager* sceneManager;

void setup() {

  sceneManager=new SceneManager();
  sceneManager->setup();

}

void loop()
{

  sceneManager->update();
  sceneManager->display();

}
 

