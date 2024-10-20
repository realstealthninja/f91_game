#include <glm/ext/matrix_float2x2.hpp>
#include <glm/ext/vector_float2.hpp>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
 
Texture2D background;
class Entity
{
    public:
    Vector2 Position;
    Vector2 Rotation = {1.0f, 1.0f};
    void Draw(const Camera2D& camera)
    {
        Vector2 mouse_position = Vector2Normalize(GetScreenToWorld2D(GetMousePosition(), camera));
        Vector2 local_position = Vector2Normalize(GetScreenToWorld2D(Position, camera));
        
        glm::mat2x2 object_center_matrix = {
                                {local_position.x, 0.0},
                                {0.0, local_position.y}
        };

        std::cout <<  (object_center_matrix * glm::vec2(0.0, 0.0) == glm::vec2(local_position.x, local_position.y));

        // convert the origin
        float angle =  -Vector2Angle(mouse_position, Rotation) * RAD2DEG;
        DrawLine(0, 0, mouse_position.x*(1280 * 0.5f), mouse_position.y*(800 * 0.5f), YELLOW);
        DrawLine(0, 0, Rotation.x*(1280 * 0.5f), Rotation.y * (800 * 0.5), RED);
        DrawRectanglePro(Rectangle{Position.x, Position.y, 50, 50}, Vector2{25.0f, 25.0f}, angle, WHITE);
    }
};

int main()
{
    InitWindow(1280, 800, "game");
    SetTargetFPS(60);

    Entity player = Entity();
    
    player.Position = {500.0f, 500.0f};

    Camera2D camera = { 0 };
    camera.target = {player.Position.x, player.Position.y};
    camera.offset = Vector2{GetScreenWidth() * 0.5f,GetScreenHeight() * 0.5f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    background = LoadTexture("background.png");
    while (WindowShouldClose() == false)
    {
       

        if(IsKeyDown(KEY_W)){player.Position.y -= 20;}

        if(IsKeyDown(KEY_S)){player.Position.y += 20;}

        if(IsKeyDown(KEY_A)){player.Position.x-= 20;}

        if(IsKeyDown(KEY_D)){player.Position.x += 20;}

        camera.target = { player.Position.x + 25.0f, player.Position.y + 25.0f};       

        BeginDrawing();
            ClearBackground(BLACK);
        
            BeginMode2D(camera);
                DrawTextureRec(background, {0, 0, 5000, 5000}, {0,0}, WHITE); 
                player.Draw(camera); 
            EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}