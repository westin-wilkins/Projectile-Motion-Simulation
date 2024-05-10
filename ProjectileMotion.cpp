#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <raylib.h>

const double GRAVITY = 9.81;    // Acceleration due to gravity (m/s^2)

class Projectile
{
private:
    double angle;       // Launch angle of projectile (degrees)
    double velocity;    // Launch velocity of projectile (m/s)
    double mass;        // Mass of object (kg)
    double posX;        // X-coordinate of the projectile
    double posY;        // Y-coordinate of the projectile
    double time;        // Current time

public:
    Projectile(double angle, double velocity, double mass, double posX = 0.0, double posY = 0.0)
        : angle(angle), velocity(velocity), mass(mass), posX(posX), posY(posY), time(0.0)
    {}

    void simulateProjectile(double deltaTime)
    {
        // Degrees to radians conversion
        double angleRad = angle * M_PI / 180.0;

        // Calculate initial vertical and horizontal velocities
        double v0x = velocity * cos(angleRad);
        double v0y = velocity * sin(angleRad);

        // Update the position of the projectile based on time
        posX = v0x * time;
        posY = v0y * time - 0.5 * GRAVITY * time * time;

        // Update the time
        time += deltaTime;
    }

    double getPositionX() const { return posX; }
    double getPositionY() const { return posY; }
};

class ProjectileMotion
{
private:
    Projectile projectile;

public:
    ProjectileMotion(double angle, double velocity, double mass)
        : projectile(angle, velocity, mass)  
    {}

    void simulatePhysics()
    {
        const int screenWidth = 800;
        const int screenHeight = 600;

        InitWindow(screenWidth, screenHeight, "Projectile Simulation");

        SetTargetFPS(60);

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(BLACK);

            projectile.simulateProjectile(GetFrameTime());

            // Get the current position of the projectile
            double posX = projectile.getPositionX();
            double posY = screenHeight - projectile.getPositionY();  

            // Visualize the motion of the projectile
            DrawCircle(static_cast<int>(posX), static_cast<int>(posY), 5, RED);

            EndDrawing();
        }

        CloseWindow();
    }
};

int main()
{
    ProjectileMotion motion(45.0, 100.0, 10.0);
    motion.simulatePhysics();

    return 0;
}
