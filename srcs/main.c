#include "../include/philosopher.h"

void get_fork(t_philo *input)
{
    pthread_mutex_lock(input->right_fork);
    pthread_mutex_lock(&input->env->lock);
    if(input->env->is_everyone_dead == 0&& input->is_finished_flag == 1)
		printf("%lld %zu has taken a fork\n",ft_get_time(input->env->start_thread_time * 1000) / 1000,input->index);
    pthread_mutex_unlock(&input->env->lock);

    pthread_mutex_lock(input->left_fork);
    pthread_mutex_lock(&input->env->lock);

    if(input->env->is_everyone_dead == 0&& input->is_finished_flag == 1)
	{
        printf("%lld %zu has taken a fork\n",ft_get_time(input->env->start_thread_time * 1000) / 1000,input->index);
    }
    pthread_mutex_unlock(&input->env->lock);
}

void drop_fork(t_philo *input)
{
    pthread_mutex_unlock(input->right_fork);
    pthread_mutex_unlock(input->left_fork);
}




void philo_sleep(t_philo * input)
{
    pthread_mutex_lock(&input->env->lock);
    if(input->env->is_everyone_dead == 0&& input->is_finished_flag == 1)
		printf("%lld %zu is sleeping\n",ft_get_time(input->env->start_thread_time * 1000) / 1000,input->index);
    if(input->eat_count >= input->env->number_of_must_eat && input->env->number_of_must_eat != -1)
    {
        //printf("%lld %zu has acomplished eat_count:%d\n",ft_get_time(input->env->start_thread_time * 1000) / 1000,input->index,input->eat_count);
        input->is_finished_flag = 0;
        input->env->is_finished++;
    }
    pthread_mutex_unlock(&input->env->lock);
    ft_usleep(input->env->time_to_sleep * 1000);
    
}
void philo_think(t_philo * input)
{
    pthread_mutex_lock(&input->env->lock);
	if(input->env->is_everyone_dead == 0&& input->is_finished_flag == 1)
	    printf("%lld %zu is thinking\n",ft_get_time(input->env->start_thread_time * 1000) / 1000,input->index);
    pthread_mutex_unlock(&input->env->lock);

}
void philo_eat(t_philo * input)
{
    get_fork(input);
    pthread_mutex_lock(&input->plock);
    input->eat_status = 1;
    input->eat_count++;
    input->ideal_death_time = ft_get_time(0) / 1000 + input->env->time_to_die;
    input->eat_status = 0;
    
    if(input->env->is_everyone_dead == 0 && input->is_finished_flag == 1)
        printf("%lld %zu is eating\n",ft_get_time(input->env->start_thread_time * 1000) / 1000,input->index);
    pthread_mutex_unlock(&input->plock);
    //printf("now time: %zu first%lld\n",input->index, ft_get_time(0));
    //printf("marai said:%lld\n",input->env->time_to_eat);

    //printf("now time %zu second:%lld\n", input->index,ft_get_time(0) / 1000);
    ft_usleep(input->env->time_to_eat * 1000);
    //printf("now time %zu second:%lld\n", input->index,ft_get_time(0) / 1000);
    //printf("now time %zu second:%lld\n", input->index,ft_get_time(0));
	//printf("ideal time:%lld\n",ft_get_time(input->ideal_death_time));
    drop_fork(input);
}
void *waiter(void * arg)
{
    t_philo *input;
    input = (t_philo *)arg;
    while(input->env->is_everyone_dead == 0&& input->is_finished_flag == 1)
    {
        pthread_mutex_lock(&input->plock);
		if((ft_get_time(input->ideal_death_time * 1000)/ 1000) > 0 && input->eat_status == 0)// 時間 over flow
        {
			pthread_mutex_lock(&input->env->lock);
			if(input->env->is_everyone_dead == 0)
				printf("%lld %zu died\n",ft_get_time(input->env->start_thread_time * 1000) / 1000,input->index);
			input->env->is_everyone_dead++;
			pthread_mutex_unlock(&input->env->lock);
			pthread_mutex_unlock(&input->plock);
            return((void *)0);
        }
		pthread_mutex_unlock(&input->plock);
        usleep(200);
    }
    return((void *)0);
}

// StartTimeMeal____ ____ ____

void *routine(void *arg)
{
    t_philo * input;
    input = (t_philo *) arg;
    
    if(input->index % 2 == 1)
        ft_usleep(input->env->time_to_eat * 1000);
     //   ft_usleep(input->env->time_to_eat);
    
    
    input->ideal_death_time = ft_get_time(0) / 1000+ input->env->time_to_die;
    pthread_create(&input->waiter_id,NULL,waiter,input);
    
    while(input->env->is_everyone_dead == 0)
    {
        //printf("ElonMusksaid:%zu\n",input->index);
        //input->start_time_meal = ft_get_time(0);
        
        philo_eat(input);
        
        philo_sleep(input);
        //printf("now time %zu second:%lld\n", input->index,ft_get_time(0));
        philo_think(input);
        //printf("now time %zu second:%lld\n", input->index,ft_get_time(0));
        
    }
    if(pthread_join(input->waiter_id,NULL))
	{
		printf("input:%lld\n%lld\n%lld\n",(ft_get_time(input->ideal_death_time * 1000) / 1000 * -1),input->env->time_to_die,(ft_get_time(input->ideal_death_time * 1000) /1000 *-1) - input->env->time_to_die);
		return((void *)1);
	}
	return((void *)0);
}

void *monitor(void *arg)
{
    t_philo * input;
    input = (t_philo *)arg;
    while(input->env->is_everyone_dead == 0)
    {
        
        pthread_mutex_lock(&input->env->lock);
        //printf("finished:%d,numphilo%d\n",input->env->is_finished,input->env->number_of_philosophers);
        if(input->env->is_finished >= input->env->number_of_philosophers)
        {
            //printf("ElonMUSK!!!!!\n");
            input->env->is_everyone_dead++;
        }
        pthread_mutex_unlock(&input->env->lock);
    }
    printf("is_finished:%d,num_of_philo:%d\n",input->env->is_finished,input->env->number_of_philosophers);
    return((void *)0);
}

void one_case(t_philo *input)
{
    pthread_mutex_lock(input->left_fork);
    printf("%lld %zu has taken a fork\n",ft_get_time(input->env->start_thread_time * 1000) / 1000,input->index);
    if(input->env->time_to_die >= input->env->time_to_eat)
        ft_usleep(input->env->time_to_eat * 1000);
    else
        ft_usleep(input->env->time_to_die * 1000);
    printf("%lld %zu died\n",ft_get_time(input->env->start_thread_time * 1000) / 1000,input->index);
    pthread_mutex_unlock(input->left_fork);
    
}
int init_thread(t_env *env)
{
	int  i;
    pthread_t monitor_id;

	i=0;
	if(env->number_of_philosophers == 1)
        one_case(&env->philo_id[0]);
    else
    {
        if(env->number_of_must_eat > 0)
        {
            //printf("must eat:%d\n",env->number_of_must_eat);
            if (pthread_create(&monitor_id, NULL, monitor, env) != 0)
                return 1;
        }
        env->start_thread_time = ft_get_time(0) / 1000;
        while(i < env->number_of_philosophers)
        {
            if(pthread_create(&env->thread_id[i],NULL,routine,&env->philo_id[i]))
                return(0);
            i++;
        }


        i=0;
        if (0 < env->number_of_must_eat)
            pthread_join(monitor_id, NULL);
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
    env->start_thread_time = ft_get_time(0) / 1000;
    env->is_everyone_dead = 0;
    env->is_finished = 0;
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
        env->philo_id[i].is_finished_flag = 1;
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

