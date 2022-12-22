#pragma once

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <vector>


namespace mgo
{
class window final
{
public:
    window(const std::string& title, unsigned int width, unsigned int height);
    
    ~window() noexcept;
    
    [[nodiscard]] GLFWwindow* data() noexcept;
    
    [[nodiscard]] GLFWwindow* const data() const noexcept;
        
    [[nodiscard]] bool should_close() const noexcept;
    
    [[nodiscard]] bool has_framebuffer_resized() noexcept;
    
    [[nodiscard]] VkExtent2D get_framebuffer_size() const noexcept;

    [[nodiscard]] static std::vector<const char*> get_required_instance_extentions() noexcept;
        
    static void poll_events() noexcept;

    void destroy_window() noexcept;
    
    void set_title(const std::string& title) const noexcept;
    
    void set_size(unsigned int width, unsigned int height) const noexcept;
    
private:
    GLFWwindow* pWindow_;
    bool has_framebuffer_resized_;
    static unsigned int window_count_;
    
    static unsigned int init();
    
    static void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height);
};
}
