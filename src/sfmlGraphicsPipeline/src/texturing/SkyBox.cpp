#include "./../../include/texturing/SkyBox.hpp"
#include "./../../include/gl_helper.hpp"
#include "./../../include/Utils.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>
#include <iostream>

SkyBox::~SkyBox()
{
    glcheck(glDeleteBuffers(1, &m_pBuffer));
    glcheck(glDeleteBuffers(1, &m_cBuffer));
    glcheck(glDeleteBuffers(1, &m_tBuffer));
    glcheck(glDeleteBuffers(1, &m_nBuffer));
}

SkyBox::SkyBox(ShaderProgramPtr shaderProgram, const std::string& filename)
    : HierarchicalRenderable(shaderProgram),
      m_pBuffer(0), m_cBuffer(0), m_nBuffer(0), m_tBuffer(0), m_tex(filename)
{
    //Initialize geometry
    getSkyBox(m_positions, m_normals, m_texCoords);
    m_colors.resize(m_positions.size(), glm::vec4(1.0,1.0,1.0,1.0));

    //Create buffers
    glcheck(glGenBuffers(1, &m_pBuffer)); //vertices
    glcheck(glGenBuffers(1, &m_cBuffer)); //colors
    glcheck(glGenBuffers(1, &m_nBuffer)); //normals
    glcheck(glGenBuffers(1, &m_tBuffer)); //texture coords

    //Activate buffer and send data to the graphics card
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
    glcheck(glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
    glcheck(glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
    glcheck(glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_tBuffer));
    glcheck(glBufferData(GL_ARRAY_BUFFER, m_texCoords.size()*sizeof(glm::vec2), m_texCoords.data(), GL_STATIC_DRAW));
}

void SkyBox::do_draw()
{
    //Location
    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    int colorLocation = m_shaderProgram->getAttributeLocation("vColor");
    int normalLocation = m_shaderProgram->getAttributeLocation("vNormal");
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
    int nitLocation = m_shaderProgram->getUniformLocation("NIT");
    int textureLocation = m_shaderProgram->getAttributeLocation("vTexCoord");

    //Send material uniform to GPU
    Material::sendToGPU(m_shaderProgram, m_material);

    //Send uniform to the graphics card
    if(modelLocation != ShaderProgram::null_location)
    {
        glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
    }

    if( nitLocation != ShaderProgram::null_location )
    {
        glcheck(glUniformMatrix3fv( nitLocation, 1, GL_FALSE,
                                    glm::value_ptr(glm::transpose(glm::inverse(glm::mat3(getModelMatrix()))))));
    }

    if(positionLocation != ShaderProgram::null_location)
    {
        //Activate location
        glcheck(glEnableVertexAttribArray(positionLocation));
        //Bind buffer
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
        //Specify internal format
        glcheck(glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    if(colorLocation != ShaderProgram::null_location)
    {
        glcheck(glEnableVertexAttribArray(colorLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
        glcheck(glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    if(normalLocation != ShaderProgram::null_location)
    {
        glcheck(glEnableVertexAttribArray(normalLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
        glcheck(glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    //Bind texture in Textured Unit 0
    if(textureLocation != ShaderProgram::null_location)
    {
        m_tex.render(m_shaderProgram, "texSampler");
        glcheck(glEnableVertexAttribArray(textureLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_tBuffer));
        glcheck(glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    //Draw triangles elements
    glcheck(glDrawArrays(GL_TRIANGLES,0, m_positions.size()));

    //Release texture
    m_tex.release();
    if(positionLocation != ShaderProgram::null_location)
    {
        glcheck(glDisableVertexAttribArray(positionLocation));
    }
    if(colorLocation != ShaderProgram::null_location)
    {
        glcheck(glDisableVertexAttribArray(colorLocation));
    }
    if(normalLocation != ShaderProgram::null_location)
    {
        glcheck(glDisableVertexAttribArray(normalLocation));
    }
    if(textureLocation != ShaderProgram::null_location)
    {
        glcheck(glDisableVertexAttribArray(textureLocation));
    }
}

void SkyBox::do_animate(float time)
{

}

void SkyBox::setMaterial(const MaterialPtr& material)
{
    m_material = material;
}

void SkyBox::getSkyBox(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords)
{
   //Face 1 bottom
   positions.push_back(glm::vec3(-0.5, -0.5, -0.5));
   positions.push_back(glm::vec3(0.5, 0.5, -0.5));
   positions.push_back(glm::vec3(0.5, -0.5, -0.5));

   texCoords.push_back(glm::vec2(0.25,0.5));
   texCoords.push_back(glm::vec2(0.5,0.75));
   texCoords.push_back(glm::vec2(0.5,0.5));

   normals.push_back(glm::vec3(0.0,0.0,-1.0));
   normals.push_back(glm::vec3(0.0,0.0,-1.0));
   normals.push_back(glm::vec3(0.0,0.0,-1.0));

   //Face 2
   positions.push_back(glm::vec3(-0.5, -0.5, -0.5));
   positions.push_back(glm::vec3(-0.5, 0.5, -0.5));
   positions.push_back(glm::vec3(0.5, 0.5, -0.5));

   texCoords.push_back(glm::vec2(0.25,0.5));
   texCoords.push_back(glm::vec2(0.25,0.75));
   texCoords.push_back(glm::vec2(0.5,0.75));

   normals.push_back(glm::vec3(0.0,0.0,-1.0));
   normals.push_back(glm::vec3(0.0,0.0,-1.0));
   normals.push_back(glm::vec3(0.0,0.0,-1.0));

   //Face 3 right
   positions.push_back(glm::vec3(0.5, -0.5, -0.5));
   positions.push_back(glm::vec3(0.5, 0.5, 0.5));
   positions.push_back(glm::vec3(0.5, -0.5, 0.5));

   texCoords.push_back(glm::vec2(0.5,0.5));
   texCoords.push_back(glm::vec2(0.75,0.25));
   texCoords.push_back(glm::vec2(0.5,0.25));

   normals.push_back(glm::vec3(1.0,0.0,0.0));
   normals.push_back(glm::vec3(1.0,0.0,0.0));
   normals.push_back(glm::vec3(1.0,0.0,0.0));

   //Face 4
   positions.push_back(glm::vec3(0.5, -0.5, -0.5));
   positions.push_back(glm::vec3(0.5, 0.5, -0.5));
   positions.push_back(glm::vec3(0.5, 0.5, 0.5));

   texCoords.push_back(glm::vec2(0.5,0.5));
   texCoords.push_back(glm::vec2(0.75,0.5));
   texCoords.push_back(glm::vec2(0.75,0.25));

   normals.push_back(glm::vec3(1.0,0.0,0.0));
   normals.push_back(glm::vec3(1.0,0.0,0.0));
   normals.push_back(glm::vec3(1.0,0.0,0.0));

   //Face 5 top
   positions.push_back(glm::vec3(-0.5, 0.5, 0.5));
   positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
   positions.push_back(glm::vec3(0.5, -0.5, 0.5));

   texCoords.push_back(glm::vec2(0.25,0.0));
   texCoords.push_back(glm::vec2(0.25,0.25));
   texCoords.push_back(glm::vec2(0.5,0.25));

   normals.push_back(glm::vec3(0.0,0.0,1.0));
   normals.push_back(glm::vec3(0.0,0.0,1.0));
   normals.push_back(glm::vec3(0.0,0.0,1.0));

   //Face 6
   positions.push_back(glm::vec3(-0.5, 0.5, 0.5));
   positions.push_back(glm::vec3(0.5, -0.5, 0.5));
   positions.push_back(glm::vec3(0.5, 0.5, 0.5));

   texCoords.push_back(glm::vec2(0.25,0.0));
   texCoords.push_back(glm::vec2(0.5,0.25));
   texCoords.push_back(glm::vec2(0.5,0.0));

   normals.push_back(glm::vec3(0.0,0.0,1.0));
   normals.push_back(glm::vec3(0.0,0.0,1.0));
   normals.push_back(glm::vec3(0.0,0.0,1.0));

   //Face 7 left
   positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
   positions.push_back(glm::vec3(-0.5, 0.5, -0.5));
   positions.push_back(glm::vec3(-0.5, -0.5, -0.5));

   texCoords.push_back(glm::vec2(0.25,0.25));
   texCoords.push_back(glm::vec2(0.0,0.5));
   texCoords.push_back(glm::vec2(0.25,0.5));

   normals.push_back(glm::vec3(-1.0,0.0,0.0));
   normals.push_back(glm::vec3(-1.0,0.0,0.0));
   normals.push_back(glm::vec3(-1.0,0.0,0.0));

   //Face 8
   positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
   positions.push_back(glm::vec3(-0.5, 0.5, 0.5));
   positions.push_back(glm::vec3(-0.5, 0.5, -0.5));

   texCoords.push_back(glm::vec2(0.25,0.25));
   texCoords.push_back(glm::vec2(0.0,0.25));
   texCoords.push_back(glm::vec2(0.0,0.5));

   normals.push_back(glm::vec3(-1.0,0.0,0.0));
   normals.push_back(glm::vec3(-1.0,0.0,0.0));
   normals.push_back(glm::vec3(-1.0,0.0,0.0));

   //Face 9 back
   positions.push_back(glm::vec3(-0.5, 0.5, -0.5));
   positions.push_back(glm::vec3(0.5, 0.5, 0.5));
   positions.push_back(glm::vec3(0.5, 0.5, -0.5));

   texCoords.push_back(glm::vec2(1.0,0.5));
   texCoords.push_back(glm::vec2(0.75,0.25));
   texCoords.push_back(glm::vec2(0.75,0.5));

   normals.push_back(glm::vec3(0.0,1.0,0.0));
   normals.push_back(glm::vec3(0.0,1.0,0.0));
   normals.push_back(glm::vec3(0.0,1.0,0.0));

   //Face 10
   positions.push_back(glm::vec3(-0.5, 0.5, -0.5));
   positions.push_back(glm::vec3(-0.5, 0.5, 0.5));
   positions.push_back(glm::vec3(0.5, 0.5, 0.5));

   texCoords.push_back(glm::vec2(1.0,0.5));
   texCoords.push_back(glm::vec2(1.0,0.25));
   texCoords.push_back(glm::vec2(0.75,0.25));

   normals.push_back(glm::vec3(0.0,1.0,0.0));
   normals.push_back(glm::vec3(0.0,1.0,0.0));
   normals.push_back(glm::vec3(0.0,1.0,0.0));

   //Face 11 front ok
   positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
   positions.push_back(glm::vec3(-0.5, -0.5, -0.5));
   positions.push_back(glm::vec3(0.5, -0.5, -0.5));

   texCoords.push_back(glm::vec2(0.25,0.25));
   texCoords.push_back(glm::vec2(0.25,0.5));
   texCoords.push_back(glm::vec2(0.5,0.5));

   normals.push_back(glm::vec3(0.0,-1.0,0.0));
   normals.push_back(glm::vec3(0.0,-1.0,0.0));
   normals.push_back(glm::vec3(0.0,-1.0,0.0));

   //Face 12 ok
   positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
   positions.push_back(glm::vec3(0.5, -0.5, -0.5));
   positions.push_back(glm::vec3(0.5, -0.5, 0.5));

   texCoords.push_back(glm::vec2(0.25,0.25));
   texCoords.push_back(glm::vec2(0.5,0.5));
   texCoords.push_back(glm::vec2(0.5,0.25));

   normals.push_back(glm::vec3(0.0,-1.0,0.0));
   normals.push_back(glm::vec3(0.0,-1.0,0.0));
   normals.push_back(glm::vec3(0.0,-1.0,0.0));
}
