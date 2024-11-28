#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "texture.h"
#include "player.h"

int checkColision(Sprite player, Block block){
    if (player.mesh.pos[0] >= block.mesh.pos[0] && player.mesh.pos[1] >= block.mesh.pos[1])
        return 1;
    return 0;
}