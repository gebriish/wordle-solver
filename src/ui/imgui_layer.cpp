#include "imgui_layer.h"
#include <core/window.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <stdio.h>

ImGuiLayer::ImGuiLayer()
{}

ImGuiLayer::~ImGuiLayer()
{}

void ImGuiLayer::init(const Window& window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 5.3f;
	style.FrameRounding = 2.3f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_WindowBg] = ImVec4(0x28/255.0f, 0x28/255.0f, 0x28/255.0f, 1.0f);

	style.WindowTitleAlign = ImVec2(0.5f, 0);

	ImGui_ImplGlfw_InitForOpenGL(window.glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	io.Fonts->AddFontFromFileTTF("res/m5x7.ttf", 25.0f);
}

void ImGuiLayer::newFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiLayer::drawFrame(const Window& window)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(window.width, window.height);
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
