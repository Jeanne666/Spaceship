#include "../include/Texture.hpp"

#include <iostream>


#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

Texture::Texture(std::string filename) : m_texFilename(filename) {
    
    //Create texture
    glGenTextures(1, &m_texId);

    //Bind the texture
    glBindTexture(GL_TEXTURE_2D, m_texId);

    //Textured options
    glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    int width, height, nrChannels;
    unsigned char *data = stbi_load(m_texFilename.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {

        // Looking for the format
        assert((1 <= nrChannels) && (4 >= nrChannels));
        GLenum glformat;
        switch (nrChannels)
        {
        case 1:
            glformat = GL_RED;
            break;
        case 2:
            glformat = GL_RG;
            break;
        case 3:
            glformat = GL_RGB;
            break;
        case 4:
            glformat = GL_RGBA;
            break;
        }

        //std::cout << "---------------*-**-*-*-*-*-----------**-*-*-*-*-**c cool----------" << std::endl;
        glcheck(glTexImage2D(GL_TEXTURE_2D, 0, glformat, width, height, 0, glformat, GL_UNSIGNED_BYTE, data)); // Warning : change to GL_RGBA when using PNG !!!!
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //Release the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::render(ShaderProgramPtr shaderPrg, std::string nameInShader, int nbTexture)
{
    int texSampleLoc = shaderPrg->getUniformLocation(nameInShader);
    glcheck(glActiveTexture(GL_TEXTURE0 + nbTexture));
    glcheck(glBindTexture(GL_TEXTURE_2D, m_texId));
    //Send "texSampler" to Textured Unit 0
    glcheck(glUniform1i(texSampleLoc, nbTexture));
}

void Texture::bind()
{
    //Bind the texture
    glBindTexture(GL_TEXTURE_2D, m_texId);
}

void Texture::release()
{
    //Release texture
    glcheck(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::setWrapOption(int wrapOption)
{
    //Textured options
    if (wrapOption == 0)
    {
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    }
    else if (wrapOption == 1)
    {
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    }
    else if (wrapOption == 2)
    {
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
    }
}

void Texture::setFilterOption(int filterOption)
{
    if (filterOption == 0)
    {
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    }
    else if (filterOption == 1)
    {
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
    else if (filterOption == 2)
    {
        glcheck(glGenerateMipmap(GL_TEXTURE_2D));
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }
}

Texture::~Texture()
{
    glcheck(glDeleteTextures(1, &m_texId));
}