//
// Created by Carlos Arauz on 22.11.17.
//
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "util/Shader.h"




Shader::Shader( const GLchar * vertex_file_path, const GLchar * fragment_file_path ) : Program(_Program)
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    // retreive shaders ////////////////////////////////////////////////////////////////////////////
    std::ios_base::iostate  exceptionMask;
    std::string             vertShaderCode;
    std::string             fragShaderCode;
    std::ifstream           vertShaderFile;
    std::ifstream           fragShaderFile;

    exceptionMask = vertShaderFile.exceptions( ) | std::ios::failbit;
    vertShaderFile.exceptions( exceptionMask );

    exceptionMask = fragShaderFile.exceptions( ) | std::ios::failbit;
    fragShaderFile.exceptions( exceptionMask );

    try
    {
        // open files
        vertShaderFile.open( vertex_file_path );
        fragShaderFile.open( fragment_file_path );

        // read file's buffer to string streams
        std::stringstream vertStringStream, fragStringStream;
        vertStringStream << vertShaderFile.rdbuf( );
        fragStringStream << fragShaderFile.rdbuf( ) ;

        // close files
        vertShaderFile.close( );
        fragShaderFile.close( );

        // convert string stream to string
        vertShaderCode = vertStringStream.str( );
        fragShaderCode = fragStringStream.str( );
    }
    catch ( const std::ifstream::failure & e )
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const GLchar *vertSourcePointer = vertShaderCode.c_str( );
    const GLchar *fragSourcePointer = fragShaderCode.c_str( );

    // compile shaders /////////////////////////////////////////////////////////////////////////////
    GLuint vertShaderID;
    GLuint fragShaderID;
    GLint  success;
    GLint  infoLogLength;

    //// vertex shader
    vertShaderID = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertShaderID, 1, &vertSourcePointer, nullptr ) ;
    glCompileShader( vertShaderID );

    glGetShaderiv( vertShaderID, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderiv( vertShaderID, GL_INFO_LOG_LENGTH, &infoLogLength );
        std::vector<char> vertShaderErrorMessage( static_cast<unsigned long>(infoLogLength + 1) );
        glGetShaderInfoLog( vertShaderID, infoLogLength, nullptr, &vertShaderErrorMessage[0] );
        std::cout << &vertShaderErrorMessage[0] << std::endl;
    }

    //// fragment shader
    fragShaderID = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragShaderID, 1, &fragSourcePointer, nullptr );
    glCompileShader( fragShaderID );

    glGetShaderiv( fragShaderID, GL_COMPILE_STATUS, &success );
    if( !success )
    {
        glGetShaderiv( fragShaderID, GL_INFO_LOG_LENGTH, &infoLogLength );
        std::vector<char> fragShaderErrorMessage( static_cast<unsigned long>(infoLogLength + 1) );
        glGetShaderInfoLog( fragShaderID, infoLogLength, nullptr, &fragShaderErrorMessage[0] );
        std::cout << &fragShaderErrorMessage[0] << std::endl;
    }

    // shader program //////////////////////////////////////////////////////////////////////////////
    this->_Program = glCreateProgram( );
    glAttachShader( this->_Program, vertShaderID );
    glAttachShader( this->_Program, fragShaderID );
    glLinkProgram( this->_Program );

    glGetProgramiv( this->_Program, GL_LINK_STATUS, &success );
    if( !success )
    {
        glGetProgramiv( this->_Program, GL_INFO_LOG_LENGTH, &infoLogLength );
        std::vector<char> programmLinkErrorMessage(static_cast<unsigned long>(infoLogLength + 1) );
        glGetProgramInfoLog( this->_Program, infoLogLength, nullptr, &programmLinkErrorMessage[0] );
        std::cout << &programmLinkErrorMessage[0] << std::endl;
    }

    // delete shaders: shaders are already linked into the program /////////////////////////////////
    glDeleteShader( vertShaderID );
    glDeleteShader( fragShaderID );
}
// Shader( const GLchar *, const GLchar * ) ////////////////////////////////////////////////////////



void Shader::use( )
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUseProgram( this->_Program );
}
// Shader::user( ) /////////////////////////////////////////////////////////////////////////////////



void Shader::setBool( const std::string &name, GLboolean value ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniform1i( glGetUniformLocation( _Program, name.c_str() ), static_cast<GLint>( value ) );
}
// Shader::setBool( const std::string &, GLboolean ) const /////////////////////////////////////////



void Shader::setInt( const std::string &name, GLint value ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniform1i( glGetUniformLocation( _Program, name.c_str() ), value );
}
// Shader::setInt( const std::string &, GLint ) const //////////////////////////////////////////////



void Shader::setFloat( const std::string &name, GLfloat value ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniform1f(glGetUniformLocation(_Program, name.c_str() ), value);
}
// Shader::setFloat( const std::string &, GLfloat ) const //////////////////////////////////////////



void Shader::setVector( const std::string &name, GLfloat x, GLfloat y ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniform2f( glGetUniformLocation( _Program, name.c_str() ), x ,y );
}
// void Shader::setVector( const std::string &, GLfloat, GLfloat ) const ///////////////////////////



void Shader::setVector( const std::string &name, GLfloat x, GLfloat y, GLfloat z ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniform3f( glGetUniformLocation( _Program, name.c_str() ), x ,y, z );
}
// void Shader::setVector( const std::string &, GLfloat, GLfloat, GLfloat ) const //////////////////



void Shader::setVector( const std::string &name, GLfloat x, GLfloat y, GLfloat z, GLfloat w ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniform4f( glGetUniformLocation( _Program, name.c_str() ), x ,y, z, w );
}
// void Shader::setVector( const std::string &, GLfloat, GLfloat, GLfloat, GLfloat ) const /////////



void Shader::setVector( const std::string &name, const glm::vec2 &value ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniform2fv( glGetUniformLocation( _Program, name.c_str( ) ), 1, glm::value_ptr( value ) );
}
// Shader::setVector( const std::string &, const glm::vec2 & ) const ///////////////////////////////



void Shader::setVector( const std::string &name, const glm::vec3 &value ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniform3fv( glGetUniformLocation( _Program, name.c_str( ) ), 1, glm::value_ptr( value ) );
}
// Shader::setVector( const std::string &, const glm::vec3 & ) const ///////////////////////////////



void Shader::setVector( const std::string &name, const glm::vec4 &value ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniform4fv( glGetUniformLocation( _Program, name.c_str( ) ), 1, glm::value_ptr( value ) );
}
// Shader::setVector( const std::string &, const glm::vec4 & ) const ///////////////////////////////



void Shader::setMatrix( const std::string &name, const glm::mat2 &value ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniformMatrix2fv( glGetUniformLocation( _Program, name.c_str( ) ), 1, GL_FALSE, glm::value_ptr( value ) );
}
// Shader::setMatrix4fv( const std::string &, const glm::mat2 & ) const ////////////////////////////



void Shader::setMatrix( const std::string &name, const glm::mat3 &value ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniformMatrix3fv( glGetUniformLocation( _Program, name.c_str( ) ), 1, GL_FALSE, glm::value_ptr( value ) );
}
// Shader::setMatrix4fv( const std::string &, const glm::mat3 & ) const ////////////////////////////



void Shader::setMatrix( const std::string &name, const glm::mat4 &value ) const
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUniformMatrix4fv( glGetUniformLocation( _Program, name.c_str( ) ), 1, GL_FALSE, glm::value_ptr( value ) );
}
// Shader::setMatrix4fv( const std::string &, const glm::mat4 & ) const ////////////////////////////
