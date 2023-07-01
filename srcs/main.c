#include "../include/philosopher.h"

int	ft_usleep(useconds_t time)
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


void take_forks(t_philo* input)
{
    pthread_mutex_lock(input->right_fork);
    printf("%lld %zu has taken a fork\n",ft_get_time()- input->env->initial_time,input->index);
    pthread_mutex_lock(input->left_fork);
    printf("%lld %zu has taken a fork\n",ft_get_time()- input->env->initial_time,input->index);     
}

void drop_forks(t_philo* input)
{
    pthread_mutex_unlock(input->right_fork);
    pthread_mutex_unlock(input->left_fork);
}

int p_eat(t_philo *input)
{
    take_forks(input);
    pthread_mutex_lock(&input->env->lock);
    input->eat_status++;
    printf("%lld %zu is eating\n",ft_get_time() - input->env->initial_time,input->index);
    pthread_mutex_unlock(&input->env->lock);
    pthread_mutex_lock(&input->plock);
    input->eat_count++;
    input->start_time_meal = ft_get_time();
    ft_usleep(input->env->time_to_eat);
    input->end_time_meal = ft_get_time();
    printf("input:%lld,inptt:%lld\n",input->start_time_meal ,input->end_time_meal);
    pthread_mutex_unlock(&input->plock);
    drop_forks(input);
    
    //if(input->env->number_of_must_eat != -1 && input->eat_count >= input->env->number_of_must_eat)
    //    input->env->num_of_eat++;    
    return 0;
}

int p_sleep(t_philo *input)
{
    pthread_mutex_lock(&input->plock);
    input->eat_status--;
    pthread_mutex_unlock(&input->plock);
    printf("%lld %zu is sleeping\n",ft_get_time()- input->env->initial_time,input->index);
    ft_usleep(input->env->time_to_sleep);
    //ft_usleep(input);
    return(0);
}

int p_think(t_philo *input)
{
    printf("%lld %zu is thinking\n",ft_get_time()- input->env->initial_time,input->index);
    return(0);
}

//void *waiter_thread(void *arg)
//{
//    t_philo *input;
//    input = (t_philo *)arg;

//    while(input->env->is_finished == 0)
//    {
//        pthread_mutex_lock(&input->env->lock);
//        if(input->env->is_finished >= 1)
//        {
//            pthread_mutex_unlock(&input->env->lock);
//            printf("Hey Elon!==============\n");
//            return((void *) 1);
//        }
//        pthread_mutex_unlock(&input->env->lock);
//        usleep(1);
//    }
//    return((void *)1);
//}

// _1_ 0__

void *monitor_thread(void *arg)
{
    t_philo *input;
    input = (t_philo*)arg;

    while(input->env->is_everyone_dead == 0)
    {
        pthread_mutex_lock(&input->env->lock);
        printf("%lld - %lld =( %lld)>%lld\n",ft_get_time(),input->start_time_meal,ft_get_time()-input->start_time_meal,input->env->time_to_die);
        if (ft_get_time() - input->start_time_meal >input->env->time_to_die && input->eat_status == 0)
		{

            printf("%lld %zu is died_a\n",ft_get_time() - input->env->initial_time,input->index);
        	return((void *)0);
        }
        //if (ft_get_time() - input->end_time_meal > input->env->time_to_sleep && input->eat_status == 0)
        //{
        //    printf("%lld,%lld\n",ft_get_time() - input->end_time_meal , input->env->time_to_sleep);
        //    printf("%lld %zu is died_b\n",ft_get_time() - input->env->initial_time,input->index);
        //    return((void *)0);
        //}
        //if(ft_get_time() - (input->start_time_meal) > input->env->time_to_die)
        //{
        //    printf("%lld %zu is died_c\n",ft_get_time()- input->env->initial_time,input->index);
        //    return((void *)0);
        //}

        //if (philo->eat_cont == philo->data->meals_nb)
		//{
		//	pthread_mutex_lock(&philo->data->lock);
		//	philo->data->finished++;
		//	philo->eat_cont++;
		//	pthread_mutex_unlock(&philo->data->lock);
		//}
        printf("is_finished :%d\n",input->env->is_finished);
        if(input->env->is_finished >= input->env->number_of_philosophers)
            input->env->is_everyone_dead++;
        pthread_mutex_unlock(&input->env->lock);
        sleep(1);
        return((void *)1);
    }

	return ((void *)0);
}

void * routine(void *arg){
	t_philo *input;
	input = (t_philo *)arg;

    if(input->index % 2 == 1)
        ft_usleep (input->env->time_to_eat);
    input->start_time_meal = ft_get_time();
    if(pthread_create(&input->monitor_id,NULL,monitor_thread,input))
    {
        return ((void *)1);
    }
    while(input->env->is_finished == 0)
	{
        if(p_eat(input) == 1)
            return((void *)0);
        if(p_sleep(input) == 1)
            return((void *)0);
        if(p_think(input) == 1)
            return((void *)0);
	}
    if (pthread_join(input->monitor_id, NULL))
         return ((void *)1);
	return((void*)0);
}

int init_thread(t_env *env)
{
	int  i;
    //pthread_t waiter;
    //void* status;

	i=0;
	if(env->number_of_philosophers == 1)
        one_case(&env->philo_id[0]);
    else
    {
        //if (pthread_create(&waiter, NULL, &waiter_thread, &env) != 0)
        //{
        //    printf("died!!!!!!!\n");
        //    return 1;
        //}
        
        while(i < env->number_of_philosophers)
        {
            if(pthread_create(&env->thread_id[i],NULL,routine,&env->philo_id[i]))
                return(0);
            //pthread_create(&monitor_id,NULL,monitor,env);
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
    env->initial_time = 0;
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

