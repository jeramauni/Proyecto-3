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
	//m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	//m_context->setRootWindow(m_root);
	//CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_root);
}

void GUI::InitResources() {
	loadScheme("TaharezLook");
	loadScheme("AlfiskoSkin");
	loadScheme("Generic");
	loadScheme("HUDDemo");
	setFont("DejaVuSans-10");

	// Esto se debera indicar en los parametros de la escena, ademas de si se renderiza o no cegui
	loadLayout("TabPage");
	//loadLayout("HUDDemoGameOver");
	//loadLayout("HUDDemoIngame");

	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
}

void GUI::destroy() {
	CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}

void GUI::setRender(bool rend) {
	ogre_renderer->setRenderingEnabled(rend);
}

void GUI::loadLayout(const std::string& layoutName) {
	m_root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layoutName + ".layout", "Layouts");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_root);
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
