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
#include <cmath>


// Function prototypes
void framebuffer_size_callback( GLFWwindow * window, int width, int height );
void mouse_callback( GLFWwindow * window, double xpos, double ypos );
void key_callback( GLFWwindow *window, int key, int scancode, int action, int mode );
void mouse_button_callback( GLFWwindow * window, int button, int action, int mods );
void scroll_callback( GLFWwindow * window, double xoffset, double yoffset );
void processInput( GLFWwindow * window );
void renderSphere( );


// Properties
const GLuint SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080;


// Camera
Camera camera (glm::vec3( 0.0f, 0.0f, 30.0f ));
GLfloat lastX = 800.0f / 2.0f;
GLfloat lastY = 600.0f / 2.0f;

bool hasClicked = false;
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
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

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
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set the required callback functions
    glfwSetKeyCallback( window, key_callback );
    glfwSetMouseButtonCallback( window, mouse_button_callback );


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
    Shader shaderTexture( "shaders/sphere_textures.vert", "shaders/sphere_textures.frag" );
    Shader skyboxShader( "shaders/skybox.vert", "shaders/skybox.frag" );

    shader.use( );
    shader.setVector( "albedo", 0.5f, 0.0f, 0.0f );
    shader.setFloat( "ao", 1.0f );

    shaderTexture.use( );
    shaderTexture.setInt( "albedoMap", 0 );
    shaderTexture.setInt( "normalMap", 1 );
    shaderTexture.setInt( "metallicMap", 2 );
    shaderTexture.setInt( "roughnessMap", 3 );
    shaderTexture.setInt( "aoMap", 4 );

    GLuint albedo    = TextureLoading::LoadTexture( (GLchar *)("textures/pbr/rusted_iron/albedo.png") );
    GLuint normal    = TextureLoading::LoadTexture( (GLchar *)("textures/pbr/rusted_iron/normal.png") );
    GLuint metallic  = TextureLoading::LoadTexture( (GLchar *)("textures/pbr/rusted_iron/metallic.png") );
    GLuint roughness = TextureLoading::LoadTexture( (GLchar *)("textures/pbr/rusted_iron/roughness.png") );
    GLuint ao        = TextureLoading::LoadTexture( (GLchar *)("textures/pbr/rusted_iron/ao.png") );

    // lights
    // ------
    glm::vec3 lightPositions[] = {
            glm::vec3(-10.0f,  10.0f, 10.0f),
            glm::vec3( 10.0f,  10.0f, 10.0f),
            glm::vec3(-10.0f, -10.0f, 10.0f),
            glm::vec3( 10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f)
    };
    GLint nrRows    = 7;
    GLint nrColumns = 7;
    GLfloat spacing = 2.5;

    // initialize static shaderTexture uniforms before rendering
    // --------------------------------------------------
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

    shader.use( );
    shader.setMatrix( "projection", projection );

    shaderTexture.use( );
    shaderTexture.setMatrix( "projection", projection );

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

    // Game loop
    while( !glfwWindowShouldClose( window ) )
    {
        // Set frame time
        auto currentFrame = static_cast<GLfloat>( glfwGetTime( ) );
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput( window );

        // Clear the colorbuffer
        glClearColor( 0.05f, 0.05f, 0.05f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


        // Draw our first triangle
        glm::mat4 model;
        glm::mat4 view = camera.GetViewMatrix();

        shader.use( );
        shader.setMatrix( "view", view );
        shader.setVector( "camPos", camera.GetPosition() );


        // render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
        for (GLuint row = 0; row < nrRows; ++row)
        {
            shader.setFloat("metallic", (GLfloat)row / (GLfloat)nrRows);

            for (GLuint col = 0; col < nrColumns; ++col)
            {
                if ( row == glm::round(nrRows/2) && col == glm::round(nrColumns/2) )
                {
                    shaderTexture.use( );
                    shaderTexture.setMatrix( "view", view );
                    shaderTexture.setVector( "camPos", camera.GetPosition() );

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, albedo);
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, normal);
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, metallic);
                    glActiveTexture(GL_TEXTURE3);
                    glBindTexture(GL_TEXTURE_2D, roughness);
                    glActiveTexture(GL_TEXTURE4);
                    glBindTexture(GL_TEXTURE_2D, ao);

                    model = glm::mat4();
                    model = glm::translate(model, glm::vec3(
                            ((GLfloat)col - ((GLfloat)nrColumns / 2)) * spacing,
                            ((GLfloat)row - ((GLfloat)nrRows / 2)) * spacing,
                            0.0f
                    ));
                    shaderTexture.setMatrix( "model", model );
                    renderSphere();
                }
                else
                {
                    shader.use();

                    // we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
                    // on direct lighting.
                    shader.setFloat("roughness", glm::clamp((GLfloat)col / (GLfloat)nrColumns, 0.05f, 1.0f));

                    model = glm::mat4();
                    model = glm::translate(model, glm::vec3(
                            ((GLfloat)col - ((GLfloat)nrColumns / 2)) * spacing,
                            ((GLfloat)row - ((GLfloat)nrRows / 2)) * spacing,
                            0.0f
                    ));
                    shader.setMatrix("model", model);
                    renderSphere();
                }
            }
        }

        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and
        // keeps the codeprint small.
        for (GLint i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
        {
            glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
            newPos = lightPositions[i];

            shader.use();
            shader.setVector("lightPositions[" + std::to_string(i) + "]", newPos);
            shader.setVector("lightColors[" + std::to_string(i) + "]", lightColors[i]);

            shaderTexture.use();
            shaderTexture.setVector("lightPositions[" + std::to_string(i) + "]", newPos);
            shaderTexture.setVector("lightColors[" + std::to_string(i) + "]", lightColors[i]);
        }


        /*
        // Draw skybox as last
        glDepthFunc( GL_LEQUAL ); // Change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use( );
        view = glm::mat4( glm::mat3( camera.GetViewMatrix( ) ) ); // Remove any translation component of the view matrix

        skyboxShader.setMatrix( "view",       view );
        skyboxShader.setMatrix( "projection", projection );

        // skybox cube
        glBindVertexArray( skyboxVAO );
        glBindTexture( GL_TEXTURE_CUBE_MAP, cubemapTexture );
        glDrawArrays( GL_TRIANGLES, 0, 36 );
        glBindVertexArray( 0 );
        glDepthFunc( GL_LESS ); // Set depth function back to default
        */

        // Swap the buffers
        glfwSwapBuffers( window );
        glfwPollEvents( );
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
    auto glXPos = static_cast<GLfloat>( xpos );
    auto glYPos = static_cast<GLfloat>( ypos );

    if ( firstMouse )
    {
        lastX      = glXPos;
        lastY      = glYPos;
        firstMouse = false;
    }

    if (hasClicked)
    {
        GLfloat xoffset = glXPos - lastX;
        GLfloat yoffset = lastY - glYPos;  // reversed since y-coordinates go from bottom to top
        camera.ProcessMouseMovement( xoffset, yoffset );
    }


    lastX = glXPos;
    lastY = glYPos;

}


// Is called whenever a key is pressed/released via GLFW
void key_callback( GLFWwindow *window, int key, int scancode, int action, int mode )
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


// Is called whenever a mouse button change its state
void mouse_button_callback( GLFWwindow * window, int button, int action, int mods )
{
    hasClicked = button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS;
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback( GLFWwindow * window, double xoffset, double yoffset )
{
    camera.ProcessMouseScroll( static_cast<GLfloat>( yoffset ) );
}


void processInput( GLFWwindow * window )
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
        const GLfloat   PI         = 3.14159265359f;

        for ( GLuint y = 0; y <= Y_SEGMENTS; ++y )
        {
            for ( GLuint x = 0; x <= X_SEGMENTS; ++x )
            {
                GLfloat xSegment = (GLfloat)x / (GLfloat)X_SEGMENTS;
                GLfloat ySegment = (GLfloat)y / (GLfloat)Y_SEGMENTS;
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
    glDrawElements( GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, nullptr );

}
