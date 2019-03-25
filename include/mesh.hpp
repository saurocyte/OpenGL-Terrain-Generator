#ifndef MESH
#define MESH

#include <initializer_list>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <drawable.hpp>
#include <string>

class Window;

class Mesh : public Drawable
{
  public:
    Mesh(std::initializer_list<float> verticies, std::string texturePath);
    ~Mesh() = default;
    unsigned int trisCount;

    // Some basic meshes
    static const std::initializer_list<float> Cube;

  private:
    unsigned int textureId;
    auto load(std::string path) -> void;
    //struct Texture {
    //  unsigned int id;
    //  auto load(std::string path) -> void;
    //} texture;

    typedef float* Vertex;
    
    // For window.draw
    void draw(Window *window) const override;
    
    unsigned int VAO;
    
    std::vector<Vertex> verticies;
};

#endif