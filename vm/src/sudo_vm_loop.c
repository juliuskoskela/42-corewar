

void    init_players()
{
    byte    *last_alive = arena.mem[MEM_SIZE / player_count * (player_count - 1)]; //youngest player
    int     cycles_executed = 0;
    int     lives_since_last_check = 0;
    int     cycle_to_die = CYCLE_TO_DIE;
    int     checks_performed = 0;


    //a carriage is placed at the beginning of each champion in the arena.
    struct carriage {
        int unique_number;
        int carry;
        // a value that statements can modify
        byte *statement_code;
        int last_live_cycle_nbr;
        // the number of the cycle in which the last live was stated.
        int cycles_until_carriage_position;
        // the number of cycles to be performed until the current carriage position.
        int carriage_position;
        int bytes_until_next_statement;
        // number of bytes to be traveled through until the next statement.
        int registries;
        // initialized at REG_NUMBER

        /*
        **
        The carriages will be made into a list. The head of the list will be the youngest palyer.
        **/

    }


}

void    gameloop(void)
{
    loop_struct;
    carriage_list;

    init_players();
    init_carriage_lst();
    introduce_players();
    while (more than one player alive)
    while (cycle < check live)
        while (all_players)
        {
            if (cycles to execute next command)
                wait
            else if (executable instruction)
                execute instruction
            else
                move pc
        }
        check if ()
        {
            /* code */
        }
        
}