#include "CPU_scheduler_header.h"

void priority_preemptive_rr(SchedulerContext *ctx, int time_quantum)
{
    if (time_quantum <= 0)
    {
        fprintf(stderr, "Error: Time quantum must be positive\n");
        return;
    }

    reset_process_states(ctx);

    int current_time = 0;
    int completed = 0;

    int rr_queue[MAX_PROCESSES];
    int rr_count = 0;

    int current_priority = INT_MAX;

    while (completed < ctx->num_processes)
    {
        int highest_priority = INT_MAX;

        for (int i = 0; i < ctx->num_processes; i++)
        {
            if (ctx->processes[i].remaining_time > 0 &&
                ctx->processes[i].arrival_time <= current_time &&
                ctx->processes[i].priority < highest_priority)
            {
                highest_priority = ctx->processes[i].priority;
            }
        }

        if (highest_priority == INT_MAX)
        {
            current_time++;
            rr_count = 0;
            current_priority = INT_MAX;
            continue;
        }

        if (highest_priority != current_priority)
        {
            rr_count = 0;
            current_priority = highest_priority;

            for (int i = 0; i < ctx->num_processes; i++)
            {
                if (ctx->processes[i].remaining_time > 0 &&
                    ctx->processes[i].arrival_time <= current_time &&
                    ctx->processes[i].priority == current_priority)
                {
                    rr_queue[rr_count++] = i;
                }
            }
        }
        else
        {
            for (int i = 0; i < ctx->num_processes; i++)
            {
                bool already_in_queue = false;

                if (ctx->processes[i].remaining_time > 0 &&
                    ctx->processes[i].arrival_time <= current_time &&
                    ctx->processes[i].priority == current_priority)
                {
                    for (int j = 0; j < rr_count; j++)
                    {
                        if (rr_queue[j] == i)
                        {
                            already_in_queue = true;
                            break;
                        }
                    }

                    if (!already_in_queue)
                    {
                        rr_queue[rr_count++] = i;
                    }
                }
            }
        }

        if (rr_count == 0)
        {
            current_time++;
            continue;
        }

        int idx = rr_queue[0];

        for (int i = 1; i < rr_count; i++)
            rr_queue[i - 1] = rr_queue[i];
        rr_count--;

        int run_time = time_quantum;
        if (ctx->processes[idx].remaining_time < run_time)
            run_time = ctx->processes[idx].remaining_time;

        bool preempted_by_higher = false;

        for (int t = 0; t < run_time; t++)
        {
            ctx->processes[idx].remaining_time--;
            current_time++;

            if (ctx->processes[idx].remaining_time == 0)
            {
                ctx->processes[idx].completion_time = current_time;
                ctx->processes[idx].is_completed = true;
                completed++;
                break;
            }

            for (int j = 0; j < ctx->num_processes; j++)
            {
                if (ctx->processes[j].remaining_time > 0 &&
                    ctx->processes[j].arrival_time <= current_time &&
                    ctx->processes[j].priority < current_priority)
                {
                    preempted_by_higher = true;
                    break;
                }
            }

            if (preempted_by_higher)
                break;
        }

        if (ctx->processes[idx].remaining_time > 0)
        {
            if (preempted_by_higher)
            {
                rr_count = 0;
                current_priority = INT_MAX;
            }
            else
            {
                rr_queue[rr_count++] = idx;
            }
        }
    }

    display_results(ctx, "PRIORITY_PREEMPTIVE_WITH_RR");
}
