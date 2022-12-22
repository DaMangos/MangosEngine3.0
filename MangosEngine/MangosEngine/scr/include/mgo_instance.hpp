#pragma once

#include "mgo_window.hpp"

namespace mgo
{
class instance final
{
public:    
    instance(const mgo::window& window);

    ~instance() noexcept;
    
    [[nodiscard]] VkInstance data() noexcept;
            
    [[nodiscard]] VkDebugUtilsMessengerEXT create_VkDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo) const;

    [[nodiscard]] VkSurfaceKHR create_VkSurfaceKHR() const;

    void destroy_VkDebugUtilsMessengerEXT(VkDebugUtilsMessengerEXT& messenger) const noexcept;
    
    void destroy_VkSurfaceKHR(VkSurfaceKHR& surface) const noexcept;
    
private:
    VkInstance instance_;
    
    [[nodiscard]] static std::vector<const char*> get_enabled_extentions(const mgo::window& window) noexcept;
    
    [[nodiscard]] static std::vector<const char*> get_enabled_layers() noexcept;
};
}
