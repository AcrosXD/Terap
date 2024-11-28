#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "model/block.h"
#include "Mesh.h"
#include "texture.h"
#include "Terap.h"

void registerBlocks(){
    Block dirt = createBlock("dirt.png");
    Blocks[0] = dirt;
}

void clearBlocks(){
    for (int i = 0; i > 1; i++){
        deleteShader(Blocks[i].shader);
        deleteMesh(Blocks[i].mesh);
    }
}