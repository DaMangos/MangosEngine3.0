#pragma once

#include "mgo_instance.hpp"

namespace mgo
{
class messenger final
{
    friend mgo::instance;
    friend mgo::window;
    
public:
    messenger(const mgo::instance& instance);
    
    ~messenger() noexcept;
    
    [[nodiscard]] VkDebugUtilsMessengerEXT data() noexcept;
    
private:
    VkDebugUtilsMessengerEXT messenger_;
    const mgo::instance& instance_;
    
    [[nodiscard]] static VkDebugUtilsMessengerCreateInfoEXT get_VkDebugUtilsMessengerCreateInfoEXT() noexcept;
    
    static VkBool32 error_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                   VkDebugUtilsMessageTypeFlagsEXT messageType,
                                   const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                   void* pUserData) noexcept;
    
    static void error_callback(int error, const char* description) noexcept;
};
}
