#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "camera.h"

Camera createCamera(int width, int height, vec3 pos){
	Camera camera;
	camera.width = width;
	camera.height = height;

	camera.speed = 0.1f;
	camera.sensitivity = 50.0f;

	glm_vec3_copy(pos, camera.pos);
	glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, camera.orientation);
	glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, camera.up);

	return camera;
}

void Matrix(float FOV, float nearPlane, float farPlane, Shader* shader, const char* uniform, Camera camera){ 
	mat4 view, proj, final;
	vec3 center = {1.0f, 1.0f, 1.0f};
	glm_mat4_identity(view);
	glm_mat4_identity(proj);
	glm_mat4_identity(final); 
	glm_vec3_add(camera.pos, camera.orientation, center);

	glm_lookat(camera.pos, center, camera.up, view);
	glm_perspective(glm_rad(FOV), (float)(2000/900), nearPlane, farPlane, proj);

	glm_mat4_mul(proj, view, final);

	glUniformMatrix4fv(glGetUniformLocation(shader->ID, uniform), 1, GL_FALSE, (const GLfloat*)final);
}

void Inputs(GLFWwindow* window, Camera camera){
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
      vec3 transformedConst = {1.0f, 1.0f, 1.0f};
		  glm_vec3_cross(camera.orientation, camera.up, transformedConst);
		  glm_normalize(transformedConst);
		  glm_vec3_scale(transformedConst, camera.speed, transformedConst);

		  glm_vec3_sub(camera.pos, transformedConst, camera.pos);	
	  }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
      vec3 transformedConst = {1.0f, 1.0f, 1.0f};
		  glm_vec3_cross(camera.orientation, camera.up, transformedConst);
		  glm_normalize(transformedConst);
		  glm_vec3_scale(transformedConst, camera.speed, transformedConst);

		  glm_vec3_add(camera.pos, transformedConst, camera.pos);	
	  }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
      vec3 transformedConst = {1.0f, 1.0f, 1.0f};
		  glm_vec3_scale(camera.orientation, camera.speed, transformedConst);
		  glm_vec3_add(camera.pos, transformedConst, camera.pos);	
	  }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
      vec3 transformedConst = {1.0f, 1.0f, 1.0f};
		  glm_vec3_scale(camera.orientation, camera.speed, transformedConst);
		  glm_vec3_sub(camera.pos, transformedConst, camera.pos);	
	  }
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
      glfwSetWindowShouldClose(window, true);
    }
}