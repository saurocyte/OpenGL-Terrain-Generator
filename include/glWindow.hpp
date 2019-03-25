#ifndef WINDOW
#define WINDOW

#include <array>
#include <drawable.hpp>
#include <glm/glm.hpp>

class GLFWwindow;

class Window
{
  public:
	enum DrawMode
	{
		Wireframe, Polys
	};
	enum BufferingType
	{
		Single, Double
	};

	// Also starts glad
	Window(unsigned const x, unsigned const y);

	// Window things //
	auto makeResizeable() 											-> void;
	auto isOpen() -> bool;

	// DrawMan or something
	auto pollEvents() 												-> void;
	auto keyPressed(unsigned int key) 								-> bool;
	auto clear(glm::vec4 color) const 								-> void;
	auto display() const 											-> void;
	auto draw(Drawable *drawable) 									-> void;
	auto draw(const unsigned int VAO, unsigned int verticiesCount) 	-> void;

	auto setDrawMode(DrawMode mode) 								-> void;
	auto setBufferingType(BufferingType type) 						-> void;
	auto getMousePos() 												-> void;

	inline auto getMXPos() { return mXPos; }
	inline auto getMYPos() { return mYPos; }

  private:
	// Mouse position
	static auto mouseCallback(GLFWwindow *win, double xpos, double ypos);
	double mXPos = 0;
	double mYPos = 0;
	// Vsync thingy
	BufferingType buffType = BufferingType::Double;

	GLFWwindow *windowPtr;
	struct State
	{
		unsigned int VAO;
	} state;
};

#endif