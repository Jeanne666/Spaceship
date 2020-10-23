#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "./../../include/gl_helper.hpp"
#include "./../../include/log.hpp"
#include "./../../include/Utils.hpp"

#include <GL/glew.h>

#include <string>
#include "ShaderProgram.hpp"

class Texture 
{


    public:
        Texture(std::string filename);
        ~Texture();

        void render(ShaderProgramPtr shaderPrg, std::string nameInShader, int nbTexture = 0);

        void bind();
        void release();

        void setWrapOption(int wrapOption);
        void setFilterOption(int filterOption);




        GLuint m_texId;
        std::string m_texFilename;
};

#endif // TEXTURE_HPP
