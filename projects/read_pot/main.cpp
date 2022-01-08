
#include "task_schedular.h"
#include "tasks.h"

int main(void)
{
	init_app();

	// Create task schedular and add tasks
    CoOpSchedular::TaskSchedular schedular;
    
    // Setup application task main_task
    CoOpSchedular::Task task1("main_task", 100, main_task);
    schedular.add_task(task1);

    while(1)
    {
        schedular.run();
    }
}