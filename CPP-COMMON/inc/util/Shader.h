//
// Created by Carlos Arauz on 22.11.17.
//
#pragma once

#include <string>

// Include GLEW ////////////////////////////////////////////////////////////////////////////////////
#include <GL/glew.h>

// Include GLM /////////////////////////////////////////////////////////////////////////////////////
#include <glm/glm.hpp>


class Shader {
////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    // program ID, private so that it cannot be modified ///////////////////////////////////////////
    GLuint  _Program;

public:
    // constructor reads and builds the shader /////////////////////////////////////////////////////
    Shader( const GLchar *, const GLchar * );


    // activates the shader ////////////////////////////////////////////////////////////////////////
    void    use( );

    // utility uniform function
    void setBool( const std::string &, GLboolean ) const;
    void setInt( const std::string &, GLint ) const;
    void setFloat( const std::string &, GLfloat ) const;

    void setVector( const std::string &, GLfloat, GLfloat ) const;
    void setVector( const std::string &, GLfloat, GLfloat, GLfloat ) const;
    void setVector( const std::string &, GLfloat, GLfloat, GLfloat, GLfloat ) const;
    void setVector( const std::string &, const glm::vec2 & ) const;
    void setVector( const std::string &, const glm::vec3 & ) const;
    void setVector( const std::string &, const glm::vec4 & ) const;

    void setMatrix( const std::string &, const glm::mat2 & ) const;
    void setMatrix( const std::string &, const glm::mat3 & ) const;
    void setMatrix( const std::string &, const glm::mat4 & ) const;

    // public reference to the program ID, so that it is read-only /////////////////////////////////
    const GLuint &Program;
};
// class Shader ////////////////////////////////////////////////////////////////////////////////////
