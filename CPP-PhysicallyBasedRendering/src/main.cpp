//
// Created by Carlos Arauz on 22.11.17.
//


// include GLEW
#include <GL/glew.h>


// include GLFW
#include <GLFW/glfw3.h>


// include GLM mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// include utility libraries
#include <util/Shader.h>
#include <util/Camera.h>
#include <util/Texture.h>
#include <util/Mesh.h>


// system includes
#include <iostream>
#include <vector>


// Function prototypes
void framebuffer_size_callback( GLFWwindow * window, int width, int height );
void mouse_callback( GLFWwindow * window, double xpos, double ypos );
void scroll_callback( GLFWwindow * window, double xoffset, double yoffset );
void processInput( GLFWwindow * window );

void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );
void renderSphere( );


// Properties
const GLuint SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;


// Camera
Camera camera (glm::vec3( 0.0f, 0.0f, 3.0f ));
GLfloat lastX = 800.0f / 2.0f;
GLfloat lastY = 600.0f / 2.0f;


bool firstMouse = true;
bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_SAMPLES, 4 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#ifdef __APPLE__
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Physically Based Rendering", nullptr, nullptr );

    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );
    glfwSetCursorPosCallback( window, mouse_callback );
    glfwSetScrollCallback( window, scroll_callback );


    // GLFW Options
    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );


    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }


    // OpenGL options
    glEnable( GL_DEPTH_TEST );

    // Setup and compile our shaders
    Shader shader( "shaders/sphere.vert", "shaders/sphere.frag" );
    Shader skyboxShader( "shaders/skybox.vert", "shaders/skybox.frag" );

    shader.use( );
    shader.setInt( "albedoMap", 0 );
    shader.setInt( "normalMap", 1 );
    shader.setInt( "metallicMap", 2 );
    shader.setInt( "roughnessMap", 3 );
    shader.setInt( "aoMap", 4 );

    GLfloat skyboxVertices[] = {
            // Positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
    };


    // Setup skybox VAO
    GLuint skyboxVAO, skyboxVBO;
    glGenVertexArrays( 1, &skyboxVAO );
    glGenBuffers( 1, &skyboxVBO );
    glBindVertexArray( skyboxVAO );
    glBindBuffer( GL_ARRAY_BUFFER, skyboxVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( skyboxVertices ), &skyboxVertices, GL_STATIC_DRAW );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), nullptr );
    glBindVertexArray(0);


    // Cubemap (Skybox)
    /**
     * FACES in this order: RIGHT, LEFT, TOP, BOTTOM, BACK, FRONT
     */
    vector<const GLchar*> faces;
    faces.push_back( "images/skybox_hd/right.jpg" );
    faces.push_back( "images/skybox_hd/left.jpg" );
    faces.push_back( "images/skybox_hd/top.jpg" );
    faces.push_back( "images/skybox_hd/bottom.jpg" );
    faces.push_back( "images/skybox_hd/back.jpg" );
    faces.push_back( "images/skybox_hd/front.jpg" );
    GLuint cubemapTexture = TextureLoading::LoadCubemap( faces );

    shader.setInt( "texture1", 0 );

    // Game loop
    while( !glfwWindowShouldClose( window ) )
    {
        // Set frame time
        auto currentFrame = static_cast<GLfloat>( glfwGetTime( ) );
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents( );
        DoMovement( );

        // Clear the colorbuffer
        glClearColor( 0.05f, 0.05f, 0.05f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



        // Draw our first triangle
        glm::mat4 model;
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );


        // Draw skybox as last
        glDepthFunc( GL_LEQUAL );  // Change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use( );
        view = glm::mat4( glm::mat3( camera.GetViewMatrix( ) ) );	// Remove any translation component of the view matrix

        skyboxShader.setMatrix( "view",       view );
        skyboxShader.setMatrix( "projection", projection );

        // skybox cube
        glBindVertexArray( skyboxVAO );
        glBindTexture( GL_TEXTURE_CUBE_MAP, cubemapTexture );
        glDrawArrays( GL_TRIANGLES, 0, 36 );
        glBindVertexArray( 0 );
        glDepthFunc( GL_LESS ); // Set depth function back to default



        // Swap the buffers
        glfwSwapBuffers( window );
    }

    glfwTerminate( );

    return EXIT_SUCCESS;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback( GLFWwindow * window, int width, int height )
{
    // make sure the viewport match the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport( 0, 0, width, height );
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback( GLFWwindow * window, double xpos, double ypos )
{
    if ( firstMouse )
    {
        lastX      = xpos;
        lastY      = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;  // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement( xoffset, yoffset );
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback( GLFWwindow * window, double xoffset, double yoffset )
{
    camera.ProcessMouseScroll( yoffset );
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }

    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }

    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }

    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
}


void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement( xOffset, yOffset );
}

// renders (and builds at first invocation) a sphere
// -------------------------------------------------
GLuint  sphereVAO = 0;
GLsizei indexCount;
void renderSphere( )
{
    if ( sphereVAO == 0 )
    {
        glGenVertexArrays( 1, &sphereVAO );

        GLuint VBO, EBO;
        glGenBuffers( 1, &VBO );
        glGenBuffers( 1, &EBO );

        std::vector<glm::vec3>  positions;
        std::vector<glm::vec2>  uv;
        std::vector<glm::vec3>  normals;
        std::vector<GLuint>     indices;

        const GLuint    X_SEGMENTS = 64;
        const GLuint    Y_SEGMENTS = 64;
        const GLfloat   PI = 3.14159265359f;

        for ( GLuint y = 0; y <= Y_SEGMENTS; ++y )
        {
            for ( GLuint x = 0; x <= X_SEGMENTS; ++x )
            {
                GLfloat xSegment = static_cast<GLfloat>( x ) / static_cast<GLfloat>( X_SEGMENTS );
                GLfloat ySegment = static_cast<GLfloat>( y ) / static_cast<GLfloat>( Y_SEGMENTS );
                GLfloat xPos     = std::cos( xSegment * 2.0f * PI ) * std::sin( ySegment * PI );
                GLfloat yPos     = std::cos( ySegment * PI );
                GLfloat zPos     = std::sin( xSegment * 2.0f * PI ) * std::sin( ySegment * PI );

                positions.emplace_back(xPos, yPos, zPos);
                uv.emplace_back( xSegment, ySegment );
                normals.emplace_back( xPos, yPos, zPos );
            }
        }

        bool oddRow = false;
        for ( GLint y = 0; y < Y_SEGMENTS; ++y )
        {
            if ( !oddRow )
            {
                for ( GLint x = 0; x <= X_SEGMENTS; ++x )
                {
                    indices.emplace_back(   y       * ( X_SEGMENTS + 1 ) + x );
                    indices.emplace_back( ( y + 1 ) * ( X_SEGMENTS + 1 ) + x );
                }
            }
            else
            {
                for ( GLint x = X_SEGMENTS; x >= 0; --x )
                {
                    indices.emplace_back( ( y + 1 ) * ( X_SEGMENTS + 1 ) + x );
                    indices.emplace_back(   y       * ( X_SEGMENTS + 1 ) + x );
                }
            }

            oddRow = !oddRow;
        }

        indexCount = static_cast<GLsizei>( indices.size( ) );

        std::vector<GLfloat> data;
        for ( GLint i = 0; i < positions.size( ); ++i )
        {
            data.emplace_back( positions[i].x );
            data.emplace_back( positions[i].y );
            data.emplace_back( positions[i].z );

            if ( !uv.empty( ) )
            {
                data.emplace_back( uv[i].x );
                data.emplace_back( uv[i].y );
            }

            if ( !normals.empty( ) )
            {
                data.emplace_back( normals[i].x );
                data.emplace_back( normals[i].y );
                data.emplace_back( normals[i].z );
            }
        }

        glBindVertexArray( sphereVAO );
        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBufferData( GL_ARRAY_BUFFER, data.size( ) * sizeof( GLfloat ), &data[0], GL_STATIC_DRAW );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size( ) * sizeof( GLuint ), &indices[0], GL_STATIC_DRAW );

        GLsizei stride = ( 3 + 2 + 3 ) * sizeof( GLfloat );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, stride, nullptr );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, stride, (void *)( 3 * sizeof( GLfloat ) ) );
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, stride, (void *)( 5 * sizeof( GLfloat ) ) );

    }

    glBindVertexArray( sphereVAO );
    glDrawElements( GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0 );

}
