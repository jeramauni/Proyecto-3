#pragma once

#include <string>

namespace CEGUI {
	class OgreRenderer;
	class OpenGL3Renderer;
	class Window;
	class GUIContext;
}

namespace Ogre {
	class RenderTarget;
}

class Vector4;

class GUI {
public:
	GUI();

	void Init(const std::string& resourceDir);
	void destroy();

	void draw();
	void setRenderTarget(CEGUI::OgreRenderer* rTg);

	void loadScheme(const std::string& schemeFile);
	void setFont(const std::string& fontFile);
	void createButton(const std::string& type, Vector4 Percents, Vector4 Pixels, const std::string& text, const std::string& name = "");

	static void setWidgetDestRect(CEGUI::Window* widget, Vector4 Percents, Vector4 Pixels);

	//const CEGUI::OpenGL3Renderer* getRenderer();
	const CEGUI::OgreRenderer* getRenderer();
	const CEGUI::GUIContext* getContext();

private:
	CEGUI::OgreRenderer* ogre_renderer;
	CEGUI::GUIContext* m_context;
	CEGUI::Window* m_root;

	CEGUI::Window* createWidget(const std::string& type, Vector4 Percents, Vector4 Pixels, const std::string& name = "");
};