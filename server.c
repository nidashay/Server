#include <stdio.h>
#include <uv.h>

uv_loop_t *loop;
uv_timer_t timer;

void timer_callback(uv_timer_t *handle) {
    printf("Timer callback triggered!\n");
}

int main() {
    loop = uv_default_loop();

    // Initialize the timer handle
    uv_timer_init(loop, &timer);

    // Start the timer: 1000ms delay, 2000ms repeat interval
    uv_timer_start(&timer, timer_callback, 1000, 2000);

    printf("Starting event loop...\n");
    // Run the loop (blocks until no active handles)
    uv_run(loop, UV_RUN_DEFAULT);

    // Cleanup
    uv_loop_close(loop);
    return 0;
}   
