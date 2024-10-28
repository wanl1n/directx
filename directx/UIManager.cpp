#include "UIManager.h"

UIManager* UIManager::sharedInstance = nullptr;
UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND hwnd, RenderSystem* rs)
{
	sharedInstance = new UIManager();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsLight();
	sharedInstance->setUIStyle();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(rs->getDevice(), rs->getContext());
}

void UIManager::destroy()
{
	if (sharedInstance == NULL)
		return;
	delete sharedInstance;
}

UIManager::UIManager() {}
UIManager::~UIManager() {}

void UIManager::update()
{
}

void UIManager::render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (creditsOpen)
		this->drawCreditsUI();

	if (demoOpen)
		this->drawSampleUI();
	
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::drawSampleUI()
{
	this->demoOpen = true;
	// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("Sample", &demoOpen, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open Credits", "Ctrl+O")) { this->drawCreditsUI(); }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { demoOpen = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// Edit a color stored as 4 floats
	float pink[] = { 0.957f, 0.761f, 0.761f, 1.0f };
	ImGui::ColorEdit4("Color", pink);

	// Generate samples and plot them
	float samples[100];
	for (int n = 0; n < 100; n++)
		samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
	ImGui::PlotLines("Samples", samples, 100);

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 150.0f/255.0f, 200.0f/255.0f, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();
	ImGui::End();
}

void UIManager::drawCreditsUI()
{
	this->creditsOpen = true;

	// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("About", &creditsOpen, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open Sample", "Ctrl+O")) { this->drawSampleUI(); }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { creditsOpen = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text("Scene Editor v0.01");
	ImGui::Text("Developed by: Kate Nicole Young");
	ImGui::Text("");
	ImGui::Text("Acknowledgements");
	ImGui::Text("Doc Neil Del Gallego as Professor");
	ImGui::Text("Omar Cornut as Dear ImGui Developer");
	ImGui::Text("Patitotective as ImThemes Developer");
	ImGui::Text("");
	ImGui::Text("Special Thanks");
	ImGui::Text("My Parents as Financial Support");

	if (this->buttonCentered("Close")) creditsOpen = false;

	ImGui::End();
}

bool UIManager::buttonCentered(std::string text) {
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	return ImGui::Button(text.c_str());
}

void UIManager::setUIStyle()
{
	// girlypop style from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 11.80000019073486f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 0.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 7.800000190734863f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 14.0f;
	style.ScrollbarRounding = 9.199999809265137f;
	style.GrabMinSize = 9.899999618530273f;
	style.GrabRounding = 20.0f;
	style.TabRounding = 5.599999904632568f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.274678111076355f, 0.2746753692626953f, 0.2746753692626953f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 0.9570815563201904f, 0.9714493155479431f, 0.8117647171020508f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.9800000190734863f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 0.300000011920929f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.9764705896377563f, 0.6624683141708374f, 0.8693404197692871f, 0.4000000059604645f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.9764705896377563f, 0.6624683141708374f, 0.8403581380844116f, 0.6705882549285889f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.8117647171020508f, 0.6430450081825256f, 0.7224425077438354f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.5607843399047852f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.0f, 0.5803921818733215f, 0.7843137383460999f, 0.5098039507865906f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.9055793881416321f, 0.8123008608818054f, 0.8723514080047607f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.9764705896377563f, 0.9764705896377563f, 0.9764705896377563f, 0.5299999713897705f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.686274528503418f, 0.686274528503418f, 0.686274528503418f, 0.800000011920929f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4862745106220245f, 0.4862745106220245f, 0.4862745106220245f, 0.800000011920929f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.4862745106220245f, 0.4862745106220245f, 0.4862745106220245f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 0.6235294342041016f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.0f, 0.6235294342041016f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.6235294342041016f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(1.0f, 0.6235294342041016f, 0.7843137383460999f, 0.4000000059604645f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.5882353186607361f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 0.5882353186607361f, 0.7921568751335144f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(1.0f, 0.5882353186607361f, 0.7882353067398071f, 0.3098039329051971f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.0f, 0.5882353186607361f, 0.7882353067398071f, 0.800000011920929f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(1.0f, 0.5882353186607361f, 0.8039215803146362f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.4627451002597809f, 0.3882353007793427f, 0.3882353007793427f, 0.6196078658103943f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(1.0f, 0.5960784554481506f, 0.800000011920929f, 0.7803921699523926f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(1.0f, 0.5882353186607361f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.0f, 0.6196078658103943f, 0.7411764860153198f, 0.168627455830574f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.0f, 0.5882353186607361f, 0.7960784435272217f, 0.6705882549285889f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 0.5882353186607361f, 0.8117647171020508f, 0.9490196108818054f);
	style.Colors[ImGuiCol_Tab] = ImVec4(1.0f, 0.7960784435272217f, 0.8352941274642944f, 0.5176470875740051f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(1.0f, 0.5882353186607361f, 0.7882353067398071f, 0.800000011920929f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(1.0f, 0.5882353186607361f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(1.0f, 0.6235294342041016f, 0.7843137383460999f, 0.7058823704719543f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(1.0f, 0.5882353186607361f, 0.7921568751335144f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.3803921639919281f, 0.2356939613819122f, 0.3037872314453125f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.6078431606292725f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.6980392336845398f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.4470588266849518f, 0.5882353186607361f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(1.0f, 0.5882353186607361f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.5686274766921997f, 0.5686274766921997f, 0.6392157077789307f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.6784313917160034f, 0.6784313917160034f, 0.7372549176216125f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.501960813999176f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 0.8841201663017273f, 0.9393014907836914f, 0.501960813999176f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.0f, 0.6235294342041016f, 0.7843137383460999f, 0.3490196168422699f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 0.5882353186607361f, 0.7803921699523926f, 0.9490196108818054f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(1.0f, 0.5882353186607361f, 0.7843137383460999f, 0.800000011920929f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.6980392336845398f, 0.6980392336845398f, 0.6980392336845398f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.3499999940395355f);

}
