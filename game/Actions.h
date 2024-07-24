
//ACTIONS
#define START_GAME "START GAME"                // COMMAND/n players names in csv
#define INITIATE_TIMER "INITIATE TIMER"        // COMMAND
#define SWITCH_MUTE "SWITCH MUTE"              // mutes buzzer
#define INITIATE_END_GAME "INITIATE END GAME"  // frontend signal to end game

//RESPONSES
#define SET_PLAYERS "SET PLAYERS\n"          // SET PLAYERS/n id,name,score
#define LAST_ROUND_SCORE "LAST ROUND SCORE"  // LAST ROUND SCORE/n roundNr, playerId, roundScore, shootTime
#define START_TIMER "START TIMER"            // CONFIRM TIMER START
#define CURRENT_TURN "CURRENT TURN"          // send the info about current turn // playerid, turnNr
#define END_GAME "END GAME"                  // ends game