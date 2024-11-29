#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

typedef enum
{
	config,
	idle_auto,
	random_auto,
	read_color_auto,
	solve_auto,
	fast,
	slow,
	idle_man,
}State_t;

typedef enum
{
	Taster_T_L,
	Taster_T_R,
	Taster_B_L,
	Taster_B_R,
	msg_random,
	msg_read_color,
	msg_send_cube,
	msg_solve,
	default_event,
}Event_t;


typedef struct {
    State_t current_state;
    Event_t event;
    State_t next_state;
    void (*action)(void);
} State_Transition;


void auto_to_random_Handler(void);
void auto_to_read_color_Handler(void);
void auto_to_solve_Handler(void);
void solve_to_fast_Handler(void);
void solve_to_slow_Handler(void);
void back_to_auto(void);

void config_to_man_Handler(void);
void man_to_random_Handler(void);
void man_to_read_color_Handler(void);
void man_to_send_cube_Handler(void);
void man_to_solve_Handler(void);

void super_machine();

extern Event_t new_event;
extern char buf_name_white[6];
extern char buf_name_yellow[5];
extern char buf_name_red[4];
extern char buf_name_green[6];
extern char buf_name_orange[7];
extern char buf_name_blue[5];

#endif /* STATE_MACHINE_H_ */
