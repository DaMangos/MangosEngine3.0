#include <cstdint>
#include <iostream>

#include "mgo_window.hpp"
#include "mgo_messenger.hpp"

unsigned int mgo::window::window_count_ = mgo::window::init();

mgo::window::window(const std::string& title, unsigned int width, unsigned int height)
{
    if ((pWindow_ = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr)) == nullptr)
        throw std::runtime_error("Falied to create GLFWwindow!");
    
    glfwSetWindowUserPointer(pWindow_, this);
    
    glfwSetFramebufferSizeCallback(pWindow_, framebuffer_size_callback);
}

mgo::window::~window() noexcept
{
    destroy_window();
}

[[nodiscard]] GLFWwindow* mgo::window::data() noexcept
{
    return pWindow_;
}

[[nodiscard]] GLFWwindow* const mgo::window::data() const noexcept
{
    return pWindow_;
}
    
[[nodiscard]] bool mgo::window::should_close() const noexcept
{
    return glfwWindowShouldClose(pWindow_);
}

[[nodiscard]] bool mgo::window::has_framebuffer_resized() noexcept
{
    if (has_framebuffer_resized_)
    {
        has_framebuffer_resized_ = false;
        return true;
    }
    return false;
}

[[nodiscard]] VkExtent2D mgo::window::get_framebuffer_size() const noexcept
{
    int width, height;
    glfwGetFramebufferSize(pWindow_, &width, &height);
    return {.width = static_cast<std::uint32_t>(width), .height = static_cast<std::uint32_t>(height)};
}

[[nodiscard]] std::vector<const char*> mgo::window::get_required_instance_extentions() noexcept
{
    std:uint32_t count;
    const char** begin = glfwGetRequiredInstanceExtensions(&count);
    return std::vector<const char*>(begin, begin + count);
}

void mgo::window::poll_events() noexcept
{
    glfwPollEvents();
}

void mgo::window::destroy_window() noexcept
{
    glfwDestroyWindow(pWindow_);
    if (--window_count_ == 0)
        glfwTerminate();
}

void mgo::window::set_title(const std::string& title) const noexcept
{
    glfwSetWindowTitle(pWindow_, title.c_str());
}

void mgo::window::set_size(unsigned int width, unsigned int height) const noexcept
{
    glfwSetWindowSize(pWindow_, static_cast<int>(width), static_cast<int>(height));
}

unsigned int mgo::window::init()
{
    glfwSetErrorCallback(mgo::messenger::error_callback);

    if (glfwInit() == GLFW_FALSE)
        throw std::runtime_error("Falied to init GLFW!");
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    return 0;
}

void mgo::window::framebuffer_size_callback(GLFWwindow* pWindow, int width, int height)
{
    mgo::window* pThis = reinterpret_cast<mgo::window*>(glfwGetWindowUserPointer(pWindow));
    pThis->has_framebuffer_resized_ = true;
}
