#include "GUI.h"
#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules\Ogre\Renderer.h>

#include "Utilities\Vector4.h"

GUI::GUI() {
	ogre_renderer = nullptr;
	m_context = nullptr;
	m_root = nullptr;
}

void GUI::Init() {
	if (ogre_renderer == nullptr) {
		ogre_renderer = &CEGUI::OgreRenderer::bootstrapSystem();

		CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("Schemes");
		CEGUI::Font::setDefaultResourceGroup("Fonts");
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
		CEGUI::ScriptModule::setDefaultResourceGroup("Scripts");
	}

	m_context = &CEGUI::System::getSingleton().createGUIContext(ogre_renderer->getDefaultRenderTarget());
	m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	m_context->setRootWindow(m_root);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_root);
}

void GUI::InitResources() {
	loadScheme("TaharezLook");
	loadScheme("AlfiskoSkin");
	setFont("DejaVuSans-10");

	//CEGUI::WindowManager::getSingleton().
	
	//local w = CEGUI::WindowManager::getSingleton().loadWindowLayout("../datafiles/layouts/test.layout");
	//CEGUI::System::getSingleton().
	//CEGUI::System::getSingleton().getGUISheet().addChildWindow(w);
	

	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	//CEGUI::System::getSingleton().setDefaultMouseCursor(“TaharezLook”, “MouseArrow”);
}

void GUI::destroy() {
	CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}

void GUI::relocate() {
	m_context = &CEGUI::System::getSingleton().getDefaultGUIContext();
	//m_root = CEGUI::WindowManager::getSingleton().wind
	//ogre_renderer = &ogre_renderer->getDefaultRenderTarget();
	//&CEGUI::OgreRenderer::

	//m_context = &CEGUI::System::getSingleton().createGUIContext(ogre_renderer->getDefaultRenderTarget());
	//m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	//m_context->setRootWindow(m_root);
}

void GUI::draw() {
	ogre_renderer->beginRendering();
	m_context->draw();
	ogre_renderer->endRendering();
	
	//glDisable(GL_SCISSOR_TEST);
}

void GUI::loadScheme(const std::string& schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile+ ".scheme");
}

void GUI::setFont(const std::string& fontFile) {
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	m_context->setDefaultFont(fontFile);
}

//Crear Boton
void GUI::createButton(const std::string& type, Vector4 Percents, Vector4 Pixels, const std::string& text, const std::string& name) {
	CEGUI::PushButton* pb = static_cast<CEGUI::PushButton*>(createWidget(type, Percents, Pixels, name));
	pb->setText(text);



	//Para pulsaciones
	/*
	El primer parámetro es el evento en sí. El segundo parámetro es un objeto Event::Subscriber. 
	Cuando se crea  un  objeto  Subscriber,  la  primera  cosa  que  se  pasa  es  un  puntero  a  
	la  función  que  manejará  el evento  (nota,  el  símbolo  &  da  un  puntero  de  la  función).  
	La  segunda  cosa  que  se  pasa  es  el  objeto TutorialListener que manejará el evento 
	(en este caso this). Ahora la función TutorialListener::quit (que ya ha sido definida) manejará el 
	clic del ratón y finalizará el programa.
	*/
	//quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&TutorialListener::quit, this));
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
