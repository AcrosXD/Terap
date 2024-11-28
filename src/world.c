#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "model/block.h"
#include "Terap.h"
#include "perlin.h"
#include "world.h"

int worldHeight = 50;
int worldWidth = 800;

void worldGen(Camera camera, GLFWwindow* window) {
    int perlinHeight = 0;
    for(int x = 0; x < worldWidth; x++) {
        perlinHeight = floor(PerlinNoise2D((float)x / 30.0f, 10.0f, 2.0, 2.0, 2) * worldHeight);
        for(int y = -25; y < perlinHeight; y++) {
            placeBlock(Blocks[DIRT], (vec3){(float)x, (float)y, 1.0f}, camera, window);
        }
    }
    // placeBlock(Blocks[DIRT], (vec3){1.0f, 1.0f, 1.0f}, camera, window);
}