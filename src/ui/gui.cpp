#include "pch.h"
#include "gui.h"

#include "user/cheat/FeatureManager.h"

GUI::GUI()
{
    setupImGuiStyle();
}

GUI::~GUI()
{
}

GUI& GUI::getInstance()
{
    static GUI instance;
    return instance;
}

void GUI::render()
{
    if (!m_visible)
    {
        return;
    }

    // Render main menu bar
    renderMainMenuBar();

    // Render example window if enabled
    if (m_showExample)
    {
        renderExampleWindow();
    }
}

void GUI::showExampleWindow()
{
    m_showExample = true;
}

void GUI::renderMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        // File menu
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit", "Alt+F4"))
            {
                // TODO: Implement exit functionality
            }
            ImGui::EndMenu();
        }

        // Windows menu
        if (ImGui::BeginMenu("Windows"))
        {
            ImGui::MenuItem("Example Window", nullptr, &m_showExample);
            ImGui::Separator();

            ImGui::EndMenu();
        }

        // Tools menu
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::Separator();

            if (ImGui::BeginMenu("Theme"))
            {
                if (ImGui::MenuItem("Dark (Default)"))
                {
                    ImGui::StyleColorsDark();
                    setupImGuiStyle();
                }
                if (ImGui::MenuItem("Light"))
                {
                    ImGui::StyleColorsLight();
                }
                if (ImGui::MenuItem("Classic"))
                {
                    ImGui::StyleColorsClassic();
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        // Performance info
        ImGui::SameLine();
        ImGui::Separator();
        ImGui::SameLine();

        float fps = ImGui::GetIO().Framerate;
        ImGui::Text("FPS: %.1f", fps);

        // Color code FPS
        if (fps >= 60.0f)
        {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "●");
        }
        else if (fps >= 30.0f)
        {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.2f, 1.0f), "●");
        }
        else
        {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.8f, 0.2f, 0.2f, 1.0f), "●");
        }

        // Controls hint
        ImGui::SameLine();
        ImGui::Separator();
        ImGui::SameLine();
        ImGui::TextDisabled("INSERT: Toggle GUI");

        ImGui::EndMainMenuBar();
    }
}

void GUI::renderExampleWindow()
{

    ImGui::Begin("##Taiga74164", nullptr, ImGuiWindowFlags_None);

    cheat::FeatureManager::getInstance().draw();

    ImGui::End();

}

void GUI::setupImGuiStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowMinSize = ImVec2(400, 300);
    
    // Modern rounded corners
    style.WindowRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.TabRounding = 6.0f;
    style.ChildRounding = 6.0f;
    style.PopupRounding = 6.0f;

    // Improved spacing and padding
    style.WindowPadding = ImVec2(12, 12);
    style.FramePadding = ImVec2(10, 6);
    style.ItemSpacing = ImVec2(10, 6);
    style.ItemInnerSpacing = ImVec2(6, 6);
    style.IndentSpacing = 24.0f;
    style.ScrollbarSize = 14.0f;
    style.GrabMinSize = 8.0f;

    // Borders
    style.WindowBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.FrameBorderSize = 0.0f;
    style.TabBorderSize = 0.0f;


    ImVec4* colors = style.Colors;

    // Core colors
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

    // Window colors
    colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.09f, 0.11f, 0.95f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.07f, 0.09f, 0.95f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.09f, 0.11f, 0.95f);

    // Border colors
    colors[ImGuiCol_Border] = ImVec4(0.20f, 0.22f, 0.25f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frame colors
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.17f, 0.19f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.20f, 0.22f, 1.00f);

    // Title bar colors
    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.08f, 0.09f, 0.11f, 1.00f);

    // Menu bar colors
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);

    // Scrollbar colors
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.07f, 0.09f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.27f, 0.30f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.32f, 0.35f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.35f, 0.37f, 0.40f, 1.00f);

    // Button colors with blue accent
    colors[ImGuiCol_Button] = ImVec4(0.15f, 0.17f, 0.19f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.22f, 0.25f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.27f, 0.30f, 1.00f);

    // Header colors (for collapsible sections)
    colors[ImGuiCol_Header] = ImVec4(0.15f, 0.17f, 0.19f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.22f, 0.25f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.27f, 0.30f, 1.00f);

    // Tab colors
    colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.14f, 0.16f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.15f, 0.17f, 0.19f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.18f, 0.20f, 0.22f, 1.00f);

    // Separator colors
    colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.22f, 0.25f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.25f, 0.27f, 0.30f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.30f, 0.32f, 0.35f, 1.00f);

    // Resize grip colors
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.25f, 0.27f, 0.30f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.30f, 0.32f, 0.35f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.37f, 0.40f, 0.95f);

    // Plot colors
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

    // Nav colors
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

    // Modal overlay
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

