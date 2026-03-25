#include "CPU_scheduler_header.h"

void shortest_job_first(SchedulerContext *ctx)
{
    reset_process_states(ctx);

    int completed = 0;
    int current_time = 0;
    bool is_completed[MAX_PROCESSES] = {false};

    while (completed < ctx->num_processes)
    {
        int best_idx = -1;
        int min_burst_time = INT_MAX;

        for (int i = 0; i < ctx->num_processes; i++)
        {
            if (ctx->processes[i].arrival_time <= current_time && !is_completed[i])
            {
                if (ctx->processes[i].burst_time < min_burst_time)
                {
                    min_burst_time = ctx->processes[i].burst_time;
                    best_idx = i;
                }
                else if (ctx->processes[i].burst_time == min_burst_time)
                {
                    if (best_idx == -1 ||
                        ctx->processes[i].arrival_time < ctx->processes[best_idx].arrival_time ||
                        (ctx->processes[i].arrival_time == ctx->processes[best_idx].arrival_time &&
                         ctx->processes[i].pid < ctx->processes[best_idx].pid))
                    {
                        best_idx = i;
                    }
                }
            }
        }

        if (best_idx == -1)
        {
            int next_arrival = INT_MAX;

            for (int i = 0; i < ctx->num_processes; i++)
            {
                if (!is_completed[i] &&
                    ctx->processes[i].arrival_time > current_time &&
                    ctx->processes[i].arrival_time < next_arrival)
                {
                    next_arrival = ctx->processes[i].arrival_time;
                }
            }

            if (next_arrival == INT_MAX)
            {
                break;
            }

            current_time = next_arrival;
        }
        else
        {
            current_time += ctx->processes[best_idx].burst_time;

            ctx->processes[best_idx].completion_time = current_time;
            ctx->processes[best_idx].is_completed = true;

            is_completed[best_idx] = true;
            completed++;
        }
    }

    display_results(ctx, "Shortest-Job-First (SJF)");
}
