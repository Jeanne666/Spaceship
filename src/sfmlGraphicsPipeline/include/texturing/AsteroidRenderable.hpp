#ifndef ASTEROID_RENDERABLE_HPP
#define ASTEROID_RENDERABLE_HPP

#include "./KeyFramedTexturedLightedMeshRenderable.hpp"
#include "./../lighting/Material.hpp"
#include "./../lighting/Light.hpp"

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class AsteroidRenderable : public KeyFramedTexturedLightedMeshRenderable
{
    public:
        AsteroidRenderable(
            ShaderProgramPtr program,
            const std::string& mesh_filename,
            const std::string& texture_filename,
            const double transformation_scale );
};

typedef std::shared_ptr<AsteroidRenderable> AsteroidRenderablePtr;

#endif
