#include "../include/philosopher.h"

int ft_atoi(const char *str)
{
    long long ln;
    size_t n;
    int sign;

    sign = 1;
    ln = 0;
    n = 0;
    while (str[n] == 32 || (9 <= str[n] && str[n] <= 13))
        n++;
    if (str[n] == '-')
        sign *= -1;
    if (str[n] == '+' || str[n] == '-')
        n++;
    while ('0' <= str[n] && str[n] <= '9')
    {
        if (ln != ((ln * 10) + (str[n] - '0') * sign) / 10 && sign > 0)
            return ((int)LONG_MAX);
        if (ln != ((ln * 10) + (str[n] - '0') * sign) / 10 && sign < 0)
            return ((int)LONG_MIN);
        ln = (ln * 10) + (str[n] - '0') * sign;
        n++;
    }
    return ((int)ln);
}

bool check_argv(char **argv)
{
    if (ft_atoi(argv[1]) <= 0)
        return false;
    return true;
}

bool check_input_format(int argc, char **argv)
{
    size_t i;
    size_t j;
    i = 1;
    if (!(argc == 5 || argc == 6))
    {
        printf("hi");
        return (false);
    }

    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            if (!('0' <= argv[i][j] && argv[i][j] <= '9'))
                return (false);
            j++;
        }
        i++;
    }
    return (check_argv(argv));
}

void write_input_env(t_input_env *env, int argc, char **argv) {
	pthread_mutex_t forks[200];
    env->number_of_philosophers = ft_atoi(argv[1]);
    env->time_to_die = ft_atoi(argv[2]);
    env->time_to_eat = ft_atoi(argv[3]);
    env->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        env->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    env->forks = &forks[200];
}
