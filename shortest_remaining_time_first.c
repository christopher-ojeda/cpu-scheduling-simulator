#include "CPU_scheduler_header.h"

void shortest_remaining_time_first(SchedulerContext *ctx)
{
    reset_process_states(ctx);

    int current_time = 0;
    int completed = 0;

    while (completed < ctx->num_processes)
    {
        int shortest = -1;
        int min_remaining_time = INT_MAX;

        for (int i = 0; i < ctx->num_processes; i++)
        {
            if (ctx->processes[i].arrival_time <= current_time &&
                ctx->processes[i].remaining_time > 0)
            {
                if (ctx->processes[i].remaining_time < min_remaining_time)
                {
                    min_remaining_time = ctx->processes[i].remaining_time;
                    shortest = i;
                }
                else if (ctx->processes[i].remaining_time == min_remaining_time)
                {
                    if (shortest == -1 ||
                        ctx->processes[i].arrival_time < ctx->processes[shortest].arrival_time ||
                        (ctx->processes[i].arrival_time == ctx->processes[shortest].arrival_time &&
                         ctx->processes[i].pid < ctx->processes[shortest].pid))
                    {
                        shortest = i;
                    }
                }
            }
        }

        if (shortest == -1)
        {
            current_time++;
            continue;
        }

        ctx->processes[shortest].remaining_time--;
        current_time++;

        if (ctx->processes[shortest].remaining_time == 0)
        {
            ctx->processes[shortest].completion_time = current_time;
            ctx->processes[shortest].is_completed = true;
            completed++;
        }
    }

    display_results(ctx, "Shortest-Remaining_Time-First (SRTF)");
}
