#include "init.h"

#ifndef NDEBUG
#include <stdio.h>
#include <stdlib.h>

static ong_result_t
print_extensions ()
{
    uint32_t extension_count = 0;
    vkEnumerateInstanceExtensionProperties (NULL, &extension_count, NULL);

    VkExtensionProperties *extensions =
        malloc (sizeof(VkExtensionProperties) * extension_count);
    ONG_MALLOC_CHECK (extensions);
    vkEnumerateInstanceExtensionProperties (NULL, &extension_count, extensions);

    printf ("Available extensions:\n");
    for (uint32_t i = 0; i < extension_count; i++)
        printf ("\t- %s\n", extensions[i].extensionName);

    return ONG_SUCCESS;
}
#endif /* not NDEBUG */

static ong_result_t
create_instance(const char *title, ong_version_t* version,
                VkInstance *instance)
{
    VkApplicationInfo app_info = {0};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = title;
    app_info.applicationVersion =
        VK_MAKE_VERSION (version->major, version->minor, 0);
    app_info.pEngineName = "Onaga";
    app_info.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    app_info.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo create_info = {0};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions (&glfw_extension_count);

    create_info.enabledExtensionCount = glfw_extension_count;
    create_info.ppEnabledLayerNames = glfw_extensions;

    create_info.enabledLayerCount = 0;
    create_info.pNext = NULL;

    VkResult result = vkCreateInstance (&create_info, NULL, instance);
    if (result != VK_SUCCESS)
        return ONG_INITIALIZATION_ERROR;

    return ONG_SUCCESS;
}

GLFWwindow *
initWindow (ong_create_data_t *data)
{
    int init_code = glfwInit ();
    if(init_code != GLFW_TRUE)
        return NULL;

    glfwWindowHint (GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint (GLFW_RESIZABLE, GLFW_FALSE);

    return glfwCreateWindow (data->width, data->height,
                             data->title, NULL, NULL);
}

ong_result_t
init_vulkan (ong_window_t *window)
{
    #ifndef NDEBUG
    ong_result_t print_extensions_result = print_extensions();
    ONG_RETURN_IFN_SUCCESS(print_extensions_result);
    #endif /* not NDEBUG */

    ong_result_t instance_create_result = create_instance
        (window->create_data->title, &window->create_data->version,
         &window->instance);
    ONG_RETURN_IFN_SUCCESS(instance_create_result);

    return ONG_SUCCESS;
}

void
init_main_loop (GLFWwindow *window)
{
    while (!glfwWindowShouldClose (window))
        glfwPollEvents ();
}

void
cleanup (ong_window_t *window)
{
    glfwDestroyWindow (window->window);
    glfwTerminate ();
}
