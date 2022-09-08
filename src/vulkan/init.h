#ifndef VULKAN_INIT_H
#define VULKAN_INIT_H

#include "../util.h"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

typedef struct
{
    ong_create_data_t *create_data;
    GLFWwindow* window;
    VkInstance instance;
} ong_window_t;

GLFWwindow *
init_window (ong_create_data_t *data);

ong_result_t
init_vulkan (ong_window_t *window);

void
init_main_loop (GLFWwindow *window);

void
cleanup (ong_window_t *window);

#endif
