#include "GUI.h"
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\Ogre\Renderer.h>

#include "Utilities\Vector4.h"

GUI::GUI() {
	ogre_renderer = nullptr;
	m_context = nullptr;
	m_root = nullptr;
}

void GUI::Init(const std::string& resourceDir) {
	if (ogre_renderer == nullptr) {
		ogre_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
		//ogre_renderer->

		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());

		rp->setResourceGroupDirectory("imagesets", resourceDir + "/imagesets/");
		rp->setResourceGroupDirectory("schemes", resourceDir + "/schemes/");
		rp->setResourceGroupDirectory("fonts", resourceDir + "/fonts/");
		rp->setResourceGroupDirectory("layouts", resourceDir + "/layouts/");
		rp->setResourceGroupDirectory("looknfeels", resourceDir + "/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", resourceDir + "/lua_scripts/");

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts ");
	}

	m_context = &CEGUI::System::getSingleton().createGUIContext(ogre_renderer->getDefaultRenderTarget());
	m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	m_context->setRootWindow(m_root);
}

void GUI::setRenderTarget(CEGUI::OgreRenderer* rTg) {
	/*
	if (ogre_renderer == nullptr) {
		ogre_renderer = rTg;
		Init("resources/cegui");
	}
	else {
		ogre_renderer = rTg;
	}

	m_context = &CEGUI::System::getSingleton().createGUIContext(ogre_renderer->getDefaultRenderTarget());
	m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	m_context->setRootWindow(m_root);
	*/
	//guiManager->loadScheme("TaharezLook.scheme");
	//guiManager->loadScheme("AlfiskoSkin.scheme");
	//guiManager->setFont("DejaVuSans-10");
}


void GUI::destroy() {
	CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}

void GUI::draw() {
	ogre_renderer->beginRendering();
	m_context->draw();
	ogre_renderer->endRendering();
	
	//glDisable(GL_SCISSOR_TEST);
}

void GUI::loadScheme(const std::string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void GUI::setFont(const std::string& fontFile) {
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	m_context->setDefaultFont(fontFile);
}

//Crear Boton
void GUI::createButton(const std::string& type, Vector4 Percents, Vector4 Pixels, const std::string& text, const std::string& name) {
	CEGUI::PushButton* pb = static_cast<CEGUI::PushButton*>(createWidget(type, Percents, Pixels, name));
	pb->setText(text);
}


CEGUI::Window* GUI::createWidget(const std::string& type, Vector4 Percents, Vector4 Pixels, const std::string& name) {
	CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	m_root->addChild(newWindow);
	setWidgetDestRect(newWindow, Percents, Pixels);
	return newWindow;
}

void GUI::setWidgetDestRect(CEGUI::Window* widget, Vector4 Percents, Vector4 Pixels) {
	widget->setPosition(CEGUI::UVector2(CEGUI::UDim(Percents.x, Pixels.x), CEGUI::UDim(Percents.y, Pixels.y)));
	widget->setSize(CEGUI::USize(CEGUI::UDim(Percents.w, Pixels.w), CEGUI::UDim(Percents.z, Pixels.z)));
}

const CEGUI::OgreRenderer* GUI::getRenderer()
{
	return ogre_renderer;
}

const CEGUI::GUIContext* GUI::getContext()
{
	return m_context;
}
