#include <iostream>

#include "mgo_messenger.hpp"

mgo::messenger::messenger(const mgo::instance& instance)
:
instance_(instance)
{
    instance_.create
}

mgo::messenger::~messenger() noexcept
{

}

[[nodiscard]] VkDebugUtilsMessengerEXT mgo::messenger::data() noexcept
{
    return messenger_;
}

[[nodiscard]] VkDebugUtilsMessengerCreateInfoEXT mgo::messenger::get_VkDebugUtilsMessengerCreateInfoEXT() noexcept
{
    VkDebugUtilsMessageSeverityFlagsEXT messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    
    VkDebugUtilsMessageTypeFlagsEXT messageType =
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    
    VkDebugUtilsMessengerCreateInfoEXT createInfo =
    {
        .sType              = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .pNext              = nullptr,
        .flags              = 0,
        .messageSeverity    = messageSeverity,
        .messageType        = messageType,
        .pfnUserCallback    = error_callback,
        .pUserData          = nullptr
    };
    return createInfo;
}

VKAPI_ATTR VkBool32 VKAPI_CALL mgo::messenger::error_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                              VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                              void* pUserData) noexcept
{
    std::cerr << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

