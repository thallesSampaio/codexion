/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thasampa <thasampa@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 16:44:08 by thasampa          #+#    #+#             */
/*   Updated: 2026/07/24 16:44:09 by thasampa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_sched
{
	CX_SCHED_FIFO,
	CX_SCHED_EDF
}	t_sched;

typedef struct s_request
{
	int			coder_id;
	long long	arrival_time;
	long long	deadline;
}	t_request;

typedef struct s_heap
{
	t_request	*data;
	int			capacity;
	int			size;
}	t_heap;

typedef struct s_config
{
	int			num_coders;
	long long	time_to_burnout;
	long long	time_to_compile;
	long long	time_to_debug;
	long long	time_to_refactor;
	int			num_compiles_required;
	long long	dongle_cooldown;
	t_sched		scheduler;
}	t_config;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_heap			*queue;
	int				is_in_use;
	long long		last_released_time;
}	t_dongle;

struct	s_engine;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	long long		last_compile_start;
	int				compiles_done;
	struct s_engine	*engine;
}	t_coder;

typedef struct s_engine
{
	t_config		config;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	state_mutex;
	int				simulation_stop;
	long long		start_time;
	pthread_t		monitor_thread;
}	t_engine;

/* --- Parsing & Utils --- */
int			parse_args(int argc, char **argv, t_config *config);
long long	get_time_ms(void);
void		log_state(t_coder *coder, const char *state);

/* --- Engine Init & Cleanup --- */
int			init_engine(t_engine *engine, t_config config);
void		cleanup_engine(t_engine *engine);

/* --- Heap (Priority Queue) --- */
t_heap		*heap_create(int capacity);
void		heap_push(t_heap *heap, t_request req, t_sched sched);
t_request	heap_pop(t_heap *heap, t_sched sched);
void		heap_destroy(t_heap *heap);
int			is_higher_priority(t_request a, t_request b, t_sched sched);
void		swap_req(t_request *a, t_request *b);

#endif
