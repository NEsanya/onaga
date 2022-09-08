#include "onaga.h"
#include "vulkan/init.h"

extern ong_result_t
init_onaga (ong_create_data_t create_data)
{
    ong_window_t window;
    window.create_data = &create_data;

    window.window = init_window (window.create_data);
    if (window.window == NULL)
        return ONG_INITIALIZATION_ERROR;

    ong_result_t init_vulkan_result = init_vulkan (&window);
    ONG_RETURN_IFN_SUCCESS (init_vulkan_result);

    init_main_loop (window.window);

    cleanup (&window);
    return ONG_SUCCESS;
}
