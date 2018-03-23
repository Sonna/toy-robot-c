#include <string.h>

#include "robot.h"


// //#include <assert.h>
// char** strsplit(char* sentence, const char delimiter)
// {
//   printf("strsplit\n");
//     char** result;//    = 0;
//     //size_t count     = 0;
//     //char* last_comma = 0;
//     //char delim[2];
//     //delim[0] = a_delim;
//     //delim[1] = 0;


//     // Count how many elements will be extracted.
//     size_t count = 0;
//     char* tmp = sentence;
//     while (*tmp)
//     {
//         if (delimiter == *tmp)
//         {
//             count++;
//             //last_comma = tmp;
//         }
//         tmp++;
//     }

//     // /* Add space for trailing token. */
//     // count += last_comma < (a_str + strlen(a_str) - 1);

//     // /* Add space for terminating null string so caller
//     //    knows where the list of returned strings ends. */
//     // count++;

//     result = malloc(sizeof(char*) * (count + 1));

//     int length = strlen(sentence);
//     int num = 0; // number of words
//     int n = 0; // number of characters, since last word

//     if (result) {
//       for (int i = 0; i < length; i++) {
//         printf("%c", sentence[i]);

//         if(sentence[i] == delimiter) {
//           printf("%s", sentence[i-n]);
//           strncpy(result[num], sentence[i-n], n);
//           num++;
//           n = 0;
//         }
//         n++;
//       }
//     printf("\n");

//     // {
//     //     size_t idx  = 0;
//     //     char* token = strtok(a_str, delim);

//     //     while (token)
//     //     {
//     //         assert(idx < count);
//     //         *(result + idx++) = strdup(token);
//     //         token = strtok(0, delim);
//     //     }
//     //     assert(idx == count - 1);
//     //     *(result + idx) = 0;
//     }

//     return result;
// }


char* turn_left(char* facing) {
  ht_hash_table* cardinal_counter_clockwise = ht_new();

  ht_insert(cardinal_counter_clockwise, "NORTH", "WEST");
  ht_insert(cardinal_counter_clockwise, "WEST", "SOUTH");
  ht_insert(cardinal_counter_clockwise, "SOUTH", "EAST");
  ht_insert(cardinal_counter_clockwise, "EAST", "NORTH");

  char* result = strdup(ht_search(cardinal_counter_clockwise, facing));

  ht_del_hash_table(cardinal_counter_clockwise);
  return result;
}

char* turn_right(char* facing) {
  ht_hash_table* cardinal_clockwise = ht_new();

  ht_insert(cardinal_clockwise, "NORTH", "EAST");
  ht_insert(cardinal_clockwise, "EAST", "SOUTH");
  ht_insert(cardinal_clockwise, "SOUTH", "WEST");
  ht_insert(cardinal_clockwise, "WEST", "NORTH");

  char* result = strdup(ht_search(cardinal_clockwise, facing));

  ht_del_hash_table(cardinal_clockwise);
  return result;
}

int move_x(char* facing) {
  ht_hash_table* cardinal_x_movement = ht_new();

  ht_insert(cardinal_x_movement, "NORTH", "0");
  ht_insert(cardinal_x_movement, "EAST", "1");
  ht_insert(cardinal_x_movement, "SOUTH", "0");
  ht_insert(cardinal_x_movement, "WEST", "-1");

  char* result = strdup(ht_search(cardinal_x_movement, facing));

  ht_del_hash_table(cardinal_x_movement);
  return atoi(result);
}

int move_y(char* facing) {
  ht_hash_table* cardinal_y_movement = ht_new();

  ht_insert(cardinal_y_movement, "NORTH", "1");
  ht_insert(cardinal_y_movement, "EAST", "0");
  ht_insert(cardinal_y_movement, "SOUTH", "-1");
  ht_insert(cardinal_y_movement, "WEST", "0");

  char* result = strdup(ht_search(cardinal_y_movement, facing));

  ht_del_hash_table(cardinal_y_movement);
  return atoi(result);
}


Robot* robot_new(const int x, const int y, const char* facing) {
  Robot* robot = malloc(sizeof(Robot));

  robot->x = x;
  robot->y = y;
  robot->facing = strdup(facing);

  return robot;
}

void robot_destroy(Robot* robot) {
  free(robot);
}

// Robot robot_report(const Robot robot) {
void robot_report(const Robot* robot) {
  printf("%d,%d,%s\n", robot->x, robot->y, robot->facing);
}

void robot_left(Robot* robot) {
  strncpy(robot->facing, turn_left(robot->facing), 5);
}

void robot_right(Robot* robot) {
  strncpy(robot->facing, turn_right(robot->facing), 5);
}

void robot_move(Robot* robot) {
  robot->x += move_x(robot->facing);
  robot->y += move_y(robot->facing);

  if (robot->x < 0 || robot->x > 4) {
    robot->x -= move_x(robot->facing);
  }

  if (robot->y < 0 || robot->y > 4) {
    robot->y -= move_y(robot->facing);
  }
}

void robot_place(Robot* robot, char* raw_coordinates) {
  // printf("robot_place: %s \n", raw_coordinates);
  robot->x = atoi(&raw_coordinates[0]);
  robot->y = atoi(&raw_coordinates[2]);
  strncpy(robot->facing, raw_coordinates + 4, 5);
}

void robot_exec(Robot* robot, char* raw_command, char* raw_args) {
  int switch_num;
  char* result;
  ht_hash_table* known_commands = ht_new();

  ht_insert(known_commands, "PLACE", "0");
  ht_insert(known_commands, "MOVE", "1");
  ht_insert(known_commands, "LEFT", "2");
  ht_insert(known_commands, "RIGHT", "3");
  ht_insert(known_commands, "REPORT", "4");

  result = ht_search(known_commands, raw_command);

  if (result != NULL) {
    switch_num = atoi(result);

    switch(switch_num) {
    case 0:
      // printf("robot_exec: %s \n", raw_args);
      robot_place(robot, raw_args);
      break;
    case 1:
      robot_move(robot);
      break;
    case 2:
      robot_left(robot);
      break;
    case 3:
      robot_right(robot);
      break;
    case 4:
      robot_report(robot);
      break;
    default:
      // Do Nothing
      break;
    }
  }

  ht_del_hash_table(known_commands);
  return;
}

void toy_robot_process(FILE* input) {
  char buff[255];
  char* raw_command; // = "";
  char* raw_args; // = "";
  // char** commands;
  // char* delimiter;
  // int delimiter;
  Robot* robot = robot_new(0, 0, "NORTH");

  // fscanf(input, "%s", buff);
  fgets(buff, 16, input);
  //printf("%s\n", buff);

  while(!feof(input) && strncmp(buff, "EXIT", 4) != 0) {
  // while(feof(input) != EOF) {
  // while(fscanf(input, "%s", buff) == 1) {
    // if (feof(input)) { break; }
    // if (strncmp(raw_command, "EXIT", 4)) { break; }

    // raw_command = strtok(buff," ");
    // raw_args = strchr(buff, ' ');

    // while (raw_command != NULL)
    // if (raw_command != NULL)
    // {
    //   printf("%s\n", raw_command);
    //   raw_args = strtok(NULL, " ");
    //   printf("%s\n", raw_args);
    // }
      // printf("%s", raw_command);
      // printf("%s\n", raw_args);

    // if (strlen(buff) > 6) {
    //   // strcpy(raw_args, buff+1+strlen(raw_command));
    //   strncpy(raw_args, buff, 6);
    // }
    // raw_command = strtok(buff, " ");

    // raw_args = strtok(NULL, " ");
    // while (raw_command != NULL && raw_args != NULL)
    // {
    //   raw_args = strtok(NULL, NULL);
    //   printf ("%s\n", raw_args);
    // }
    //raw_args = strtok(NULL, "\n");
    //strncpy(raw_args, buff+1+strlen(raw_command), 9);
    // robot_exec(robot, raw_command, raw_args);
    // robot_exec(robot, raw_command, "3,3,SOUTH");
    // robot_place(robot, "3,3,SOUTH");

      // printf("toy_robot_process(BEFORE): %s \n", buff);
    // commands = str_split(buff, ' ');
    // strcpy(raw_command, commands[0]);
    // if (commands[1] != NULL) {
      // strcpy(raw_args, commands[1]);
    // }
    // raw_command = strtok(buff, " ");

    // if(raw_command) {
    //   printf("%s ", raw_command);
      // printf("toy_robot_process(AFTER): %s \n", buff);
      // printf("toy_robot_process(raw_command): %s \n", raw_command);
      // // raw_args = strtok(NULL, " ");
      // // strncpy(raw_args, buff+strlen(raw_command), strlen(buff)-strlen(raw_command));
      // printf("toy_robot_process(raw_args): %s \n", raw_args);

      // if(raw_args) {
      //   printf("%s", raw_args);
    // char* raw_string = strdup(buff);
    // raw_command = strtok(raw_string, " ");
    // raw_command = strtok(raw_string, " ");
    // const char* delimiter = strchr(buff, ' ');
    // if(delimiter) {
    // char ** commands = strsplit(buff, ' ');
    // if (commands != NULL) {
    //   int i = 0;
    //   while (commands[i]) {
    //     printf("command [%d]: %s\n", i, commands[i]);
    //     i++;
    //   }
    // }
    char* raw_input = strdup(buff);
    char* newline = strchr(raw_input, '\n');
    if (newline) { *newline = 0; }


    // raw_command = strtok(buff, " ");
    raw_command = strtok(raw_input, " ");
    // printf("delimiter = %s ", delimiter);
    // printf("raw_string-delimiter = %ld ", raw_string-delimiter);
    // printf("delimiter-raw_string = %ld ", delimiter-raw_string);
      // strncpy(raw_command, raw_string, raw_string-delimiter);
      // strncpy(raw_command, raw_string, delimiter-raw_string);
    // }
    if(raw_command) { //!= NULL) {
      // raw_args = strstr(buff, " ");
      // raw_args = strtok(buff, " ");
      raw_args = strtok(NULL, " ");
      // raw_args = strtok(NULL, " ");

      if(raw_args) { //!= NULL) {
        robot_exec(robot, raw_command, raw_args);
        // printf("robot_exec(robot, \"%s\", \"%s\"); \n", raw_command, raw_args);
      } else {
        robot_exec(robot, raw_command, "");
        // printf("robot_exec(robot, \"%s\", \"%s\"); \n", raw_command, "");
      }
    }
    //   } else {
    //     robot_exec(robot, raw_command, "");
    //   }
    //   printf("\n");
    // }

    // robot_exec(robot, raw_command, raw_args);

    raw_command = NULL; //"";
    raw_args = NULL; //"";
    // fscanf(input, "%s", buff);
    fgets(buff, 16, input);
  }

  robot_destroy(robot);
  return;
}

int toy_robot_run(char** argv) {
  if (argv[1]) {
    FILE *input;
    input = fopen(argv[1], "r");

    toy_robot_process(input);

    fclose(input);
  } else {
    toy_robot_process(stdin);
  }

  return 0;
}
