#include "gbepch.h"
#include "ImGui/ImGuiLayer.h"

#include "imgui.h"
#include "Application/Application.h"

#ifdef GBE_WINDOW_API_GLFW
#include "backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#endif

#ifdef GBE_RENDER_API_OPENGL
#include "backends/imgui_impl_opengl3.h"
#endif

#include "Window/Platform/WindowsWindow.h"

#ifdef GBE_WINDOW_API_GLFW
#endif

namespace GreyboxEngine
{
    static inline float Saturate(float v) { return v < 0.0f ? 0.0f : v > 1.0f ? 1.0f : v; }

    ImGuiLayer::ImGuiLayer() : Layer("ImGui Layer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
            //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
            //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
            
            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsClassic();

            // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
            ImGuiStyle& style = ImGui::GetStyle();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                    style.WindowRounding = 0.0f;
                    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }

            auto& colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

            /* Dark Theme Begin */
            // Headers
            colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		
            // Buttons
            colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

            // Frame BG
            colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

            // Tabs
            colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
            colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
            colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

            // Title
            colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
            /* Dark Theme End */

            auto& app = Application::Get();
            auto* nativeWindow = app.GetWindow().GetNativeWindow();
            if (nativeWindow != nullptr)
            {
#ifdef GBE_WINDOW_API_GLFW
                    auto* windowsWindow = static_cast<GLFWwindow*>(nativeWindow);
                    ImGui_ImplGlfw_InitForOpenGL(windowsWindow, true);
#endif
            }
#ifdef GBE_RENDER_API_OPENGL
            ImGui_ImplOpenGL3_Init("#version 410");
#endif
    }

    void ImGuiLayer::OnDetach()
    {
#ifdef GBE_RENDER_API_OPENGL
            ImGui_ImplOpenGL3_Shutdown();
#endif
#ifdef GBE_WINDOW_API_GLFW
            ImGui_ImplGlfw_Shutdown();
#endif
            ImGui::DestroyContext();
    }

    void ImGuiLayer::OnImGuiRender()
    {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void ImGuiLayer::Begin()
    {
#ifdef GBE_RENDER_API_OPENGL
        ImGui_ImplOpenGL3_NewFrame();
#endif
#ifdef GBE_WINDOW_API_GLFW
        ImGui_ImplGlfw_NewFrame();
#endif
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
            
            ImGuiIO& io = ImGui::GetIO();
            Application& app = Application::Get();
            io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

            // Rendering
            ImGui::Render();

#ifdef GBE_WINDOW_API_GLFW
        int display_w, display_h;
        glfwGetFramebufferSize(static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow()), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
#endif
        
#ifdef GBE_RENDER_API_OPENGL
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
#ifdef GBE_WINDOW_API_GLFW
                    GLFWwindow* backup_current_context = glfwGetCurrentContext();
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                    glfwMakeContextCurrent(backup_current_context);
#endif
            }
    }
}
