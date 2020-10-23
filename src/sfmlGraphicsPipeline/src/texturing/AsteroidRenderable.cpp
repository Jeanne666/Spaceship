#include "./../../include/texturing/AsteroidRenderable.hpp"
#include "./../../include/gl_helper.hpp"
#include "./../../include/log.hpp"
#include "./../../include/Io.hpp"
#include "./../../include/Utils.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

AsteroidRenderable::AsteroidRenderable(
    ShaderProgramPtr shaderProgram, const std::string& mesh_filename, const std::string& texture_filename, const double transformation_scale ) :
    KeyFramedTexturedLightedMeshRenderable(shaderProgram, mesh_filename, texture_filename)
{
    this->setLocalTransform(
    	glm::scale( glm::mat4(1.0),
    				glm::vec3(transformation_scale, transformation_scale, transformation_scale) )
    );
  
    this->setMaterial(Material::Pearl());
}


