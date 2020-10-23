#ifndef SKY_BOX_HPP
#define SKY_BOX_HPP

#include "./../HierarchicalRenderable.hpp"
#include "./../lighting/Material.hpp"
#include "./../Texture.hpp"
#include <vector>
#include <glm/glm.hpp>

class SkyBox : public HierarchicalRenderable
{
public :
    ~SkyBox();
    SkyBox(ShaderProgramPtr shaderProgram, const std::string& filename);
    void setMaterial(const MaterialPtr& material);

private:
    void do_draw();
    void do_animate( float time );
    void getSkyBox(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords);

    std::vector< glm::vec3 > m_positions;
    std::vector< glm::vec4 > m_colors;
    std::vector< glm::vec3 > m_normals;
    std::vector< glm::vec2 > m_texCoords;

    unsigned int m_pBuffer;
    unsigned int m_cBuffer;
    unsigned int m_nBuffer;
    unsigned int m_tBuffer;

    MaterialPtr m_material;
    Texture m_tex;
};

typedef std::shared_ptr<SkyBox> SkyBoxPtr;

#endif
