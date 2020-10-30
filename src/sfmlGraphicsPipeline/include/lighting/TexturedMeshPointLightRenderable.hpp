#ifndef POINT_LIGHT_RENDERABLE_HPP
#define POINT_LIGHT_RENDERABLE_HPP

#include "./../HierarchicalRenderable.hpp"
#include "./../KeyframeCollection.hpp"
#include "Light.hpp"

#include <string>
#include <vector>
#include <glm/glm.hpp>

class TexturedMeshPointLightRenderable : public HierarchicalRenderable
{
public:
    ~TexturedMeshPointLightRenderable();
    TexturedMeshPointLightRenderable( ShaderProgramPtr program, const std::string& mesh_filename,
            const std::string& texture_filename, PointLightPtr light);
    void addLocalTransformKeyframe( const GeometricTransformation& transformation, float time );
    void addParentTransformKeyframe( const GeometricTransformation& transformation, float time );
    //void setAlpha( const float alpha );

private:
    void do_draw();
    void do_animate( float time );

    std::vector< glm::vec3 > m_positions;
    std::vector< glm::vec4 > m_colors;
    std::vector< glm::vec3 > m_normals;
	std::vector< glm::vec2 > m_texCoords;
    std::vector< unsigned int > m_indices;
    
    KeyframeCollection m_localKeyframes;
    KeyframeCollection m_parentKeyframes;

    unsigned int m_pBuffer;
    unsigned int m_cBuffer;
    unsigned int m_nBuffer;
    unsigned int m_iBuffer;
    unsigned int m_tBuffer;
    unsigned int m_texId;

    PointLightPtr m_light;
};

typedef std::shared_ptr<TexturedMeshPointLightRenderable> TexturedMeshPointLightRenderablePtr;

#endif
