#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "window.h"
#include "camera.h"
#include "texture.h"
#include "Terap.h"
#include "world.h"
#include "player.h"
#include "model/sprite.h"

int main(){
  GLFWwindow* window = createWindowAndInitGl();

  Camera camera = createCamera(2000, 900, (vec3){0.0f, 0.0f, 60.0f});

  registerBlocks();
  // initPlayer();
  Sprite playerSpite = createSprite("player.png");

  //LOOP
  while(!glfwWindowShouldClose(window)){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    worldGen(camera, window);
    
    drawSprite(playerSpite, (vec3){camera.pos[0], camera.pos[1], 1.0f}, camera, window);
    
    // if(checkColision(playerSpite, Blocks[DIRT])){
    //   playerSpite.mesh.pos[0] -= 1.0f;
    //   playerSpite.mesh.pos[1] -= 1.0f;
    // }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
      vec3 transBuffer = {1.0f, 1.0f, 1.0f};
		  glm_vec3_cross(camera.orientation, camera.up, transBuffer);
		  glm_normalize(transBuffer);
		  glm_vec3_scale(transBuffer, camera.speed, transBuffer);

		  glm_vec3_sub(camera.pos, transBuffer, camera.pos);	
	  }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
      vec3 transBuffer = {1.0f, 1.0f, 1.0f};
		  glm_vec3_cross(camera.orientation, camera.up, transBuffer);
		  glm_normalize(transBuffer);
		  glm_vec3_scale(transBuffer, camera.speed, transBuffer);

		  glm_vec3_add(camera.pos, transBuffer, camera.pos);	
	  }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
      vec3 transBuffer = {1.0f, 1.0f, 1.0f};
		  glm_vec3_scale(camera.orientation, camera.speed, transBuffer);
		  glm_vec3_add(camera.pos, transBuffer, camera.pos);	
	  }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
      vec3 transBuffer = {1.0f, 1.0f, 1.0f};
		  glm_vec3_scale(camera.orientation, camera.speed, transBuffer);
		  glm_vec3_sub(camera.pos, transBuffer, camera.pos);	
	  }
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
      glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if(glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //printf("Camera Position: x = %f, y = %f, z = %f\n", camera.pos[0], camera.pos[1], camera.pos[2]);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  clearBlocks();
  cleanSprite(playerSpite);
  clearFunc();

  return 1;
}
