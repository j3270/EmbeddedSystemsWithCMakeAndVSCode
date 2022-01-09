
#include "tasks.h"

int main(void)
{
    init_app();

	// Create task schedular and add tasks
    CoOpSchedular::TaskSchedular schedular;
    
    // Setup application task main_task
    CoOpSchedular::Task task1("toggle_led", get_schedular_ticks_from_ms(100), toggle_led);
    schedular.add_task(task1);

    CoOpSchedular::Task task2("read_pot", get_schedular_ticks_from_ms(5), read_pot);
    schedular.add_task(task2);

    CoOpSchedular::Task task3("set_servo_position", get_schedular_ticks_from_ms(20), set_servo_position);
    schedular.add_task(task3);

    while(1)
    {
        schedular.run();
    } 
}
