#pragma once

class Application
{
public:
	Application();
	virtual ~Application();
	
	bool init(int width, int height, const char* name);
	void shutdown();

	void start();
	void requestStop();

	virtual void started();
	virtual void update(float dt);
	virtual void render();
	virtual void stopped();

	// TODO: proper input helpers
	virtual void onKeyEvent(int key, int scancode, int action, int mods);

	glm::ivec2	getWindowSize() const;
	float		getWindowRatio() const;

private:
	void _processEvents();
	void _update();
	void _render();

	bool		m_initialized;
	GLFWwindow* m_window;
	double		m_previousTime;

};
