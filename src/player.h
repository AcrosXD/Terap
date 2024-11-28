#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "model/sprite.h"
#include "model/block.h"
#include "Mesh.h"
#include "texture.h"

#ifndef PLAYER_H
#define PLAYER_H

int checkColision(Sprite player, Block block);

#endif