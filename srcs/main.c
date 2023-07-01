#include "../include/philosopher.h"

void get_fork(t_philo *input)
{
    pthread_mutex_lock(input->right_fork);
    pthread_mutex_lock(&input->env->lock);
    printf("%lld %zu has taken a fork\n",ft_get_time(input->env->start_thread_time),input->index);
    pthread_mutex_unlock(&input->env->lock);

    pthread_mutex_lock(input->left_fork);
    pthread_mutex_lock(&input->env->lock);
    printf("%lld %zu has taken a fork\n",ft_get_time(input->env->start_thread_time),input->index);
    pthread_mutex_unlock(&input->env->lock);

    pthread_mutex_lock(&input->env->lock);
    printf("%lld %zu is eating\n",ft_get_time(input->env->start_thread_time),input->index);
    pthread_mutex_unlock(&input->env->lock);
}

void drop_fork(t_philo *input)
{
    pthread_mutex_unlock(input->right_fork);
    pthread_mutex_unlock(input->left_fork);

}


void philo_eat(t_philo * input)
{
    get_fork(input);
    pthread_mutex_lock(&input->plock);
    input->eat_status = 1;
    input->eat_count++;
    ft_usleep(input->env->time_to_eat);
    input->ideal_death_time = ft_get_time(0) + input->env->time_to_die;
    //printf("ideal time:%lld\n",ft_get_time(input->ideal_death_time));
    input->eat_status = 0;
    pthread_mutex_unlock(&input->plock);
    drop_fork(input);
}
void philo_sleep(t_philo * input)
{
    pthread_mutex_lock(&input->env->lock);
    printf("%lld %zu is sleeping\n",ft_get_time(input->env->start_thread_time),input->index);
    pthread_mutex_unlock(&input->env->lock);
    ft_usleep(input->env->time_to_sleep);
    
}
void philo_think(t_philo * input)
{
    pthread_mutex_lock(&input->env->lock);
    printf("%lld %zu is thinking\n",ft_get_time(input->env->start_thread_time),input->index);
    pthread_mutex_unlock(&input->env->lock);
}

void *waiter(void * arg)
{
    t_philo *input;
    input = (t_philo *)arg;
    while(input->env->is_everyone_dead == 0)
    {
        //printf("ninput:%lld\n%lld\n%lld\n",(ft_get_time(input->ideal_death_time) *-1),input->env->time_to_die,(ft_get_time(input->ideal_death_time) *-1) - input->env->time_to_die);

        if((ft_get_time(input->ideal_death_time) * -1) < 0 && input->eat_status == 0)// 時間 over flow
        {
			pthread_mutex_lock(&input->env->lock);
            printf("input:%lld\n%lld\n%lld\n",(ft_get_time(input->ideal_death_time) *-1),input->env->time_to_die,(ft_get_time(input->ideal_death_time) *-1) - input->env->time_to_die);
            input->env->is_everyone_dead++;
			pthread_mutex_unlock(&input->env->lock);
            return((void *)0);
        }
    }
    return((void *)0);
}

// StartTimeMeal____ ____ ____

void *routine(void *arg)
{
    t_philo * input;
    input = (t_philo *) arg;
    
    if(input->index %2 == 1)
        ft_usleep(input->env->time_to_eat);
    pthread_t   waiter_id;
    
    input->ideal_death_time = ft_get_time(0) + input->env->time_to_die;
    pthread_create(&waiter_id,NULL,waiter,input);
    
    while(input->env->is_everyone_dead == 0)
    {
        //printf("ElonMusksaid:%zu\n",input->index);
        input->start_time_meal = ft_get_time(0);
        philo_eat(input);
        philo_sleep(input);
        philo_think(input);
        
    }
    if(pthread_join(waiter_id,NULL))
		return((void *)1);
    return((void *)0);
}

void *monitor(void *arg)
{
    t_philo * input;
    input = (t_philo *)arg;
    while(input->env->is_everyone_dead != 0)
    {
        
        pthread_mutex_lock(&input->env->lock);
        if(input->env->is_finished >= input->env->number_of_philosophers)
            input->env->is_everyone_dead++;
        pthread_mutex_unlock(&input->env->lock);
    }
    return((void *)0);
}

void one_case(t_philo *input)
{
    (void)input;
    printf("sasasa\n");
}
int init_thread(t_env *env)
{
	int  i;
    pthread_t waiter;

	i=0;
	if(env->number_of_philosophers == 1)
        one_case(&env->philo_id[0]);
    else
    {
        if(env->number_of_must_eat > 0)
        {
            if (pthread_create(&waiter, NULL, &monitor, &env) != 0)
            {
                printf("died!!!!!!!\n");
                return 1;
            }
        }
        env->start_thread_time = ft_get_time(0);
        while(i < env->number_of_philosophers)
        {
            if(pthread_create(&env->thread_id[i],NULL,routine,&env->philo_id[i]))
                return(0);
            i++;
        }


        i=0;
        while(i < env->number_of_philosophers)
        {
            pthread_join(env->thread_id[i],NULL);
            i++;
        }
        }
    return 0;
}

int init_alloc(t_env *env)
{
	int i;
	i = 0;
    env->start_thread_time = ft_get_time(0);
    env->is_everyone_dead = 0;
	while(i < env->number_of_philosophers)
	{
		if(pthread_mutex_init(&env->fork_id[i],NULL) != 0 || pthread_mutex_init(&env->lock,NULL) != 0)
			return 1;
		i++;
	}
	i = 0;
	while(i< env->number_of_philosophers)
	{
		if(i == 0)
		{
			env->philo_id[0].left_fork = &env->fork_id[0];
			env->philo_id[0].right_fork = &env->fork_id[env->number_of_philosophers - 1];
		}
		else
		{
		    env->philo_id[i].left_fork = &env->fork_id[i];
		    env->philo_id[i].right_fork = &env->fork_id[i-1];
		}
        pthread_mutex_init(&env->philo_id[i].plock,NULL);
		env->philo_id[i].index = i;
		env->philo_id[i].eat_count = 0; // eat_countの初期化
		env->philo_id[i].env = env; // 所属するenvの設定
        env->philo_id[i].eat_status = 0;
        env->philo_id[i].end_time_meal = env->time_to_eat;
		i++;
	}
	return 0;
}


int main(int argc, char **argv)
{
	t_env env;

	if (check_input_format(argc, argv))
	{
		alloc_input_env(&env, argc, argv);    
		if(init_alloc(&env)!= 0)
			return 1;
		if(init_thread(&env)!= 0)
			return 1;
	}
	else
	{
		printf("your input is incorrect\n");
		return 1;
	}
	return 0;
}

