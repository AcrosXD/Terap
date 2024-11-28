#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "model/block.h"
#include "Mesh.h"
#include "texture.h"

#ifndef TERAP_H
#define TERAP_H

Block Blocks[100];

enum BLOCKS_INDEX {
    DIRT = 0
};

void registerBlocks();
void clearBlocks();

#endif