#include "CPU_scheduler_header.h"

void priority_non_preemptive(SchedulerContext *ctx)
{
    reset_process_states(ctx);

    int completed = 0;
    int current_time = 0;
    bool is_completed[MAX_PROCESSES] = {false};

    while (completed < ctx->num_processes)
    {
        int best_idx = -1;

        for (int i = 0; i < ctx->num_processes; i++)
        {
            if (ctx->processes[i].arrival_time <= current_time && !is_completed[i])
            {
                if (best_idx == -1 ||
                    ctx->processes[i].priority < ctx->processes[best_idx].priority ||
                    (ctx->processes[i].priority == ctx->processes[best_idx].priority &&
                     ctx->processes[i].arrival_time < ctx->processes[best_idx].arrival_time) ||
                    (ctx->processes[i].priority == ctx->processes[best_idx].priority &&
                     ctx->processes[i].arrival_time == ctx->processes[best_idx].arrival_time &&
                     ctx->processes[i].pid < ctx->processes[best_idx].pid))
                {
                    best_idx = i;
                }
            }
        }

        if (best_idx == -1)
        {
            current_time++;
            continue;
        }

        current_time += ctx->processes[best_idx].burst_time;

        ctx->processes[best_idx].completion_time = current_time;
        ctx->processes[best_idx].is_completed = true;

        is_completed[best_idx] = true;
        completed++;
    }
      display_results(ctx, "PRIORITY_NON_PREEMPTIVE");
}
