#include <vector>

#include <Viewer.hpp>
#include <ShaderProgram.hpp>

#include <lighting/PointLightRenderable.hpp>
//#include <lighting/SpotLightRenderable.hpp>

#include <FrameRenderable.hpp>
#include <CubeRenderable.hpp>
#include <texturing/SkyBox.hpp>
#include <lighting/LightedMeshRenderable.hpp>
#include <texturing/KeyFramedTexturedLightedMeshRenderable.hpp>
#include <texturing/AsteroidRenderable.hpp>

int shuttleAnimation(KeyFramedTexturedLightedMeshRenderablePtr& shuttle, Viewer& viewer);
void asteroid1Animation(AsteroidRenderablePtr& asteroid);
void asteroid2Animation(AsteroidRenderablePtr& asteroid);
void asteroid3Animation(AsteroidRenderablePtr& asteroid);


void initialize_scene( Viewer& viewer )
{  
    //Default shader
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>(  "../../sfmlGraphicsPipeline/shaders/flatVertex.glsl","../../sfmlGraphicsPipeline/shaders/flatFragment.glsl");
    viewer.addShaderProgram( flatShader );

    //Define a shader that encode an illumination model
    ShaderProgramPtr phongShader = std::make_shared<ShaderProgram>( "../../sfmlGraphicsPipeline/shaders/phongVertex.glsl","../../sfmlGraphicsPipeline/shaders/phongFragment.glsl");
    viewer.addShaderProgram( phongShader );

    //Add a 3D frame to the viewer
    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);

	//Skybox Cube
    ShaderProgramPtr skyBoxShader = std::make_shared<ShaderProgram>("../../sfmlGraphicsPipeline/shaders/skyBoxTextureVertex.glsl","../../sfmlGraphicsPipeline/shaders/skyBoxTextureFragment.glsl");
    viewer.addShaderProgram( skyBoxShader );
    
    SkyBoxPtr skybox = std::make_shared<SkyBox>(skyBoxShader,"../../../model/skybox/skymap.png");
    skybox->setParentTransform(glm::scale( glm::mat4(1.0), glm::vec3(100.0,100.0,100.0) ));
    viewer.addRenderable( skybox );

    //Define a transformation
    glm::mat4 parentTransformation, localTransformation;

    //Define a directional light for the whole scene
    glm::vec3 d_direction = glm::normalize(glm::vec3(1.0,0.63,-1.0));
    glm::vec3 d_ambient(0.5,0.5,0.5), d_diffuse(0.7,0.7,0.7), d_specular(0.7,0.7,0.7);
    DirectionalLightPtr directionalLight = std::make_shared<DirectionalLight>(d_direction, d_ambient, d_diffuse, d_specular);
    viewer.setDirectionalLight(directionalLight);


    //Define a point light
    /*glm::vec3 p_position(0.0,0.0,0.0), p_ambient(0.0,0.0,0.0), p_diffuse(0.0,0.0,0.0), p_specular(0.0,0.0,0.0);
    float p_constant=0.0, p_linear=0.0, p_quadratic=0.0;
    p_position = glm::vec3(0.0, 0.0, 5.0);
    p_ambient = glm::vec3(0.0,0.0,0.0);
    p_diffuse = glm::vec3(1.0,0.8,0.8);
    p_specular = glm::vec3(1.0,0.8,0.8);
    p_constant=1.0;
    p_linear=5e-1;
    p_quadratic=0;
    PointLightPtr pointLight1 = std::make_shared<PointLight>(p_position, p_ambient, p_diffuse, p_specular, p_constant, p_linear, p_quadratic);
    viewer.addPointLight(pointLight1);
    PointLightRenderablePtr pointLightRenderable1 = std::make_shared<PointLightRenderable>(flatShader, pointLight1);
    viewer.addRenderable(pointLightRenderable1);*/

/*    p_position = glm::vec3(8, 5.0, 5.0);
    p_ambient = glm::vec3(0.0,0.0,0.0);
    p_diffuse = glm::vec3(0.0,0.0,1.0);
    p_specular = glm::vec3(0.0,0.0,1.0);
    p_constant=1.0;
    p_linear=5e-1;
    p_quadratic=0;
    PointLightPtr pointLight2 = std::make_shared<PointLight>(p_position, p_ambient, p_diffuse, p_specular, p_constant, p_linear, p_quadratic);
    PointLightRenderablePtr pointLightRenderable2 = std::make_shared<PointLightRenderable>(flatShader, pointLight2);
    localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5,0.5,0.5));
    pointLightRenderable2->setLocalTransform(localTransformation);
    viewer.addPointLight(pointLight2);
    viewer.addRenderable(pointLightRenderable2);

    //Define a spot light
    glm::vec3 s_position(0.0,5.0,-8.0), s_spotDirection = glm::normalize(glm::vec3(0.0,-1.0,1.0));
    //glm::vec3 s_ambient(0.0,0.0,0.0), s_diffuse(0.0,0.0,0.0), s_specular(0.0,0.0,0.0);
    glm::vec3 s_ambient(0.0,0.0,0.0), s_diffuse(0.5,0.5,0.5), s_specular(0.5,0.5,0.5);
    float s_constant=1.0, s_linear=0.0, s_quadratic=0.0;
    float s_innerCutOff=std::cos(glm::radians(20.0f)), s_outerCutOff=std::cos(glm::radians(40.0f));
    SpotLightPtr spotLight = std::make_shared<SpotLight>(s_position, s_spotDirection,
                                                         s_ambient, s_diffuse, s_specular,
                                                         s_constant, s_linear, s_quadratic,
                                                         s_innerCutOff, s_outerCutOff);
    SpotLightRenderablePtr spotLightRenderable = std::make_shared<SpotLightRenderable>(flatShader, spotLight);
    localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5,0.5,0.5));
    spotLightRenderable->setLocalTransform(localTransformation);
    viewer.addSpotLight(spotLight);
    viewer.addRenderable(spotLightRenderable);
*/
    
    //Define a shader for textured renderables
    ShaderProgramPtr textureShader = std::make_shared<ShaderProgram>( "../../sfmlGraphicsPipeline/shaders/textureVertex.glsl","../../sfmlGraphicsPipeline/shaders/textureFragment.glsl");
    viewer.addShaderProgram( textureShader );
    
        
    //Moon
    /*AsteroidRenderablePtr moon = std::make_shared<AsteroidRenderable>(textureShader, "../../../model/asteroid/Moon_3D_Model/moon.obj", "../../../model/asteroid/Moon_3D_Model/MoonMap2_2500x1250.jpg", 0.1);
    viewer.addRenderable(moon);*/
    
    //Asteroid1
    AsteroidRenderablePtr asteroid1 = std::make_shared<AsteroidRenderable>(textureShader, "../../../model/asteroid/L3/asteroid.obj", "../../../model/asteroid/L3/10464_Asteroid_v1_diffuse.jpg", 0.017);
    viewer.addRenderable(asteroid1);
    
    asteroid1Animation(asteroid1);
            
    //Asteroid2
    AsteroidRenderablePtr asteroid2 = std::make_shared<AsteroidRenderable>(textureShader, "../../../model/asteroid/bennu/bennu.obj", "../../../model/asteroid/_textures/moon_surface.jpg", 5.0);
    viewer.addRenderable(asteroid2);
    
    asteroid2Animation(asteroid2);
    
    //Asteroid3
    AsteroidRenderablePtr asteroid3 = std::make_shared<AsteroidRenderable>(textureShader, "../../../model/asteroid/L3/asteroid.obj", "../../../model/asteroid/_textures/moon_surface.jpg", 0.02);
    viewer.addRenderable(asteroid3);
    
    asteroid3Animation(asteroid3);
    
    //Shuttle
    //KeyFramedTexturedLightedMeshRenderablePtr shuttle = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/Orbiter_Space_Shuttle/shuttle.obj", "../../../model/Orbiter_Space_Shuttle/Orbiter_Space_Shuttle_OV-103_Discovery-150k-4096-diffuse.jpg");
    //shuttle->setLocalTransform(glm::scale(glm::mat4(1.0f),glm::vec3(0.1,0.1,0.1)));
    KeyFramedTexturedLightedMeshRenderablePtr shuttle = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/shuttle_test/test2.obj", "../../../model/shuttle_test/texture/texture-0.png");
    shuttle->setLocalTransform(glm::scale(glm::mat4(1.0f),glm::vec3(0.05,0.05,0.05)));
    shuttle->setMaterial(Material::Pearl());
    viewer.addRenderable(shuttle);
    
    int t=shuttleAnimation(shuttle, viewer);
    
    //FIXME
    //Fire
    /*KeyFramedTexturedLightedMeshRenderablePtr fire = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/fire/fire.obj", "../../../model/fire/fire.png");
    fire->setLocalTransform(glm::translate(glm::mat4(1.0),glm::vec3(0.45,-0.05,3.8)));
    fire->setMaterial(Material::Pearl());
    viewer.addRenderable(fire);*/
    
    //Position the camera
	viewer.getCamera().setAnimation(false);

	CubeRenderablePtr cube = std::make_shared<CubeRenderable>(flatShader);
	viewer.addRenderable(cube);

    viewer.startAnimation();
    viewer.setAnimationLoop(true, t);
}

int main() 
{
	Viewer viewer(1280,720);
	initialize_scene(viewer);

	while( viewer.isRunning() )
	{
		viewer.handleEvent();
		viewer.animate();
		viewer.draw();
		viewer.display();
	}	

	return EXIT_SUCCESS;
}

int shuttleAnimation(KeyFramedTexturedLightedMeshRenderablePtr& shuttle, Viewer& viewer){
	//NOTE: To combine 2 rotations: (2nd rot quaternion) * (1st rot quaternion)
	
    std::vector<GeometricTransformation> gtShuttle;
    float t=0.0;
    
    //-3s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-25,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-20,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-15,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-10,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    //0s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-5,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{0,0,0},
    											glm::angleAxis(glm::radians(-15.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{5.5,1.3,1},
    											glm::angleAxis(glm::radians(15.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-30.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{9.1,5.2,3},
    											glm::angleAxis(glm::radians(40.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-40.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{10,10,3.5},
    											glm::angleAxis(glm::radians(80.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-30.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    //3.75s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{8,15,3},
    											glm::angleAxis(glm::radians(120.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-10.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{6,20,2},
    											glm::angleAxis(glm::radians(100.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(15.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{6.9,24.9,0},
    											glm::angleAxis(glm::radians(70.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(25.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{10.3,28.6,-2},
    											glm::angleAxis(glm::radians(30.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(35.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{15,30,-3},
    											glm::angleAxis(glm::radians(10.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(45.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    //7.5s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{19.5,28.5,-3.7},
    											glm::angleAxis(glm::radians(-20.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(45.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{22.2,26.1,-4},
    											glm::angleAxis(glm::radians(-45.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(40.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{24.2,22.4,-3},
    											glm::angleAxis(glm::radians(-80.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(40.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{24.7,18.8,-1},
    											glm::angleAxis(glm::radians(-90.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(30.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{23.5,14,0},
    											glm::angleAxis(glm::radians(-105.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(15.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    //11.25s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{20,10,0.5},
    											glm::angleAxis(glm::radians(-115.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(5.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{17.7,6,1},
    											glm::angleAxis(glm::radians(-110.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-10.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{17,1.7,2},
    											glm::angleAxis(glm::radians(-90.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-30.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{18.4,-3.7,3},
    											glm::angleAxis(glm::radians(-60.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-40.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{21.4,-7.4,4.5},
    											glm::angleAxis(glm::radians(-30.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-40.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    //15s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{26.9,-8.5,5.5},
    											glm::angleAxis(glm::radians(-10.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-30.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{31.3,-6.5,5},
    											glm::angleAxis(glm::radians(15.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-20.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{35.1,-2.3,4},
    											glm::angleAxis(glm::radians(30.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-10.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{39.2,0.7,3},
    											glm::angleAxis(glm::radians(20.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-7.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{45.3,3.7,1.5},
    											glm::angleAxis(glm::radians(10.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-3.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    //18.75s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{50,5,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));
        
    for(auto it=gtShuttle.begin() ; it<gtShuttle.end() ; ++it){
    	shuttle->addParentTransformKeyframe(*it,t);
    	viewer.getCamera().addKeyframe((*it).getTranslation()+glm::vec3(-3,3,1),(*it).getTranslation(),t);
    	t+=0.75;
    }
    gtShuttle.clear();
    
    
    //19.5s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{55,5,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{66,3,0},
    											glm::angleAxis(glm::radians(2.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{72.5,-1,0},
    											glm::angleAxis(glm::radians(10.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{80,-1,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{87.5,0,0},
    											glm::angleAxis(glm::radians(-7.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    //22s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{91,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));

	for(auto it=gtShuttle.begin() ; it<gtShuttle.end() ; ++it){
    	shuttle->addParentTransformKeyframe(*it,t);
    	viewer.getCamera().addKeyframe((*it).getTranslation()+glm::vec3(-12,-(*it).getTranslation()[1],5),(*it).getTranslation()+glm::vec3(0,-(*it).getTranslation()[1],0),t);
    	t+=0.5;
    }
    gtShuttle.clear();

	gtShuttle.push_back(GeometricTransformation(glm::vec3{92,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
	gtShuttle.push_back(GeometricTransformation(glm::vec3{96,2,0},
    											glm::angleAxis(glm::radians(-120.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{99,4,0},
    											glm::angleAxis(glm::radians(-240.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{102,6,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtShuttle.begin() ; it<gtShuttle.end() ; ++it){
    	shuttle->addParentTransformKeyframe(*it,t);
    	viewer.getCamera().addKeyframe((*it).getTranslation()+glm::vec3(-12,-(*it).getTranslation()[1],5),(*it).getTranslation()+glm::vec3(0,-(*it).getTranslation()[1],0),t);
    	t+=0.3;
    }
    gtShuttle.clear();
    
    gtShuttle.push_back(GeometricTransformation(glm::vec3{107,6,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtShuttle.begin() ; it<gtShuttle.end() ; ++it){
    	shuttle->addParentTransformKeyframe(*it,t);
    	viewer.getCamera().addKeyframe((*it).getTranslation()+glm::vec3(-12,-(*it).getTranslation()[1],5),(*it).getTranslation()+glm::vec3(0,-(*it).getTranslation()[1],0),t);
    	t+=0.5;
    }
    gtShuttle.clear();
    
    gtShuttle.push_back(GeometricTransformation(glm::vec3{111,6,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{115,4,0},
    											glm::angleAxis(glm::radians(-240.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{119,2,0},
    											glm::angleAxis(glm::radians(-120.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{123,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{127,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{130,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    //27s
    
    for(auto it=gtShuttle.begin() ; it<gtShuttle.end() ; ++it){
    	shuttle->addParentTransformKeyframe(*it,t);
    	viewer.getCamera().addKeyframe((*it).getTranslation()+glm::vec3(-12,-(*it).getTranslation()[1],5),(*it).getTranslation()+glm::vec3(0,-(*it).getTranslation()[1],0),t);
    	t+=0.3;
    }
    gtShuttle.clear();
    
    return t+1;
        
}

void asteroid1Animation(AsteroidRenderablePtr& asteroid){
    std::vector<GeometricTransformation> gt;
    float t=0.0;
    
    gt.push_back(GeometricTransformation(glm::vec3{26,2,5},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0.7, 0, 0.7)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{26,2,5},
    											glm::angleAxis(glm::radians(72.f), glm::vec3(0.7, 0, 0.7)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{26,2,5},
    											glm::angleAxis(glm::radians(144.f), glm::vec3(0.7, 0, 0.7)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{26,2,5},
    											glm::angleAxis(glm::radians(216.f), glm::vec3(0.7, 0, 0.7)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{26,2,5},
    											glm::angleAxis(glm::radians(360.f), glm::vec3(0.7, 0, 0.7)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gt.begin() ; it<gt.end() ; ++it){
    	asteroid->addParentTransformKeyframe(*it,t);
    	t+=6;
    }
}

void asteroid2Animation(AsteroidRenderablePtr& asteroid){
    std::vector<GeometricTransformation> gt;
    float t=0.0;
    
    gt.push_back(GeometricTransformation(glm::vec3{10,-5,-5},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0.7, 0.7)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{10,-5,-5},
    											glm::angleAxis(glm::radians(72.f), glm::vec3(0, 0.7, 0.7)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{10,-5,-5},
    											glm::angleAxis(glm::radians(144.f), glm::vec3(0, 0.7, 0.7)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{10,-5,-5},
    											glm::angleAxis(glm::radians(216.f), glm::vec3(0, 0.7, 0.7)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{10,-5,-5},
    											glm::angleAxis(glm::radians(360.f), glm::vec3(0, 0.7, 0.7)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gt.begin() ; it<gt.end() ; ++it){
    	asteroid->addParentTransformKeyframe(*it,t);
    	t+=6;
    }
}


void asteroid3Animation(AsteroidRenderablePtr& asteroid){
    std::vector<GeometricTransformation> gt;
    float t=0.0;
    
    gt.push_back(GeometricTransformation(glm::vec3{15,20,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 1, 0)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{15,20,0},
    											glm::angleAxis(glm::radians(72.f), glm::vec3(0, 1, 0)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{15,20,0},
    											glm::angleAxis(glm::radians(144.f), glm::vec3(0, 1, 0)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{15,20,0},
    											glm::angleAxis(glm::radians(216.f), glm::vec3(0, 1, 0)),
    											glm::vec3{1,1,1}));
    gt.push_back(GeometricTransformation(glm::vec3{15,20,0},
    											glm::angleAxis(glm::radians(360.f), glm::vec3(0, 1, 0)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gt.begin() ; it<gt.end() ; ++it){
    	asteroid->addParentTransformKeyframe(*it,t);
    	t+=6;
    }
}


