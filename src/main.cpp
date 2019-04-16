#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <terrain.hpp>
#include <lib.hpp>

int main() {
    // Window cretion
    // --------------
    glfwFullInit();
    const int res[2] = {800, 600};
    Window window(res[0], res[1]);
    window.makeResizeable();

    std::string dataDir = "./data/";

	// Model
	// -----------
    // Texture and mesh
    Mesh cube(Mesh::Cube, dataDir + "textures/rock.png");
    // Shader
	ShaderProgram shaderProgram(dataDir + "shaders/shader.vert", dataDir + "shaders/shader.frag");
    
    glm::vec3 positions[] = {
        glm::vec3( 1.0f,  1.0f,  1.0f), 
        glm::vec3( 2.0f,  1.0f,  1.0f), 
        glm::vec3( 3.0f,  1.0f,  1.0f), 
    };

    glm::mat4 model;
    Camera camera(glm::vec3(-6.0f, 14.5f, 40.0f), glm::vec3(0.8f, -0.5f, -0.3f), 20.0f);

    // TERRAIN
    // -------
    const uint terrainX = 50, terrainY = 50;
    Terrain<50, 50> *terrain = new Terrain<50, 50> ();
    std::vector<glm::vec4> transitions = terrain -> getTransitions();

    // Render loop
    // -----------
    float deltaTime = 0.0f, lastFrame = 0.0f;
    while (window.isOpen()) {
        // Delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Camera controls
        if (window.keyPressed(GLFW_KEY_W))
            camera.move(camera.front(), deltaTime);
        if (window.keyPressed(GLFW_KEY_S))
            camera.move(camera.back(), deltaTime);
        if (window.keyPressed(GLFW_KEY_A))
            camera.move(camera.left(), deltaTime);
        if (window.keyPressed(GLFW_KEY_D))
            camera.move(camera.right(), deltaTime);
        if (window.keyPressed(GLFW_KEY_SPACE))
            camera.move(camera.up(), deltaTime);
        if (window.keyPressed(GLFW_KEY_LEFT_CONTROL))
            camera.move(camera.down(), deltaTime);
        camera.mouseMove(window.getMXPos(), window.getMYPos());
        // New terrain generation
        if (window.keyPressed(GLFW_KEY_R)) {
            delete terrain;
            terrain = new Terrain<50, 50>();     
            transitions = terrain -> getTransitions();
        }
        // Rendering
        window.clear(glm::vec4(0.693f, 0.905f, 1.0f, 1.0f));   
        shaderProgram.setUniform("u_time", glfwGetTime());
        shaderProgram.setUniform("view", camera.viewMat());
        shaderProgram.setUniform("projection", camera.projMat());
        shaderProgram.setUniform("u_resolution", glm::vec2(res[0], res[1]));
        shaderProgram.setUniform("texture1", 0);
		shaderProgram.use();
        for (auto &vec : transitions) {
            //std::cout << "MAIN::RENDER::DRAWING_AT: " << vec.x << " " << vec.y << " " << vec.z << std::endl;
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(vec.x, vec.y, vec.z));
            shaderProgram.setUniform("model", model);
            window.draw(&cube);
        }
        window.display();

        window.pollEvents();
    }
    glfwTerminate();
    return 0;
}
