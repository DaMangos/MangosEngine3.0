#include "mgo_instance.hpp"
#include "mgo_messenger.hpp"

#define MGO_TO_SIZE(container) static_cast<std::uint32_t>(container.size())
#define MGO_TO_DATA(container) (container.size() > 0) ? container.data() : nullptr

mgo::instance::instance(const mgo::window& window)
{
#ifdef DEBUG
    VkDebugUtilsMessengerCreateInfoEXT messengerCreateInfo = mgo::messenger::get_VkDebugUtilsMessengerCreateInfoEXT();
#endif
    
    std::vector<const char*> enabledLayers = get_enabled_layers();
    std::vector<const char*> enabledExtensions = get_enabled_extentions(window);
    
    VkInstanceCreateInfo createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = nullptr,
        .flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
        .pApplicationInfo = nullptr,
        .enabledLayerCount = MGO_TO_SIZE(enabledLayers),
        .ppEnabledLayerNames = MGO_TO_DATA(enabledLayers),
        .enabledExtensionCount = MGO_TO_SIZE(enabledExtensions),
        .ppEnabledExtensionNames = MGO_TO_DATA(enabledExtensions)
    };
    
    if (vkCreateInstance(&createInfo, nullptr, &instance_) != VK_SUCCESS)
        throw std::runtime_error("Failed to create VkInstance!");
}

mgo::instance::~instance() noexcept
{
    
}

[[nodiscard]] VkInstance mgo::instance::data() noexcept
{
    return instance_;
}
    
[[nodiscard]] VkDebugUtilsMessengerEXT mgo::instance::create_VkDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo) const
{
    VkDebugUtilsMessengerEXT messenger;
    if (vkCreateDebugUtilsMessengerEXT(instance_, pCreateInfo, nullptr, &messenger) != VK_SUCCESS)
        throw std::runtime_error("Falied to create VkDebugUtilsMessengerEXT!");
    return messenger;
}

[[nodiscard]] VkSurfaceKHR mgo::instance::create_VkSurfaceKHR() const
{
    return 0;
}

void mgo::instance::destroy_VkDebugUtilsMessengerEXT(VkDebugUtilsMessengerEXT& messenger) const noexcept
{
    
}

void mgo::instance::destroy_VkSurfaceKHR(VkSurfaceKHR& surface) const noexcept
{
    
}

std::vector<const char*> mgo::instance::get_enabled_extentions(const mgo::window& window) noexcept
{
    std::vector<const char*> extensions = window.get_required_instance_extentions();
    extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    extensions.emplace_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#ifdef DEBUG
    extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
    return extensions;
}

std::vector<const char*> mgo::instance::get_enabled_layers() noexcept
{
    std::vector<const char*> layers;
#ifdef DEBUG
    layers.emplace_back("VK_LAYER_KHRONOS_validation");
#endif
    return layers;
}
