#include "../include/philosopher.h"

//void mutex_printf(t_philo *input,long long second,size_t index,)
//{
//    pthread_
//}

int	ft_usleep(useconds_t time)//why
{
	u_int64_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void one_case(t_philo *input)
{
    printf("here is one case\n");
    pthread_mutex_lock(input->right_fork);
    printf("%lld %zu has taken a fork\n",ft_get_time()- input->env->initial_time,input->index);
    ft_usleep(input->env->time_to_die);    
    pthread_mutex_unlock(input->right_fork);
}

void p_eat(t_philo *input)
{
    pthread_mutex_lock(input->right_fork);
    printf("%lld %zu has taken a fork\n",ft_get_time()- input->env->initial_time,input->index);
    pthread_mutex_lock(input->left_fork);
    printf("%lld %zu has taken a fork\n",ft_get_time()- input->env->initial_time,input->index);
    printf("%lld %zu is eating\n",ft_get_time()- input->env->initial_time,input->index);
    ft_usleep(input->env->time_to_eat);
    input->eat_count++;
    input->last_meal_time = ft_get_time();
    pthread_mutex_unlock(input->right_fork);
    pthread_mutex_unlock(input->left_fork);

}

void p_sleep(t_philo *input)
{
    printf("%lld %zu is sleeping\n",ft_get_time()- input->env->initial_time,input->index);
    ft_usleep(input->env->time_to_sleep);
    //ft_usleep(input);
}

void p_think(t_philo *input)
{
    printf("%lld %zu is thinking\n",ft_get_time()- input->env->initial_time,input->index);
}

int monitor(t_philo *input)
{
    pthread_mutex_lock(&input->env->lock);
    if(input->env->is_finished == 0)
    {
        pthread_mutex_unlock(&input->env->lock);
        return(0);
    }
    else
        return(1);
}

void * routine(void *arg){
	t_philo *input;
	input = (t_philo *)arg;
    if(input->index % 2 == 0)
        ft_usleep (input->env->time_to_eat);
    input->last_meal_time = ft_get_time();
    while(1)
	{
        if(monitor(input) == 1)
        {
            pthread_mutex_unlock(&input->env->lock);
            return((void *)0);
        }
        p_eat(input);
        if(monitor(input) == 1)
        {
            pthread_mutex_unlock(&input->env->lock);
            return((void *)0);
        }
        if(input->env->number_of_must_eat != -1 && input->eat_count >= input->env->number_of_must_eat)
        {
            pthread_mutex_lock(&input->env->lock);
            printf("%lld %zu died\n",ft_get_time()- input->env->initial_time,input->index);
            input->env->is_finished++;
            pthread_mutex_unlock(&input->env->lock);
            return((void*)0);
        }
        if(monitor(input) == 1)
        {
            pthread_mutex_unlock(&input->env->lock);
            return((void *)0);
        }
        p_sleep(input);
        if(monitor(input) == 1)
        {
            pthread_mutex_unlock(&input->env->lock);
            return((void *)0);
        }
        if(input->env->time_to_eat + input->env->time_to_sleep >= input->env->time_to_die)
        {
            pthread_mutex_lock(&input->env->lock);
            printf("%lld %zu died\n",ft_get_time()- input->env->initial_time,input->index);
            input->env->is_finished++;
            pthread_mutex_unlock(&input->env->lock);
            return((void*)0);
        }
        p_think(input);
	}
	return((void*)0);
}

int init_thread(t_env *env)
{
	size_t  i;
	i=0;
	if(env->number_of_philosophers == 1)
        one_case(&env->philo_id[0]);
    else
    {
	while(i < env->number_of_philosophers)
	{
    	pthread_create(&env->thread_id[i],NULL,routine,&env->philo_id[i]);
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
	size_t i;
	i = 0;
    env->initial_time = 0;
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
		env->philo_id[i].index = i;
		env->philo_id[i].eat_count = 0; // eat_countの初期化
		env->philo_id[i].env = env; // 所属するenvの設定
		i++;
	}
	return 0;
}


int main(int argc, char **argv)
{
	t_env env;

	if (check_input_format(argc, argv))
	{
		//printf("your arg is correct\n");
		alloc_input_env(&env, argc, argv);    
		//printf("argv[1]:%zu\n", env.number_of_philosophers);
		//printf("argv[2]:%lld\n", env.time_to_die);
		//printf("argv[3]:%zu\n", env.time_to_eat);
		//printf("argv[4]:%zu\n", env.time_to_sleep); 
		//printf("argv[5]:%d\n", env.number_of_must_eat);
		if(init_alloc(&env)!= 0)
			return 1;
		env.initial_time = ft_get_time();

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

