#include "lab_m1/Code/gameLogic.h"

#include <vector>
#include <iostream>

#include "lab_m1/Code/transform2D.h"
#include "lab_m1/Code/meshes.h"

using namespace std;
using namespace m1;

#define starSpawnLowest 2
#define starSpawnHighest 4
#define squareSide 100
#define dangerzoneWidth 30
#define rombSize (squareSide / 2.5)
#define healthSize (squareSide / 1.2)
#define shootingStarSize (squareSide / 6)
#define pointStarSize (squareSide / 10)
#define smallHexSize (squareSide / 5)
#define bigHexSize (squareSide / 3)
#define starPoinsRadius (squareSide / 5)
#define starRadius (squareSide / 4.5)
#define hexRadius (squareSide / 3)
#define starsTimeStart 2
#define starsTimeEnd 5
#define zombiesTimeStart 2
#define zombiesTimeEnd 5
#define rotation (-3)
#define zombiesSpeed 100
#define error 10
/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    angularStep = 0;

    //game--------------------------------------------------------
    game.healthPoints = 3;
    game.stars = 5;
    game.timeStars = 0.0;
    game.randomTimeStars = 0;
    game.timeZombies = 0.0;
    game.randomTimeZombies = 0;

    //background------------------------------------------------
    Mesh* background = object2D::CreateSquare("bg", corner, 10000, glm::vec3(0.2, 0.2, 0.2), true);
    AddMeshToList(background);

    //grid -----------------------------------
    int distance = squareSide * 3 / 2;
    for (int i = 0; i < 9; i++) {
        gridSquares[i].mesh = object2D::CreateSquare("square" + std::to_string(i), corner, squareSide, glm::vec3(0, 1, 0), true);
        AddMeshToList(gridSquares[i].mesh);
        gridSquares[i].x = 60 + distance * (i % 3);
        gridSquares[i].y = 20 + floor(i / 3) * distance;
        gridSquares[i].side = squareSide;
    }
    //dangerzone -----------------------------
    dangerzone.width = dangerzoneWidth;
    dangerzone.height = gridSquares[8].y + squareSide - 20;
    dangerzone.mesh = object2D::CreateRectangle("rectangle", corner, dangerzone.width, dangerzone.height, glm::vec3(1, 0, 0), true);
    dangerzone.x = 10;
    dangerzone.y = 20;
    AddMeshToList(dangerzone.mesh);

    //GUI squares -------------------------------
    for (int i = 0; i < 4; i++) {
        GUIsquares[i].mesh = object2D::CreateSquare("GUIsquare" + std::to_string(i), corner, squareSide, glm::vec3(0, 0, 0));
        AddMeshToList(GUIsquares[i].mesh);
        GUIsquares[i].x = 90 + (distance + 40) * (i % 4);
        GUIsquares[i].y = 550;
        GUIsquares[i].side = squareSide;
        GUIsquares[i].cost = i + 1;
        GUIsquares[2].cost = 2;
        GUIsquares[3].cost = 3;
        if (i == 0) {
            GUIsquares[i].color = "orange";
        }
        else if (i == 1) {
            GUIsquares[i].color = "blue";
        }
        else if (i == 2) {
            GUIsquares[i].color = "yellow";
        }
        else if (i == 3) {
            GUIsquares[i].color = "purple";
        }

    }
    //GUI rombs --------------------------------------
    Mesh* orangeRomb = object2D::CreateRomb("orangeRomb", corner, rombSize, glm::vec3(1, 0.6, 0.2), true);
    AddMeshToList(orangeRomb);

    Mesh* blueRomb = object2D::CreateRomb("blueRomb", corner, rombSize, glm::vec3(0, 0, 1), true);
    AddMeshToList(blueRomb);

    Mesh* yellowRomb = object2D::CreateRomb("yellowRomb", corner, rombSize, glm::vec3(1, 1, 0), true);
    AddMeshToList(yellowRomb);

    Mesh* purpleRomb = object2D::CreateRomb("purpleRomb", corner, rombSize, glm::vec3(0.8, 0, 0.9), true);
    AddMeshToList(purpleRomb);

    //GUI healthpoints ------------------------------------------
    for (int i = 0; i < game.healthPoints; i++) {
        healthPoints[i].side = healthSize;
        healthPoints[i].mesh = object2D::CreateSquare("healthPoints" + std::to_string(i), corner, healthPoints[i].side, glm::vec3(1, 0, 0), true);
        AddMeshToList(healthPoints[i].mesh);
        healthPoints[i].x = 100 + (healthPoints[i].side + 40) * (i % 3) + GUIsquares[3].x + squareSide;
        healthPoints[i].y = GUIsquares[i].y + squareSide / 4;
    }

    Mesh* star = object2D::CreateStar("grayStar", corner, pointStarSize, glm::vec3(0.8, 0.8, 0.8), true);
    AddMeshToList(star);

    Mesh* pointStar = object2D::CreatePinkStar("star", corner, pointStarSize, glm::vec3(0.7, 0.4, 0.9), true);
    AddMeshToList(pointStar);
    Mesh* orangeStar = object2D::CreatePinkStar("orangeStar", corner, shootingStarSize, glm::vec3(1, 0.6, 0.2), true);
    AddMeshToList(orangeStar);
    Mesh* blueStar = object2D::CreatePinkStar("blueStar", corner, shootingStarSize, glm::vec3(0, 0, 1), true);
    AddMeshToList(blueStar);
    Mesh* yellowStar = object2D::CreatePinkStar("yellowStar", corner, shootingStarSize, glm::vec3(1, 1, 0), true);
    AddMeshToList(yellowStar);
    Mesh* purpleStar = object2D::CreatePinkStar("purpleStar", corner, shootingStarSize, glm::vec3(0.8, 0, 0.9), true);
    AddMeshToList(purpleStar);

    Mesh* orangeHex = object2D::CreateHexagon("orangeHex", corner, bigHexSize, smallHexSize, glm::vec3(1, 0.6, 0.2), glm::vec3(0, 0.3, 0),true);
    AddMeshToList(orangeHex);

    Mesh* blueHex = object2D::CreateHexagon("blueHex", corner, bigHexSize, smallHexSize, glm::vec3(0, 0, 1), glm::vec3(0, 0.3, 0), true);
    AddMeshToList(blueHex);

    Mesh* yellowHex = object2D::CreateHexagon("yellowHex", corner, bigHexSize, smallHexSize, glm::vec3(1, 1, 0), glm::vec3(0, 0.3, 0), true);
    AddMeshToList(yellowHex);

    Mesh* purpleHex = object2D::CreateHexagon("purpleHex", corner, bigHexSize, smallHexSize, glm::vec3(0.8, 0, 0.9), glm::vec3(0, 0.3, 0), true);
    AddMeshToList(purpleHex);

}

bool intersects(int circleX, int circleRadius, int rectX, int rectWidth)
{
    if ((circleX - circleRadius <= rectX + rectWidth) && (circleX - circleRadius >= rectX + rectWidth - error))
        return true;
    return false;
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{
    

    //the grid -----------------------------------------------------------------------------------------
    glm::ivec2 resolution = window->GetResolution();
    int distance = squareSide * 3 / 2;
    for (int i = 0; i < 9; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(gridSquares[i].x, gridSquares[i].y);
        RenderMesh2D(meshes["square" + std::to_string(i)], shaders["VertexColor"], modelMatrix);
        
    }
    //the dangerzone ------------------------------------------------------------------------------------
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(dangerzone.x, dangerzone.y);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
    
    //GUI squares ---------------------------------------------------------------------
    
    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(GUIsquares[i].x, GUIsquares[i].y);
        RenderMesh2D(meshes["GUIsquare" + std::to_string(i)], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(GUIsquares[i].x + squareSide / 2, GUIsquares[i].y + squareSide/2);
        if (i == 0) {
            RenderMesh2D(meshes["orangeRomb"], shaders["VertexColor"], modelMatrix);
        } else if (i == 1) {
            RenderMesh2D(meshes["blueRomb"], shaders["VertexColor"], modelMatrix);
        }
        else if (i == 2) {
            RenderMesh2D(meshes["yellowRomb"], shaders["VertexColor"], modelMatrix);
        }
        else {
            RenderMesh2D(meshes["purpleRomb"], shaders["VertexColor"], modelMatrix);
        }
    }
    //healthpoints ----------------------------------------------------------------------
    for (int i = 0; i < game.healthPoints; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(healthPoints[i].x, healthPoints[i].y);
        RenderMesh2D(meshes["healthPoints" + std::to_string(i)], shaders["VertexColor"], modelMatrix);

    }


    //star costs-----------------------------
    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(GUIsquares[0].x + 7, GUIsquares[0].y - 25);
    RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < 2; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(GUIsquares[1].x + 7 + (i) * squareSide/2.5, GUIsquares[1].y - 25);
        RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(GUIsquares[2].x + 7 + (i)*squareSide / 2.5, GUIsquares[2].y - 25);
        RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(GUIsquares[3].x + 7 + (i)*squareSide / 2.5, GUIsquares[3].y - 25);
        RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);
    }

    ///my stars --------------------------------
    for (int i = 0; i < game.stars; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(healthPoints[0].x + 7 + (i % 9) * squareSide / 2.5, healthPoints[0].y - 25 - 30 * floor(i/9));
        RenderMesh2D(meshes["grayStar"], shaders["VertexColor"], modelMatrix);
    }


    //bg------------------
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0);
    RenderMesh2D(meshes["bg"], shaders["VertexColor"], modelMatrix);


    //star points --------------------------------------------
    game.timeStars += deltaTimeSeconds;
    if (game.randomTimeStars == 0) {
        game.randomTimeStars = starsTimeStart + (rand() % starsTimeEnd);
    }
    
    if (game.timeStars > game.randomTimeStars) {
        int numberOfStars = starSpawnLowest + rand() % starSpawnHighest;
        for (int i = 1; i < numberOfStars; i ++) {
            myStars newStar;
            newStar.x =  50+ (rand() % (1280 - 100));
            newStar.y = 50 + (rand() % (720 - 100));
            newStar.radius = starPoinsRadius;
            randomStars.push_back(newStar);
     
        }
        game.timeStars = 0.0;
        game.randomTimeStars = 0;
    }
    for (int i = 0; i < randomStars.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(randomStars.at(i).x, randomStars.at(i).y);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    }
    

    //zombies ------------------------------------------------------
    game.timeZombies += deltaTimeSeconds;
    if (game.randomTimeZombies == 0) {
        game.randomTimeZombies = zombiesTimeStart + (rand() % zombiesTimeEnd);
    }
    if (game.timeZombies > game.randomTimeZombies) {
        int column = rand() % 8;
        int color = rand() % 4;
        myEnemy zombie;
        zombie.healthPoints = 3;
        zombie.radius = hexRadius;
        zombie.y = gridSquares[column].y + squareSide / 2;
        zombie.x = 1280;
        if (color == 0) {
            zombie.color = "orange";
        }
        else if (color == 1) {
            zombie.color = "blue";
        }
        else if (color == 2) {
            zombie.color = "yellow";
        }
        else if (color == 3) {
            zombie.color = "purple";
        }
        game.timeZombies = 0.0;
        game.randomTimeZombies = 0;
        zombies.push_back(zombie);
        }
    for (int i = 0; i < zombies.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(zombies.at(i).x, zombies.at(i).y);
        if (zombies.at(i).dissapear == true) {
            modelMatrix *= transform2D::Scale(zombies.at(i).scaleFactor, zombies.at(i).scaleFactor);
            zombies.at(i).scaleFactor -= 2 * deltaTimeSeconds;
        }
        zombies.at(i).x -= zombiesSpeed * deltaTimeSeconds;
        string color = zombies.at(i).color;
        RenderMesh2D(meshes[color + "Hex"], shaders["VertexColor"], modelMatrix);
    }
    for (int i = 0; i < zombies.size(); i++) {
        if (zombies.at(i).scaleFactor <= 0) {
            zombies.erase(zombies.begin() + i);
            i--;
        }
    }


    //remove health -------------------------------------------------------------------
    for (int i = 0; i < zombies.size(); i++) {
        if (intersects(zombies.at(i).x, zombies.at(i).radius, dangerzone.x, dangerzone.width) == true) {
            zombies.erase(zombies.begin() + i);
            game.healthPoints--;
        }
    }

    //drag & drop ---------------------------------------------------------------------------
    if (game.clicked == true) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(click.x, click.y);
        string color = game.rombColor;
        RenderMesh2D(meshes[color + "Romb"], shaders["VertexColor"], modelMatrix);
    }
    
    //end the game -----------------------------------------------------
    if (game.healthPoints == 0) {
        cout << "You died! :(";
        exit(1);
    }
    
    //place plants -------------------------------------------------------
    
    for (int i = 0; i < plants.size(); i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(plants.at(i).x, plants.at(i).y);
        if (plants.at(i).dissapear == true) {
            modelMatrix *= transform2D::Scale(plants.at(i).scaleFactor, plants.at(i).scaleFactor);
            plants.at(i).scaleFactor -= 2 * deltaTimeSeconds;
        }
        string color = plants.at(i).color;
        RenderMesh2D(meshes[color + "Romb"], shaders["VertexColor"], modelMatrix);
    }
    for (int i = 0; i < plants.size(); i++) {
        if (plants.at(i).scaleFactor <= 0) {
            plants.erase(plants.begin() + i);
            i--;
        }
    }

    //shooting stars -------------------------------------------------------
    for (int i = 0; i < 9; i++) {
        if (gridSquares[i].color != noColor) {
            bool isEnemy = false;
            for (int j = 0; j < zombies.size(); j++) {
                if (zombies.at(j).color == gridSquares[i].color && (zombies.at(j).y == (gridSquares[i].y + squareSide/2)) && zombies.at(j).x >= gridSquares[i].x) {
                    isEnemy = true;
                }
            }
            if (gridSquares[i].attackInterval >= starsSpeedSeconds && isEnemy == true) {
                gridSquares[i].attackInterval = 0.0;
                myStars newStar;
                newStar.color = gridSquares[i].color;
                newStar.x = gridSquares[i].x + squareSide;
                newStar.y = gridSquares[i].y + squareSide / 2;
                newStar.radius = starRadius;
                shootingStars.push_back(newStar);

            }
            gridSquares[i].attackInterval += deltaTimeSeconds;
        }
    }
    for (int i = 0; i < shootingStars.size(); i++) {
        modelMatrix = glm::mat3(1);
       // ----------------------------------------
        modelMatrix *= transform2D::Translate(shootingStars.at(i).x, shootingStars.at(i).y);
        modelMatrix *= transform2D::Rotate(angularStep);
        shootingStars.at(i).x += 200 * deltaTimeSeconds;
        string color = shootingStars.at(i).color;
        RenderMesh2D(meshes[color + "Star"], shaders["VertexColor"], modelMatrix);
    }
    angularStep -= 5 * deltaTimeSeconds;

    //kill zombies ---------------------------------------------------------------------
    for (int i = 0; i < shootingStars.size(); i++) {
        for (int j = 0; j < zombies.size(); j++) {
            if (intersects(zombies.at(j).x, zombies.at(j).radius, shootingStars.at(i).x, shootingStars.at(i).radius) == true && zombies.at(j).color == shootingStars.at(i).color) {
                if (shootingStars.at(i).y == zombies.at(j).y) {
                    shootingStars.erase(shootingStars.begin() + i);
                    zombies.at(j).healthPoints--;
                    return;
                }
                
            }
        }
    }
    for (int i = 0; i < zombies.size(); i++) {
        if (zombies.at(i).healthPoints == 0) {
            zombies.at(i).dissapear = true;
            
        }
    }

    //kill plants ----------------------------------------------------------------------

    for (int i = 0; i < plants.size(); i++) {
        for (int j = 0; j < zombies.size(); j++) {
            if (intersects(zombies.at(j).x, zombies.at(j).radius, plants.at(i).x, squareSide / 2) == true && zombies.at(j).y == plants.at(i).y) {
                
                for (int k = 0; k < 9; k++) {
                    if ((gridSquares[k].x + squareSide / 2) == plants.at(i).x && (gridSquares[k].y + squareSide / 2 == plants.at(i).y) && zombies.at(j).x >= gridSquares[k].x) {
                        gridSquares[k].color = noColor;
                        
                    }
                }
                plants.at(i).dissapear = true;
                
            }
        }
    }
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < zombies.size(); j++) {
            if (intersects(zombies.at(j).x, zombies.at(j).radius, gridSquares[i].x, squareSide) == true && zombies.at(j).y == (gridSquares[i].y + squareSide /2)) {
                gridSquares[i].color = noColor;
                
            }
        }
    }

    
}

bool isInsideCircle(int circlex, int circley, int radius, int x, int y) {
    int dist = (x - circlex) * (x - circlex) + (y - circley) * (y - circley);
    if (dist <= radius * radius)
        return true;
    else
        return false;
}

void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
    
}


void Lab3::OnKeyPress(int key, int mods)
{
    
    
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    glm::ivec2 resolution = window->GetResolution();
    // Add mouse move event
    int logicMouseX = mouseX * 1280 / resolution.x;
    int logicMouseY = mouseY * 720 / resolution.y;
    click.x = logicMouseX;
    click.y = 720 - logicMouseY;
    
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    glm::ivec2 resolution = window->GetResolution();
    int logicMouseX = mouseX * 1280 / resolution.x;
    int logicMouseY = mouseY * 720 / resolution.y;
   
    if (!IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT))
    {
        for (int i = 0; i < randomStars.size(); i++) {
            if (isInsideCircle(randomStars.at(i).x, randomStars.at(i).y, randomStars.at(i).radius, logicMouseX, 720 - logicMouseY) == true) {
                game.stars++;
                randomStars.erase(randomStars.begin() + i);


            }
                }
        for (int i = 0; i < 4; i++) {
              if (logicMouseX >= GUIsquares[i].x && logicMouseX <= (GUIsquares[i].x + GUIsquares[i].side)) {
                if ((720 - logicMouseY) <= (GUIsquares[i].y + GUIsquares[i].side) && (720 - logicMouseY) >= GUIsquares[i].y) {
                    if (GUIsquares[i].cost <= game.stars) {
                        game.rombColor = GUIsquares[i].color;
                        game.clicked = true;
                    }
                
                }
            }
        }
    }
    else {
        for (int i = 0; i < 9; i++) {
            if (logicMouseX >= gridSquares[i].x && logicMouseX <= (gridSquares[i].x + gridSquares[i].side)) {
                if ((720 - logicMouseY) <= (gridSquares[i].y + gridSquares[i].side) && (720 - logicMouseY) >= gridSquares[i].y) {
                    if (gridSquares[i].color != noColor) {
                       
                        
                        for (int j = 0; j < plants.size(); j++) {
                            
                            if (plants.at(j).x == (gridSquares[i].x + squareSide / 2) && plants.at(j).y == (gridSquares[i].y + squareSide / 2)) {
                                
                                
                                plants.at(j).dissapear = true;
                            }
                        }
                        gridSquares[i].color = noColor;
                    }
                }
            }
        }
    }
    

    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    glm::ivec2 resolution = window->GetResolution();
    // Add mouse button release event
    int logicMouseX = mouseX * 1280 / resolution.x;
    int logicMouseY = mouseY * 720 / resolution.y;
    for (int i = 0; i < 9; i++) {
        if (logicMouseX >= gridSquares[i].x && logicMouseX <= (gridSquares[i].x + gridSquares[i].side)) {
            if ((720 - logicMouseY) <= (gridSquares[i].y + gridSquares[i].side) && (720 - logicMouseY) >= gridSquares[i].y) {
                if (game.rombColor != noColor && gridSquares[i].color == noColor) {
                    myPlants newPlant;
                    newPlant.color = game.rombColor;
                    newPlant.x = gridSquares[i].x + squareSide / 2;
                    newPlant.y = gridSquares[i].y + squareSide / 2;
                    plants.push_back(newPlant);
                    gridSquares[i].color = game.rombColor;
                    if (game.rombColor == "orange") game.stars -= 1;
                    if (game.rombColor == "blue") game.stars -= 2;
                    if (game.rombColor == "yellow") game.stars -= 2;
                    if (game.rombColor == "purple") game.stars -= 3;
                    
                }
                
            }
        }
    }
    if (game.clicked == true) {
        game.clicked = false;
        game.rombColor = noColor;
    }
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    
}


void Lab3::OnWindowResize(int width, int height)
{
}
