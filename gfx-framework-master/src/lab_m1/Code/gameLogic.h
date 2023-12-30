#pragma once

#include "components/simple_scene.h"
#include <vector>

using namespace std;

#define starsSpeedSeconds 1
#define noColor "white"

namespace m1
{
    class Lab3 : public gfxc::SimpleScene
    {
     public:
        Lab3();
        ~Lab3();

        void Init() override;
        class myGrid {
        public:
            Mesh* mesh;
            float x;
            float y;
            int side;
            std::string color = noColor;
            int cost = 0;
            float attackInterval = starsSpeedSeconds;
        };
        class myGame {
            public:
                int healthPoints;
                int stars;
                float timeStars;
                int randomTimeStars;
                float timeZombies;
                int randomTimeZombies;
                string rombColor = noColor;
                bool clicked;
            };
        class myEnemy {
            public:
                int healthPoints;
                float x;
                int y;
                char* color;
                int radius;
                bool dissapear = false;
                float scaleFactor = 1;
            };
        class myRectangle {
            public:
                Mesh* mesh;
                float x;
                float y;
                float width;
                float height;
            };

        class myStars {
            public:
                float x;
                float y;
                float radius;
                string color;
            };
        class myClick {
            public:
                int x;
                int y;
            };
        class myPlants {
            public:
                int x;
                int y;
                string color;
                bool dissapear = false;
                float scaleFactor = 1;
            };
     

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        
        glm::mat3 modelMatrix;
        float angularStep;
        myGrid GUIsquares[4];
        myGrid gridSquares[9];
        myRectangle dangerzone;
        myGame game;
        myGrid healthPoints[3];
        std::vector <myStars> randomStars;
        std::vector <myEnemy> zombies;
        std::vector <myPlants> plants;
        myClick click;
        std::vector <myStars> shootingStars;
    };
}   // namespace m1
