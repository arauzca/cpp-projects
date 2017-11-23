//
// Created by Carlos Arauz on 22.11.17.
//
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "../inc/Shader.h"


Shader::Shader( const GLchar * vertex_file_path, const GLchar * fragment_file_path )
///////////////////////////////////////////////////////////////////////////////////////////////////
{
    // retreive shaders ///////////////////////////////////////////////////////////////////////////
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

    // compile shaders ////////////////////////////////////////////////////////////////////////////
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

    // shader program /////////////////////////////////////////////////////////////////////////////
    this->Program = glCreateProgram( );
    glAttachShader( this->Program, vertShaderID );
    glAttachShader( this->Program, fragShaderID );
    glLinkProgram( this->Program );

    glGetProgramiv( this->Program, GL_LINK_STATUS, &success );
    if( !success )
    {
        glGetProgramiv( this->Program, GL_INFO_LOG_LENGTH, &infoLogLength );
        std::vector<char> programmLinkErrorMessage(static_cast<unsigned long>(infoLogLength + 1) );
        glGetProgramInfoLog( this->Program, infoLogLength, nullptr, &programmLinkErrorMessage[0] );
        std::cout << &programmLinkErrorMessage[0] << std::endl;
    }

    // delete shaders: shaders are already linked into the program ////////////////////////////////
    glDeleteShader( vertShaderID );
    glDeleteShader( fragShaderID );
}
// Shader(const GLchar *, const GLchar *) /////////////////////////////////////////////////////////


GLuint Shader::getProgram( )
///////////////////////////////////////////////////////////////////////////////////////////////////
{
    return this->Program;
}
// Shader::getProgram( ) //////////////////////////////////////////////////////////////////////////


void Shader::use( )
///////////////////////////////////////////////////////////////////////////////////////////////////
{
    glUseProgram( this->Program );
}
// Shader::user( ) ////////////////////////////////////////////////////////////////////////////////
