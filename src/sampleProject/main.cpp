#include <vector>

#include <Viewer.hpp>
#include <ShaderProgram.hpp>

//#include <lighting/SpotLightRenderable.hpp>

#include <lighting/TexturedMeshPointLightRenderable.hpp>
#include <FrameRenderable.hpp>
#include <texturing/SkyBox.hpp>
#include <lighting/LightedMeshRenderable.hpp>
#include <texturing/KeyFramedTexturedLightedMeshRenderable.hpp>
#include <texturing/AsteroidRenderable.hpp>
#include <SFML/Audio.hpp>



int shuttleAnimation(KeyFramedTexturedLightedMeshRenderablePtr& shuttle, Viewer& viewer);
void fireAnimation(TexturedMeshPointLightRenderablePtr& fireRenderable, const float TIME_MAX);
void asteroid1Animation(AsteroidRenderablePtr& asteroid);
void asteroid2Animation(AsteroidRenderablePtr& asteroid);
void asteroid3Animation(AsteroidRenderablePtr& asteroid);
void meanGuyAnimation(KeyFramedTexturedLightedMeshRenderablePtr& meanguy);
void missile0Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile);
void missile1Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile);
void missile2Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile);
void missile3Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile);
void missile4Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile);
void missile5Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile);
void missile6Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile);
void missileFAnimation(KeyFramedTexturedLightedMeshRenderablePtr& missile);
void sphereMFAnimation(TexturedMeshPointLightRenderablePtr& sphere);
void flashAnimation(TexturedMeshPointLightRenderablePtr& flash, float d);
void flashRAnimation(TexturedMeshPointLightRenderablePtr& flash);
void moonAnimation(AsteroidRenderablePtr& moon);
void sceneFinAnimation(TexturedMeshPointLightRenderablePtr& fin);
void titreDebutAnimation(TexturedMeshPointLightRenderablePtr& fin);
void titreFinAnimation(TexturedMeshPointLightRenderablePtr& fin);
//float CalcGauss( float x, float sigma );



void initialize_scene( Viewer& viewer )
{  

    //Audio
    /*sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sound.wav"))
        return -1;
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();*/

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
    skybox->setParentTransform(GeometricTransformation(glm::vec3{0,0,0},
    											glm::angleAxis(glm::radians(90.f), glm::vec3(0, 1, 1)),
    											glm::vec3{60,60,60}).toMatrix());
    											
    viewer.addRenderable( skybox );

    //Define a transformation
    glm::mat4 parentTransformation, localTransformation;

    //Define a directional light for the whole scene
    glm::vec3 d_direction = glm::normalize(glm::vec3(-1.0,-0.63,-1.0));
    glm::vec3 d_ambient(0.3,0.3,0.3), d_diffuse(0.7,0.7,0.7), d_specular(0.7,0.7,0.7);
    DirectionalLightPtr directionalLight = std::make_shared<DirectionalLight>(d_direction, d_ambient, d_diffuse, d_specular);
    viewer.setDirectionalLight(directionalLight);


    

/*  //Define a spot light
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
    ShaderProgramPtr unlightedTextureShader = std::make_shared<ShaderProgram>( "../../sfmlGraphicsPipeline/shaders/unlightedTextureVertex.glsl","../../sfmlGraphicsPipeline/shaders/unlightedTextureFragment.glsl");
    viewer.addShaderProgram( unlightedTextureShader );
    ShaderProgramPtr transpTextureShader = std::make_shared<ShaderProgram>( "../../sfmlGraphicsPipeline/shaders/unlightedTextureVertex.glsl","../../sfmlGraphicsPipeline/shaders/unlightedTextureTransparentFragment.glsl");
    viewer.addShaderProgram( transpTextureShader );
    
        
    //Moon
    AsteroidRenderablePtr moon = std::make_shared<AsteroidRenderable>(textureShader, "../../../model/asteroid/Moon_3D_Model/moon.obj", "../../../model/asteroid/Moon_3D_Model/MoonMap2_2500x1250.jpg", 0.3);
    viewer.addRenderable(moon);
    moonAnimation(moon);
    
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
    
    int t=0;
    t=shuttleAnimation(shuttle, viewer);
    
    //FireUp
    PointLightPtr fireLightUp = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0,0.0,0.0), glm::vec3(1.0,0.8,0.8), glm::vec3(1.0,0.8,0.8), 1.0, 5e-1, 0);
    viewer.addPointLight(fireLightUp);
    TexturedMeshPointLightRenderablePtr fireUp = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/fire/fire.obj", "../../../model/fire/fire5.png", fireLightUp);
    fireUp->setLocalTransform(GeometricTransformation(glm::vec3{-0.9,0,0.28},
    											glm::angleAxis(glm::radians(-90.f), glm::vec3(0, 1, 0)),
    											glm::vec3{0.2,0.2,0.2}).toMatrix());
    HierarchicalRenderable::addChild(shuttle, fireUp);
    fireAnimation(fireUp, t);
    
    //FireLeft
    PointLightPtr fireLightLeft = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0,0.0,0.0), glm::vec3(1.0,0.8,0.8), glm::vec3(1.0,0.8,0.8), 1.0, 5e-1, 0);
    viewer.addPointLight(fireLightLeft);
    TexturedMeshPointLightRenderablePtr fireLeft = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/fire/fire.obj", "../../../model/fire/fire5.png", fireLightLeft);
    fireLeft->setLocalTransform(GeometricTransformation(glm::vec3{-0.9,0.08,0.15},
    											glm::angleAxis(glm::radians(-90.f), glm::vec3(0, 1, 0)),
    											glm::vec3{0.2,0.2,0.2}).toMatrix());
    HierarchicalRenderable::addChild(shuttle, fireLeft);
    fireAnimation(fireLeft, t);
    
    //FireRight
    PointLightPtr fireLightRight = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0,0.0,0.0), glm::vec3(1.0,0.8,0.8), glm::vec3(1.0,0.8,0.8), 1.0, 5e-1, 0);
    viewer.addPointLight(fireLightRight);
    TexturedMeshPointLightRenderablePtr fireRight = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/fire/fire.obj", "../../../model/fire/fire5.png", fireLightRight);
    fireRight->setLocalTransform(GeometricTransformation(glm::vec3{-0.9,-0.08,0.15},
    											glm::angleAxis(glm::radians(-90.f), glm::vec3(0, 1, 0)),
    											glm::vec3{0.2,0.2,0.2}).toMatrix());
    HierarchicalRenderable::addChild(shuttle, fireRight);
    fireAnimation(fireRight, t);
    
    //MeanSpaceship
    KeyFramedTexturedLightedMeshRenderablePtr meanguy = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/meanSpaceship/usable/meanScaleUp.obj", "../../../model/meanSpaceship/texture/test.png");
    //../../../model/meanSpaceship/usable/meanScaleUp.mtl
    meanguy->setLocalTransform(glm::scale(glm::mat4(1.0f),glm::vec3(0.05,0.05,0.05)));
    //custom material : chrome
    const glm::vec3 ambient = glm::vec3(0.25f);	
    const glm::vec3 diffuse = glm::vec3(0.4f);
    const glm::vec3 specular = glm::vec3(0.774597f);
    float shininess = 0.6f;
    meanguy->setMaterial(MaterialPtr(new Material(ambient, diffuse, specular, shininess)));
    viewer.addRenderable(meanguy);
    meanGuyAnimation(meanguy);
    
    //Missiles
    //Missile1
    KeyFramedTexturedLightedMeshRenderablePtr missile1 = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/missile/missile.obj", "../../../model/missile/fireblue3.png");
    missile1->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 1, 0)), glm::vec3{1,1,1}).toMatrix());
    //custom material : turquoise
    const glm::vec3 ambientMissile = glm::vec3(0.1, 0.18725, 0.1745);	
    const glm::vec3 diffuseMissile = glm::vec3(0.396, 0.74151, 0.69102);
    const glm::vec3 specularMissile = glm::vec3(0.297254, 0.30829, 0.306678);
    float shininessMissile = 0.1f;
    missile1->setMaterial(MaterialPtr(new Material(ambientMissile, diffuseMissile, specularMissile, shininessMissile)));
    viewer.addRenderable(missile1);
    missile1Animation(missile1);
    
    //Missile0
    KeyFramedTexturedLightedMeshRenderablePtr missile0 = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/missile/missile.obj", "../../../model/missile/fireblue3.png");
    missile0->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 1, 0)), glm::vec3{1,1,1}).toMatrix());
    missile0->setMaterial(MaterialPtr(new Material(ambientMissile, diffuseMissile, specularMissile, shininessMissile)));
    viewer.addRenderable(missile0);
    missile0Animation(missile0);
    
    //Missile2
    KeyFramedTexturedLightedMeshRenderablePtr missile2 = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/missile/missile.obj", "../../../model/missile/fireblue3.png");
    missile2->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 1, 0)), glm::vec3{1,1,1}).toMatrix());
    missile2->setMaterial(MaterialPtr(new Material(ambientMissile, diffuseMissile, specularMissile, shininessMissile)));
    viewer.addRenderable(missile2);
    missile2Animation(missile2);
    
    //Missile3
    KeyFramedTexturedLightedMeshRenderablePtr missile3 = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/missile/missile.obj", "../../../model/missile/fireblue3.png");
    missile3->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 1, 0)), glm::vec3{1,1,1}).toMatrix());
    missile3->setMaterial(MaterialPtr(new Material(ambientMissile, diffuseMissile, specularMissile, shininessMissile)));
    viewer.addRenderable(missile3);
    missile3Animation(missile3);
    
    //Missile4
    KeyFramedTexturedLightedMeshRenderablePtr missile4 = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/missile/missile.obj", "../../../model/missile/fireblue3.png");
    missile4->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 1, 0)), glm::vec3{1,1,1}).toMatrix());
    missile4->setMaterial(MaterialPtr(new Material(ambientMissile, diffuseMissile, specularMissile, shininessMissile)));
    viewer.addRenderable(missile4);
    missile4Animation(missile4);
    
    //Missile5
    KeyFramedTexturedLightedMeshRenderablePtr missile5 = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/missile/missile.obj", "../../../model/missile/fireblue3.png");
    missile5->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 1, 0)), glm::vec3{1,1,1}).toMatrix());
    missile5->setMaterial(MaterialPtr(new Material(ambientMissile, diffuseMissile, specularMissile, shininessMissile)));
    viewer.addRenderable(missile5);
    missile5Animation(missile5);
    
    //Missile6
    KeyFramedTexturedLightedMeshRenderablePtr missile6 = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(textureShader, "../../../model/missile/missile.obj", "../../../model/missile/fireblue3.png");
    missile6->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 1, 0)), glm::vec3{1,1,1}).toMatrix());
    missile6->setMaterial(MaterialPtr(new Material(ambientMissile, diffuseMissile, specularMissile, shininessMissile)));
    viewer.addRenderable(missile6);
    missile6Animation(missile6);
    
    //Final Missile
    KeyFramedTexturedLightedMeshRenderablePtr missileF = std::make_shared<KeyFramedTexturedLightedMeshRenderable>(unlightedTextureShader, "../../../model/missile/finalMissileX.obj", "../../../model/missile/fireblueTransp2.png");
    missileF->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(-90.f), glm::vec3(0, 0, 1)), glm::vec3{1,1,1}).toMatrix());
    missileF->setMaterial(MaterialPtr(new Material(ambientMissile, diffuseMissile, specularMissile, shininessMissile)));
    //glMaterialfv(gl_emission, glow_color);
    viewer.addRenderable(missileF);
    missileFAnimation(missileF);
    
    //Final Missile Charging Sphere
    PointLightPtr sphereLight = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.6,0.6,0.9), glm::vec3(0.6,0.6,0.9), glm::vec3(0.6,0.6,0.9), 0.4, 5e-1, 0);
    viewer.addPointLight(sphereLight);
    TexturedMeshPointLightRenderablePtr sphereMF = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/missile/sphere.obj", "../../../model/missile/fireblueSquareTransp2.png", sphereLight);
    viewer.addRenderable(sphereMF);
    sphereMFAnimation(sphereMF);
    
    //Explosion
    //FlashPlanes
    //Flash1
    PointLightPtr flash1Light = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1,0.1,0.1), glm::vec3(0.1,0.1,0.1), glm::vec3(0.1,0.1,0.1), 1.0, 5e-1, 0);
    viewer.addPointLight(flash1Light);
    TexturedMeshPointLightRenderablePtr flash1 = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/explosion/plane.obj", "../../../model/explosion/f1p.png", flash1Light);
    flash1->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)), glm::vec3{1,1,1}).toMatrix());
    viewer.addRenderable(flash1);
    flashAnimation(flash1, 0.0);
    
    //Flash2
    PointLightPtr flash2Light = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1,0.1,0.1), glm::vec3(0.1,0.1,0.1), glm::vec3(0.1,0.1,0.1), 1.0, 5e-1, 0);
    viewer.addPointLight(flash2Light);
    TexturedMeshPointLightRenderablePtr flash2 = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/explosion/plane.obj", "../../../model/explosion/f2p.png", flash2Light);
    flash2->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)), glm::vec3{1,1,1}).toMatrix());
    flash2->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(45.f), glm::vec3(1, 0, 0)), glm::vec3{1,1,1}).toMatrix());
    viewer.addRenderable(flash2);
    flashAnimation(flash2, 0.005);
    
    //Flash3
    PointLightPtr flash3Light = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1,0.1,0.1), glm::vec3(0.1,0.1,0.1), glm::vec3(0.1,0.1,0.1), 1.0, 5e-1, 0);
    viewer.addPointLight(flash3Light);
    TexturedMeshPointLightRenderablePtr flash3 = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/explosion/plane.obj", "../../../model/explosion/f3p.png", flash3Light);
    flash3->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)), glm::vec3{1,1,1}).toMatrix());
    flash3->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(1, 0, 0)), glm::vec3{1,1,1}).toMatrix());
    viewer.addRenderable(flash3);
    flashAnimation(flash3, 0.01);
    
    //Flash4
    PointLightPtr flash4Light = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1,0.1,0.1), glm::vec3(0.1,0.1,0.1), glm::vec3(0.1,0.1,0.1), 1.0, 5e-1, 0);
    viewer.addPointLight(flash4Light);
    TexturedMeshPointLightRenderablePtr flash4 = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/explosion/plane.obj", "../../../model/explosion/f4p.png", flash4Light);
    flash4->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)), glm::vec3{1,1,1}).toMatrix());
    flash4->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(135.f), glm::vec3(1, 0, 0)), glm::vec3{1,1,1}).toMatrix());
    viewer.addRenderable(flash4);
    flashAnimation(flash4, 0.015);
    
    //FlashRond
    PointLightPtr flashRLight = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.1,0.1,0.1), glm::vec3(0.1,0.1,0.1), glm::vec3(0.1,0.1,0.1), 1.0, 5e-1, 0);
    viewer.addPointLight(flashRLight);
    TexturedMeshPointLightRenderablePtr flashR = std::make_shared<TexturedMeshPointLightRenderable>(transpTextureShader, "../../../model/explosion/plane.obj", "../../../model/explosion/fRt.png", flashRLight);
    flashR->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)), glm::vec3{1,1,1}).toMatrix());
    viewer.addRenderable(flashR);
    flashRAnimation(flashR);
    
    //FinScene
    PointLightPtr lumNoire = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 1.0, 5e-1, 0);
    viewer.addPointLight(lumNoire);
    TexturedMeshPointLightRenderablePtr flashFin = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/explosion/plane.obj", "../../../model/explosion/try.png", lumNoire);
    flashFin->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)), glm::vec3{1,1,1}).toMatrix());
    viewer.addRenderable(flashFin);
    sceneFinAnimation(flashFin);
    
    //Titres
    //Titre Debut
    PointLightPtr lumStart = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 1.0, 5e-1, 0);
    viewer.addPointLight(lumStart);
    TexturedMeshPointLightRenderablePtr titreDebut = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/explosion/plane.obj", "../../../model/titre/titreDT.png", lumStart);
    titreDebut->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)), glm::vec3{1,1,1}).toMatrix());
    viewer.addRenderable(titreDebut);
    titreDebutAnimation(titreDebut);
    
    //Titre Fin
    PointLightPtr lumEnd = std::make_shared<PointLight>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 1.0, 5e-1, 0);
    viewer.addPointLight(lumEnd);
    TexturedMeshPointLightRenderablePtr titreFin = std::make_shared<TexturedMeshPointLightRenderable>(unlightedTextureShader, "../../../model/explosion/plane.obj", "../../../model/titre/titreFT.png", lumEnd);
    titreFin->setLocalTransform(GeometricTransformation(glm::vec3{0,0,0}, glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)), glm::vec3{1,1,1}).toMatrix());
    viewer.addRenderable(titreFin);
    titreFinAnimation(titreFin);
    
    
    //Is the camera moving
    viewer.getCamera().setAnimation(true);

    viewer.startAnimation();
    viewer.setAnimationLoop(true, 34);
}

int main() 
{
	Viewer viewer(1280,720);
	initialize_scene(viewer);

	/*sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../../../music/Apollo13-wehaveaproblem.ogg"))
        return -1;
		
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();*/
	
	sf::Music music;
	if (!music.openFromFile("../../../music/star_wars_kazoo.ogg"))
		return -1; // error
	music.play();

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
    
    //fix camera in place while waiting for shuttle
    viewer.getCamera().setPosition(glm::vec3(0,3,-0.5));
    
    
    viewer.getCamera().addKeyframe(glm::vec3(-4,3.5,5),glm::vec3(-12,12,0),0);
    viewer.getCamera().addKeyframe(glm::vec3(-4,3.5,5),glm::vec3(-12,12,0),3);
    viewer.getCamera().addKeyframe(glm::vec3(-3.5,3,3),glm::vec3(-6,0,0),5);
    viewer.getCamera().addKeyframe(glm::vec3(-3,3,2),glm::vec3(0,0,0),6);
    
    //-6s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-40,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-40,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-40,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-40,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-40,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-35,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{-30,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}));
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
    											
    for(auto it=gtShuttle.begin() ; it<gtShuttle.end() ; ++it){
    	shuttle->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }
    gtShuttle.clear();
    				
    //shuttle comes into screen, goes to the left											
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
    //around first asteroid
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
    //goes to second one
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
    
    //around second one
    //15s
    gtShuttle.push_back(GeometricTransformation(glm::vec3{26.9,-8.5,5.5},
    											glm::angleAxis(glm::radians(-10.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-30.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{31.3,-6.5,5},
    											glm::angleAxis(glm::radians(15.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(-20.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    //transitioning towards missiles
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
    //first  missile
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
    	viewer.getCamera().addKeyframe((*it).getTranslation()+glm::vec3(-10,-(*it).getTranslation()[1],5),(*it).getTranslation()+glm::vec3(0,-(*it).getTranslation()[1],0),t);
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
    	viewer.getCamera().addKeyframe((*it).getTranslation()+glm::vec3(-10,-(*it).getTranslation()[1],5),(*it).getTranslation()+glm::vec3(0,-(*it).getTranslation()[1],0),t);
    	t+=0.3;
    }
    gtShuttle.clear();
    
    gtShuttle.push_back(GeometricTransformation(glm::vec3{107,6,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtShuttle.begin() ; it<gtShuttle.end() ; ++it){
    	shuttle->addParentTransformKeyframe(*it,t);
    	viewer.getCamera().addKeyframe((*it).getTranslation()+glm::vec3(-10,-(*it).getTranslation()[1],5),(*it).getTranslation()+glm::vec3(0,-(*it).getTranslation()[1],0),t);
    	t+=0.5;
    }
    gtShuttle.clear();
    
    //final missile
    gtShuttle.push_back(GeometricTransformation(glm::vec3{111,6,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    /*gtShuttle.push_back(GeometricTransformation(glm::vec3{115,4,0},
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
    											glm::vec3{1,1,1}));*/
    
    for(auto it=gtShuttle.begin() ; it<gtShuttle.end() ; ++it){
    	shuttle->addParentTransformKeyframe(*it,t);
    	viewer.getCamera().addKeyframe((*it).getTranslation()+glm::vec3(-10,-(*it).getTranslation()[1],5),(*it).getTranslation()+glm::vec3(0,-(*it).getTranslation()[1],0),t);
    	t+=0.9;
    }
    
    gtShuttle.clear();
    
    //destruction
    gtShuttle.push_back(GeometricTransformation(glm::vec3{111,6,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{111,6,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{0.1,0.1,0.1}));
    gtShuttle.push_back(GeometricTransformation(glm::vec3{160,6,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{0.1,0.1,0.1}));
    for(auto it=gtShuttle.begin() ; it<gtShuttle.end() ; ++it){
    	shuttle->addParentTransformKeyframe(*it,t);
    	//viewer.getCamera().addKeyframe((*it).getTranslation()+glm::vec3(-10,-(*it).getTranslation()[1],5),(*it).getTranslation()+glm::vec3(0,-(*it).getTranslation()[1],0),t);
    	t+=0.1;
    }
    
    gtShuttle.clear();											
    
    return t+1;
        
}

void fireAnimation(TexturedMeshPointLightRenderablePtr& fireRenderable, const float TIME_MAX){  
    for(float t=0.0;t<TIME_MAX;t+=0.2){
    	fireRenderable->addParentTransformKeyframe(GeometricTransformation(glm::vec3{0,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{1,1,1}), t);
    	fireRenderable->addParentTransformKeyframe(GeometricTransformation(glm::vec3{0,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{0.95,0.98,0.98}), t+0.1);
    }
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
    	t+=8;
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
    	t+=8;
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
    	t+=8;
    }
}


void meanGuyAnimation(KeyFramedTexturedLightedMeshRenderablePtr& meanie){
	
    std::vector<GeometricTransformation> gtMeanGuy;
    float t=0.0;
    
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::quat{0,0,0,0},
    											glm::vec3{0.5,0.5,0.5}));
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.5,0.5,0.5}));
    											
    for(auto it=gtMeanGuy.begin() ; it<gtMeanGuy.end() ; ++it){
    	meanie->addParentTransformKeyframe(*it,t);
    	t+=0.1;
    }
    
    gtMeanGuy.clear();
    

    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(72.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(144.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(216.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(360.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(72.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(144.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(216.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    gtMeanGuy.push_back(GeometricTransformation(glm::vec3{140,0,0},
    											glm::angleAxis(glm::radians(360.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
    											
    for(auto it=gtMeanGuy.begin() ; it<gtMeanGuy.end() ; ++it){
    	meanie->addParentTransformKeyframe(*it,t);
    	t+=8;
    }											
    
}

void missile0Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile){
	
    std::vector<GeometricTransformation> gtMissile;
    float t=21.0;
    														
   gtMissile.push_back(GeometricTransformation(glm::vec3{160,0,5},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));			
   gtMissile.push_back(GeometricTransformation(glm::vec3{10,0,5},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }	
    
}

void missile1Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile){
	
    std::vector<GeometricTransformation> gtMissile;
    float t=24.25;
    														
   gtMissile.push_back(GeometricTransformation(glm::vec3{160,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));			
   gtMissile.push_back(GeometricTransformation(glm::vec3{10,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }	
    
}

void missile2Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile){
	
    std::vector<GeometricTransformation> gtMissile;
    float t=25.25;
    														
   gtMissile.push_back(GeometricTransformation(glm::vec3{160,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));			
   gtMissile.push_back(GeometricTransformation(glm::vec3{10,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }	
    
}

void missile3Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile){
	
    std::vector<GeometricTransformation> gtMissile;
    float t=27.25;
    														
   gtMissile.push_back(GeometricTransformation(glm::vec3{160,-10,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));			
   gtMissile.push_back(GeometricTransformation(glm::vec3{10,-10,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }	
    
}

void missile4Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile){
	
    std::vector<GeometricTransformation> gtMissile;
    float t=27.75;
    														
   gtMissile.push_back(GeometricTransformation(glm::vec3{160,-10,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));			
   gtMissile.push_back(GeometricTransformation(glm::vec3{10,-10,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }	
    
}

void missile5Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile){
	
    std::vector<GeometricTransformation> gtMissile;
    float t=28.25;
    														
   gtMissile.push_back(GeometricTransformation(glm::vec3{160,-5,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));			
   gtMissile.push_back(GeometricTransformation(glm::vec3{10,-5,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }	
    
}

void missile6Animation(KeyFramedTexturedLightedMeshRenderablePtr& missile){
	
    std::vector<GeometricTransformation> gtMissile;
    float t=28.75;
    														
   gtMissile.push_back(GeometricTransformation(glm::vec3{160,-2,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));			
   gtMissile.push_back(GeometricTransformation(glm::vec3{10,-2,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }	
    
}

void missileFAnimation(KeyFramedTexturedLightedMeshRenderablePtr& missile){
	
    std::vector<GeometricTransformation> gtMissile;
    float t=0.0;
    														
   gtMissile.push_back(GeometricTransformation(glm::vec3{125,-0.4,0},
    											glm::angleAxis(glm::radians(-23.5f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.0001,0.0001,0.0001}));
   
   for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=30.15;
    }
    
   gtMissile.clear();
   
   gtMissile.push_back(GeometricTransformation(glm::vec3{125,-0.4,0},
    											glm::angleAxis(glm::radians(-23.5f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.0001,0.0001,0.0001})); 								
   gtMissile.push_back(GeometricTransformation(glm::vec3{125,-0.4,0},
    											glm::angleAxis(glm::radians(-23.5f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.06,0.04,0.04}));
    
    for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }	 				
   
   /*
   gitMissile.clear();
   				
   gtMissile.push_back(GeometricTransformation(glm::vec3{125,-0.4,0},
    											glm::angleAxis(glm::radians(-23.5f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.06,0.04,0.04}));
   
   for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }*/
    
   gtMissile.clear();
   
   gtMissile.push_back(GeometricTransformation(glm::vec3{125,-0.4,0},
    											glm::angleAxis(glm::radians(-23.5f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.0001,0.0001,0.0001})); 								
   gtMissile.push_back(GeometricTransformation(glm::vec3{160,-0.4,0},
    											glm::angleAxis(glm::radians(-23.5f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.001,0.001,0.001}));
    
    for(auto it=gtMissile.begin() ; it<gtMissile.end() ; ++it){
    	missile->addParentTransformKeyframe(*it,t);
    	t+=0.5;
    }
    
}

void sphereMFAnimation(TexturedMeshPointLightRenderablePtr& sphere){
	
    std::vector<GeometricTransformation> gtSphere;
    float t=0.0;
    														
   gtSphere.push_back(GeometricTransformation(glm::vec3{120,-0.4,0},
    											glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   
   for(auto it=gtSphere.begin() ; it<gtSphere.end() ; ++it){
    	sphere->addParentTransformKeyframe(*it,t);
    	t+=29.25;
   }
   
   gtSphere.clear();
   
   gtSphere.push_back(GeometricTransformation(glm::vec3{120,-0.4,0},
    											glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   gtSphere.push_back(GeometricTransformation(glm::vec3{125,-0.4,0},
    											glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001})); 								
   gtSphere.push_back(GeometricTransformation(glm::vec3{125,-0.4,0},
    											glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.001,0.001,0.001}));
    for(auto it=gtSphere.begin() ; it<gtSphere.end() ; ++it){
    	sphere->addParentTransformKeyframe(*it,t);
    	t+=0.3;
    }	
    
    gtSphere.clear();
    
    gtSphere.push_back(GeometricTransformation(glm::vec3{125,-0.4,0},
    											glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.001,0.001,0.001})); 								
    gtSphere.push_back(GeometricTransformation(glm::vec3{111,6,0},
    											glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
    for(auto it=gtSphere.begin() ; it<gtSphere.end() ; ++it){
    	sphere->addParentTransformKeyframe(*it,t);
    	t+=0.01;
    }
    
}

void flashAnimation(TexturedMeshPointLightRenderablePtr& flash, float d){
	
    std::vector<GeometricTransformation> gtFlash;
    float t=0.0;
    														
   
   gtFlash.push_back(GeometricTransformation(glm::vec3{140,-0.4,-10},
    											glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   
   for(auto it=gtFlash.begin() ; it<gtFlash.end() ; ++it){
    	flash->addParentTransformKeyframe(*it,t);
    	t+= (30.15 + d);
    }
    
   gtFlash.clear();
   
   gtFlash.push_back(GeometricTransformation(glm::vec3{140,-0.4,-10},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   gtFlash.push_back(GeometricTransformation(glm::vec3{111,6,0},
    											glm::angleAxis(glm::radians(45.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.0001,0.0001,0.0001}));
   
   for(auto it=gtFlash.begin() ; it<gtFlash.end() ; ++it){
    	flash->addParentTransformKeyframe(*it,t);
    	t+= 0.1;
    }
    
   gtFlash.clear();
   
   gtFlash.push_back(GeometricTransformation(glm::vec3{110,5,0},
    											glm::angleAxis(glm::radians(45.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.5,0.5,0.5}));
   gtFlash.push_back(GeometricTransformation(glm::vec3{110,5,0},
    											glm::angleAxis(glm::radians(45.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.01,0.01,0.01}));
   gtFlash.push_back(GeometricTransformation(glm::vec3{110,5,0},
    											glm::angleAxis(glm::radians(45.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   gtFlash.push_back(GeometricTransformation(glm::vec3{160,6,0},
    											glm::angleAxis(glm::radians(45.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   
   for(auto it=gtFlash.begin() ; it<gtFlash.end() ; ++it){
    	flash->addParentTransformKeyframe(*it,t);
    	t+= 0.005;
    }
   
}



void flashRAnimation(TexturedMeshPointLightRenderablePtr& flash){
	
    std::vector<GeometricTransformation> gtFlash;
    float t=0.0;
    														
   gtFlash.push_back(GeometricTransformation(glm::vec3{140,-0.4,-10},
    											glm::angleAxis(glm::radians(90.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   
   for(auto it=gtFlash.begin() ; it<gtFlash.end() ; ++it){
    	flash->addParentTransformKeyframe(*it,t);
    	t+= 30.25;
    }
    
   gtFlash.clear();
   
   gtFlash.push_back(GeometricTransformation(glm::vec3{140,-0.4,-10},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   gtFlash.push_back(GeometricTransformation(glm::vec3{111,6,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.0001,0.0001,0.0001}));
   
   for(auto it=gtFlash.begin() ; it<gtFlash.end() ; ++it){
    	flash->addParentTransformKeyframe(*it,t);
    	t+= 0.1;
    }
    
   gtFlash.clear();
   
   gtFlash.push_back(GeometricTransformation(glm::vec3{110,5,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.01,0.01,0.01}));
   gtFlash.push_back(GeometricTransformation(glm::vec3{110,5,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.4,0.4,0.4}));
   gtFlash.push_back(GeometricTransformation(glm::vec3{110,5,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.6,0.6,0.6}));
   gtFlash.push_back(GeometricTransformation(glm::vec3{110,5,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.8,0.8,0.8}));
   gtFlash.push_back(GeometricTransformation(glm::vec3{110,5,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
   											glm::vec3{1.0,1.0,1.0}));
   //gtFlash.push_back(GeometricTransformation(glm::vec3{160,5,0},
   // 											glm::angleAxis(glm::radians(45.f), glm::vec3(0, 0, 1)),
   // 											glm::vec3{0.01,0.01,0.01}));
   
   for(auto it=gtFlash.begin() ; it<gtFlash.end() ; ++it){
    	flash->addParentTransformKeyframe(*it,t);
    	t+= 0.5;
    }
   
}

void moonAnimation(AsteroidRenderablePtr& moon){
    std::vector<GeometricTransformation> gtMoon;
    float t=0.0;
    
    gtMoon.push_back(GeometricTransformation(glm::vec3{85,35,5},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0.7, 0, 0.7)),
    											glm::vec3{1,1,1}));
    gtMoon.push_back(GeometricTransformation(glm::vec3{85,35,5},
    											glm::angleAxis(glm::radians(72.f), glm::vec3(0.7, 0, 0.7)),
    											glm::vec3{1,1,1}));
    gtMoon.push_back(GeometricTransformation(glm::vec3{85,35,5},
    											glm::angleAxis(glm::radians(144.f), glm::vec3(0.7, 0, 0.7)),
    											glm::vec3{1,1,1}));
    gtMoon.push_back(GeometricTransformation(glm::vec3{85,35,5},
    											glm::angleAxis(glm::radians(216.f), glm::vec3(0.7, 0, 0.7)),
    											glm::vec3{1,1,1}));
    gtMoon.push_back(GeometricTransformation(glm::vec3{85,35,5},
    											glm::angleAxis(glm::radians(360.f), glm::vec3(0.7, 0, 0.7)),
    											glm::vec3{1,1,1}));
    
    for(auto it=gtMoon.begin() ; it<gtMoon.end() ; ++it){
    	moon->addParentTransformKeyframe(*it,t);
    	t+=8;
    }
}

void sceneFinAnimation(TexturedMeshPointLightRenderablePtr& fin){
	
    std::vector<GeometricTransformation> gtFin;
    float t=0.0;
    
   /* 
   gtFin.push_back(GeometricTransformation(glm::vec3{0,0,0},
    											glm::angleAxis(glm::radians(-45.f), glm::vec3(0, 0, 1)),
    											glm::vec3{7,7,7}));
   gtFin.push_back(GeometricTransformation(glm::vec3{0,0,0},
    											glm::angleAxis(glm::radians(-45.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.001,0.001,0.001}));
   for(auto it=gtFin.begin() ; it<gtFin.end() ; ++it){
    	fin->addParentTransformKeyframe(*it,t);
    	t+= 3.f;
    }
    
   gtFin.clear();
   
   gtFin.push_back(GeometricTransformation(glm::vec3{0,0,0},
    											glm::angleAxis(glm::radians(-45.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.001,0.001,0.001}));										
   gtFin.push_back(GeometricTransformation(glm::vec3{140,-0.4,-10},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   
   for(auto it=gtFin.begin() ; it<gtFin.end() ; ++it){
    	fin->addParentTransformKeyframe(*it,t);
    	t+= 0.1;
    }
    
   gtFin.clear();
    														
   gtFin.push_back(GeometricTransformation(glm::vec3{140,-0.4,-10},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   
   for(auto it=gtFin.begin() ; it<gtFin.end() ; ++it){
    	fin->addParentTransformKeyframe(*it,t);
    	t+= 22.8;
    }*/
    														
   gtFin.push_back(GeometricTransformation(glm::vec3{140,-0.4,-10},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   
   for(auto it=gtFin.begin() ; it<gtFin.end() ; ++it){
    	fin->addParentTransformKeyframe(*it,t);
    	t+= 34.25;
    }
    
   gtFin.clear();
   
   gtFin.push_back(GeometricTransformation(glm::vec3{140,-0.4,10},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   gtFin.push_back(GeometricTransformation(glm::vec3{110,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.0001,0.0001,0.0001}));
   
   for(auto it=gtFin.begin() ; it<gtFin.end() ; ++it){
    	fin->addParentTransformKeyframe(*it,t);
    	t+= 0.1;
    }
    
   gtFin.clear();
   
   gtFin.push_back(GeometricTransformation(glm::vec3{110,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.01,0.01,0.01}));
   gtFin.push_back(GeometricTransformation(glm::vec3{110,0,0},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{15,15,15}));
   
   for(auto it=gtFin.begin() ; it<gtFin.end() ; ++it){
    	fin->addParentTransformKeyframe(*it,t);
    	t+= 2.5;
    }
   
}

void titreDebutAnimation(TexturedMeshPointLightRenderablePtr& titre){
	
    std::vector<GeometricTransformation> gtDebut;
    float t=0.0;
    
    
   gtDebut.push_back(GeometricTransformation(glm::vec3{-7,7,2},
    											glm::angleAxis(glm::radians(-67.f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(180.f), glm::vec3(1, 1, 0)),
    											glm::vec3{0.35,0.35,0.35}));
   gtDebut.push_back(GeometricTransformation(glm::vec3{-7,7,2},
    											glm::angleAxis(glm::radians(-67.f), glm::vec3(0, 0, 1)) *  glm::angleAxis(glm::radians(180.f), glm::vec3(1, 1, 0)),
    											glm::vec3{0.2,0.2,0.2}));
   gtDebut.push_back(GeometricTransformation(glm::vec3{-7,7,2},
    											glm::angleAxis(glm::radians(-67.f), glm::vec3(0, 0, 1)) *  glm::angleAxis(glm::radians(180.f), glm::vec3(1, 1, 0)),
    											glm::vec3{0.001,0.001,0.001}));
   gtDebut.push_back(GeometricTransformation(glm::vec3{-7,7,2},
    											glm::angleAxis(glm::radians(-67.f), glm::vec3(0, 0, 1)) *  glm::angleAxis(glm::radians(180.f), glm::vec3(1, 1, 0)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   for(auto it=gtDebut.begin() ; it<gtDebut.end() ; ++it){
    	titre->addParentTransformKeyframe(*it,t);
    	t+= 2.f;
    }
    
   gtDebut.clear();
   
   gtDebut.push_back(GeometricTransformation(glm::vec3{0,0,10},
    											glm::angleAxis(glm::radians(180.f), glm::vec3(1, 0, 0)),
    											glm::vec3{0.001,0.001,0.001}));										
   gtDebut.push_back(GeometricTransformation(glm::vec3{140,20,-30},
    											glm::angleAxis(glm::radians(0.f), glm::vec3(0, 0, 1)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   
   for(auto it=gtDebut.begin() ; it<gtDebut.end() ; ++it){
    	titre->addParentTransformKeyframe(*it,t);
    	t+= 0.1;
    }
   
}

void titreFinAnimation(TexturedMeshPointLightRenderablePtr& titre){
	
    std::vector<GeometricTransformation> gtFin;
    float t=0.0;
    
    
   gtFin.push_back(GeometricTransformation(glm::vec3{112,0,0},
    											glm::angleAxis(glm::radians(180.f), glm::vec3(1, 0, 0)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   for(auto it=gtFin.begin() ; it<gtFin.end() ; ++it){
    	titre->addParentTransformKeyframe(*it,t);
    	t+= 30.75;
    }
    
   gtFin.clear();
   
   gtFin.push_back(GeometricTransformation(glm::vec3{112,0,0},
    											glm::angleAxis(glm::radians(180.f), glm::vec3(1, 0, 0)),
    											glm::vec3{0.00001,0.00001,0.00001}));
   gtFin.push_back(GeometricTransformation(glm::vec3{112,0,0},
    											glm::angleAxis(glm::radians(180.f), glm::vec3(1, 0, 0)),
    											glm::vec3{0.001,0.001,0.001}));
   //gtFin.push_back(GeometricTransformation(glm::vec3{110,0,0},
   // 											glm::angleAxis(glm::radians(180.f), glm::vec3(1, 0, 0)),
   // 											glm::vec3{0.2,0.2,0.2}));
   //gtFin.push_back(GeometricTransformation(glm::vec3{110,0,0},
   // 											glm::angleAxis(glm::radians(180.f), glm::vec3(1, 0, 0)),
   // 											glm::vec3{0.35,0.35,0.35}));
   gtFin.push_back(GeometricTransformation(glm::vec3{112,0,0},
    											glm::angleAxis(glm::radians(180.f), glm::vec3(1, 0, 0)),
    											glm::vec3{0.7,0.7,0.7}));
   gtFin.push_back(GeometricTransformation(glm::vec3{112,0,0},
    											glm::angleAxis(glm::radians(180.f), glm::vec3(1, 0, 0)),
    											glm::vec3{1,1,1}));
   
   for(auto it=gtFin.begin() ; it<gtFin.end() ; ++it){
    	titre->addParentTransformKeyframe(*it,t);
    	t+= 1.f;
    }
   
}



