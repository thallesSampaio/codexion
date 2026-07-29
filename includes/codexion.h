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
# include <limits.h>

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
	t_config			config;
	t_coder				*coders;
	t_dongle			*dongles;
	pthread_mutex_t		log_mutex;
	pthread_mutex_t		state_mutex;
	int					simulation_stop;
	long long			start_time;
	unsigned long long	next_sequence;
	pthread_t			monitor_thread;
}	t_engine;

/* --- Parsing & Utils --- */
int			parse_args(int argc, char **argv, t_config *config);
int			parse_numeric_args(char **argv, t_config *config);
int			parse_positive_ll(const char *str, long long *value);
int			parse_positive_int(const char *str, int *value);
int			validate_numeric_values(t_config *config);
int			parse_scheduler(const char *str, t_sched *scheduler);
void		print_parser_error(void);
long long	get_time_ms(void);
void		log_state(t_coder *coder, const char *state);

/* Initialization */
int		init_engine(t_engine *engine, t_config config);
int		init_dongles(t_engine *engine);
void	init_coders(t_engine *engine);

/* Cleanup */
void	cleanup_engine(t_engine *engine);

/* Heap */
t_heap	*heap_create(int capacity);
void	heap_destroy(t_heap *heap);
int		heap_push(t_heap *heap, t_request request, t_sched sched);
int		heap_peek(t_heap *heap, t_request *request);
int		heap_pop(t_heap *heap, t_sched sched, t_request *request);
int		request_has_priority(t_request a, t_request b, t_sched sched);
void	swap_requests(t_request *a, t_request *b);

/* Simulation */
int		run_simulation(t_engine *engine);
void	*coder_routine(void *arg);

#endif
