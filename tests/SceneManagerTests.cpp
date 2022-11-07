//
// Created by lucas on 7-11-2022.
//

#include <doctest.h>
#include "core/SceneManager.h"

TEST_CASE("SceneManger is able to add Scene"){
        SceneManager sceneManager = SceneManager();
        sceneManager.addScene(Scene());
        CHECK_EQ(1,sceneManager.getScenes().size());
}
