#include "gbepch.h"
#include "ImGui/ImGuiLayer.h"

#include "imgui.h"
#include "Application/Application.h"

#ifdef GBE_WINDOW_API_GLFW
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#endif

#include "Window/Platform/WindowsWindow.h"
#include "Window/Platform/OpenGL/ImGuiOpenGLRenderer.h"

#ifdef GBE_WINDOW_API_GLFW
#include "Window/Platform/OpenGL/ImGuiImplGLFW.h"
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
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        auto& app = Application::Get();
        auto* nativeWindow = app.GetWindow().GetNativeWindow();
        if (nativeWindow != nullptr)
        {
#ifdef GBE_WINDOW_API_GLFW
            auto* windowsWindow = static_cast<GLFWwindow*>(nativeWindow);
            ImGui_ImplGlfw_InitForOpenGL(windowsWindow, false);
#endif
        }
#ifdef GBE_RENDER_API_OPENGL
        ImGui_ImplOpenGL3_Init("#version 410");
#endif

        // Key Mappings
        io.KeyMap[ImGuiKey_Backspace] = Key::Backspace;
        io.KeyMap[ImGuiKey_LeftShift] = Key::LeftShift;
        io.KeyMap[ImGuiKey_LeftAlt] = Key::LeftAlt;
        io.KeyMap[ImGuiKey_LeftSuper] = Key::LeftSuper;
        io.KeyMap[ImGuiKey_LeftCtrl] = Key::LeftControl;
        io.KeyMap[ImGuiKey_RightShift] = Key::RightShift;
        io.KeyMap[ImGuiKey_RightAlt] = Key::RightAlt;
        io.KeyMap[ImGuiKey_RightSuper] = Key::RightSuper;
        io.KeyMap[ImGuiKey_RightCtrl] = Key::RightControl;
        io.KeyMap[ImGuiKey_LeftArrow] = Key::Left;
        io.KeyMap[ImGuiKey_UpArrow] = Key::Up;
        io.KeyMap[ImGuiKey_DownArrow] = Key::Down;
        io.KeyMap[ImGuiKey_RightArrow] = Key::Right;
    }

    void ImGuiLayer::OnDetach()
    {
    }

    void ImGuiLayer::OnUpdate(float time)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
        m_time = time;

        // Start the Dear ImGui frame
#ifdef GBE_RENDER_API_OPENGL
        ImGui_ImplOpenGL3_NewFrame();
#endif
#ifdef GBE_WINDOW_API_GLFW
        ImGui_ImplGlfw_NewFrame();
#endif
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();

        //int display_w, display_h;
        //auto* glfwWindow = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
        //glfwGetFramebufferSize(glfwWindow, &display_w, &display_h);
        
#ifdef GBE_RENDER_API_OPENGL
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
    }

    void ImGuiLayer::OnEvent(Event& event)
    {
        m_eventDispatcher.Dispatch<MouseButtonPressedEvent>(
            event, GBE_BIND_EVENT_FN(&ImGuiLayer::OnMouseButtonPressedEvent));
        m_eventDispatcher.Dispatch<MouseButtonReleasedEvent>(
            event, GBE_BIND_EVENT_FN(&ImGuiLayer::OnMouseButtonReleasedEvent));
        m_eventDispatcher.Dispatch<MouseMovedEvent>(event, GBE_BIND_EVENT_FN(&ImGuiLayer::OnMouseMovedEvent));
        m_eventDispatcher.Dispatch<MouseScrollEvent>(event, GBE_BIND_EVENT_FN(&ImGuiLayer::OnMouseScrollEvent));
        m_eventDispatcher.Dispatch<KeyPressedEvent>(event, GBE_BIND_EVENT_FN(&ImGuiLayer::OnKeyPressed));
        m_eventDispatcher.Dispatch<KeyReleasedEvent>(event, GBE_BIND_EVENT_FN(&ImGuiLayer::OnKeyReleased));
        m_eventDispatcher.Dispatch<KeyTypedEvent>(event, GBE_BIND_EVENT_FN(&ImGuiLayer::OnKeyTypedEvent));
        m_eventDispatcher.Dispatch<WindowResizeEvent>(event, GBE_BIND_EVENT_FN(&ImGuiLayer::OnWindowResizeEvent));
    }
    
    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.button] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.button] = false;

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.x, e.y);

        return false;
    }

    bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheel += e.y;
        io.MouseWheelH += e.x;

        return false;
    }

    bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.key] = true;
        io.KeyCtrl = io.KeysDown[Key::LeftControl] || io.KeysDown[Key::RightControl];
        io.KeyShift = io.KeysDown[Key::LeftShift] || io.KeysDown[Key::RightShift];
        io.KeySuper = io.KeysDown[Key::LeftSuper] || io.KeysDown[Key::RightSuper];
        io.KeyAlt = io.KeysDown[Key::LeftAlt] || io.KeysDown[Key::RightAlt];
        return false;
    }

    bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.key] = false;

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        const int keyCode = e.keyCode;
        if (keyCode > 0 && keyCode < 0x10000)
        {
            io.AddInputCharacter(static_cast<unsigned short>(keyCode));
        }

        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.width, e.height);
        io.DisplayFramebufferScale = ImVec2(1.f, 1.f);

#ifdef GBE_WINDOW_API_GLFW
        glViewport(0, 0, e.width, e.height);
#endif

        return false;
    }
}
