#include "./../include/Camera.hpp"
#include <iostream>

#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/compatibility.hpp>

using namespace std;

Camera::Camera()
    : m_view{ glm::lookAt( glm::vec3{0, 0, -5}, glm::vec3{}, glm::vec3{0,1,0}) },
      m_fov{ 1.04f }, m_ratio{ 1.0f }, m_znear{ 1.0f }, m_zfar{ 100.0f },
      m_mouseBehavior{ ARCBALL_BEHAVIOR }, is_animated{ false }
{}

Camera::~Camera()
{

}

void Camera::animate(float time)
{
	if(is_animated){
		glm::vec3 pos = glm::vec3(0,0,0);
		glm::vec3 target = glm::vec3(10,0,0);	
		
		if( !m_keyframes.empty() )
		{
		    //Handle the case where the time parameter is outside the keyframes time scope.
		    std::map< float, std::pair<glm::vec3, glm::vec3> >::const_iterator itFirstFrame = m_keyframes.begin();
		    std::map< float, std::pair<glm::vec3, glm::vec3> >::const_reverse_iterator itLastFrame = m_keyframes.rbegin();
		    if( time <= itFirstFrame->first ){
		    	pos=itFirstFrame->second.first;
		    	target=itFirstFrame->second.second;
		    }else if( time >= itLastFrame->first ){
		    	pos=itLastFrame->second.first;
		    	target=itLastFrame->second.second;
			}else{
				//Get keyframes surrounding the time parameter
				std::array< Keyframe, 2 > result = getBoundingKeyframes( time );

				//Compute the interpolating factor based on the time parameter and the surrounding keyframes times.
				float factor = (time-result[0].first)/(result[1].first-result[0].first);

				pos = glm::lerp(result[0].second.first,result[1].second.first,factor);
				target = glm::lerp(result[0].second.second,result[1].second.second,factor);

		    }
		}
		
		setViewMatrix(glm::lookAt(pos, target, glm::vec3(0,0,1)));
    }
}

void Camera::setAnimation(bool isAnimated){
	is_animated=isAnimated;
}

void Camera::addKeyframe( const glm::vec3& pos, const glm::vec3& target, float time )
{
	m_keyframes.insert( std::make_pair(time, std::make_pair(pos, target) ) );
}

std::array< Camera::Keyframe, 2 > Camera::getBoundingKeyframes( float time ) const
{
    std::array< Keyframe, 2 > result{ std::make_pair(0, std::make_pair(glm::vec3(0,0,0), glm::vec3(1,0,0))), std::make_pair(0, std::make_pair(glm::vec3(0,0,0), glm::vec3(1,0,0))) };
    std::map< float, std::pair<glm::vec3, glm::vec3> >::const_iterator upper = m_keyframes.upper_bound(time);
    std::map< float, std::pair<glm::vec3, glm::vec3> >::const_iterator lower = std::prev(upper);
    std::map< float, std::pair<glm::vec3, glm::vec3> >::const_iterator end = m_keyframes.end();
    if(upper != end && lower != end )
    {
        result[0] = *lower;
        result[1] = *upper;
    }
    return result;
}

const glm::mat4& Camera::viewMatrix() const
{
    return m_view;
}

void Camera::setViewMatrix(const glm::mat4& view)
{
    m_view = view;
}

glm::vec3 Camera::getPosition() const
{
    return -glm::vec3( m_view[3] ) * glm::mat3( m_view );
}

glm::vec3 Camera::getRight() const
{
    return glm::vec3( m_view[0][0], m_view[1][0], m_view[2][0] );
}

glm::vec3 Camera::getUp() const
{
    return glm::vec3( m_view[0][1], m_view[1][1], m_view[2][1] );
}

glm::vec3 Camera::getForward() const
{
    return glm::vec3( -m_view[0][2], -m_view[1][2], -m_view[2][2] );
}

void Camera::setPosition( const glm::vec3& pos )
{
    for( int i = 0; i < 3; ++ i )
    {
        m_view[3][i] = float(0);
        for( int j = 0; j < 3; ++ j )
        {
            m_view[3][i] -= m_view[j][i] * pos[j];
        }
    }
}

void Camera::setRight( const glm::vec3& right )
{
    glm::vec3 minus_pos = glm::vec3( m_view[3] ) * glm::mat3( m_view );
    m_view[0][0] = right.x;
    m_view[1][0] = right.y;
    m_view[2][0] = right.z;
    m_view[3][0] = dot( right, minus_pos );
}

void Camera::setUp( const glm::vec3& up )
{
  glm::vec3 minus_pos = glm::vec3( m_view[3] ) * glm::mat3( m_view );
  m_view[0][1] = up.x;
  m_view[1][1] = up.y;
  m_view[2][1] = up.z;
  m_view[3][1] = dot( up, minus_pos );
}

void Camera::setForward( const glm::vec3& forward )
{
  glm::vec3 pos = -glm::vec3( m_view[3] ) * glm::mat3( m_view );
  m_view[0][0] = -forward.x;
  m_view[1][0] = -forward.y;
  m_view[2][0] = -forward.z;
  m_view[3][0] = dot( forward, pos );
}

const glm::mat4& Camera::projectionMatrix() const
{
    return m_projection;
}

void Camera::setProjectionMatrix(const glm::mat4& projection)
{
    m_projection = projection;
}

float Camera::fov() const
{
    return m_fov;
}

float Camera::ratio() const
{
    return m_ratio;
}

float Camera::znear() const
{
    return m_znear;
}

float Camera::zfar() const
{
    return m_zfar;
}

void Camera::setFov( const float& v )
{
    m_fov = v;
    m_projection = glm::perspective( m_fov, m_ratio, m_znear, m_zfar );
}

void Camera::setRatio( const float& v )
{
    m_ratio = v;
    m_projection = glm::perspective( m_fov, m_ratio, m_znear, m_zfar );
}

void Camera::setZfar( const float& v )
{
    m_zfar = v;
    m_projection = glm::perspective( m_fov, m_ratio, m_znear, m_zfar );
}

void Camera::setZnear( const float& v )
{
    m_znear = v;
    m_projection = glm::perspective( m_fov, m_ratio, m_znear, m_zfar );
}

Camera::CAMERA_MOUSE_BEHAVIOR Camera::getMouseBehavior() const
{
    return m_mouseBehavior;
}

void Camera::setMouseBehavior( const CAMERA_MOUSE_BEHAVIOR& v )
{
    m_mouseBehavior = v;
    if( m_mouseBehavior == ARCBALL_BEHAVIOR )
      {
        glm::vec3 pos = getPosition();
        glm::vec3 up = getUp();
        m_view = glm::lookAt(
            getPosition(),
            glm::vec3{},
            getUp());
      }
}

void Camera::update( float dx, float dy )
{
    switch( m_mouseBehavior )
    {
    case ARCBALL_BEHAVIOR:
    {
        glm::mat4 rotation = glm::rotate( glm::mat4( glm::mat3(m_view) ), dx, getUp() );
        rotation = glm::rotate( rotation, dy, getRight() );

        m_view[0] = rotation[0];
        m_view[1] = rotation[1];
        m_view[2] = rotation[2];

        setPosition( -glm::vec3(m_view[3]) * glm::mat3(rotation) );
    }
        break;

    case SPACESHIP_BEHAVIOR:
    {
        const float cx = float( std::cos( dx ) );
        const float sx = float( std::sin( dx ) );
        const float cy = float( std::cos( dy ) );
        const float sy = float( std::sin( dy ) );

        glm::mat3 rotation = glm::mat3( m_view );
        glm::vec3 minus_pos = glm::vec3( m_view[3] ) * rotation;
        // build a rotation matrix to apply to the current rotation:
        //
        rotation = glm::mat3(
                    glm::vec3( cx, sx*sy,-sx*cy),
                    glm::vec3(  0,    cy,    sy),
                    glm::vec3( sx,-cx*sy, cx*cy) ) *rotation;
        for( int col = 0; col < 3; ++ col )
            for( int lin = 0; lin < 3; ++ lin )
            {
                m_view[col][lin] = rotation[col][lin];
            }
        m_view[3][0] = dot( minus_pos, getRight() );
        m_view[3][1] = dot( minus_pos, getUp() );
        m_view[3][2] = dot( minus_pos, -getForward() );
    }
        break;

    default:
        assert(false);
    }
}
