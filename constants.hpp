#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// General buffer size
#define BUFFER_SIZE 256

// Commands
#define COMMAND_ENROLL      "enroll"
#define COMMAND_ADVANCE     "advance"
#define COMMAND_CHANGE      "change"
#define COMMAND_GRADUATE    "graduate"
#define COMMAND_INTERRUPT   "interrupt"
#define COMMAND_RESUME      "resume"
#define COMMAND_PRINT       "print"
#define COMMAND_PRINT_ALL   "printall"
#define COMMAND_ENROLL_IN   "enrollin"
#define COMMAND_ADD_GRADE   "addgrade"
#define COMMAND_PROTOCOL    "protocol"
#define COMMAND_REPORT      "report"

// Usage of commands
#define USAGE_ENROLL        "<fn> <program> <group> <name>"
#define USAGE_ADVANCE       "<fn>"
#define USAGE_CHANGE        "<fn> <program|group|year> <value>"
#define USAGE_GRADUATE      "<fn>"
#define USAGE_INTERRUPT     "<fn>"
#define USAGE_RESUME        "<fn>"
#define USAGE_PRINT         "<fn>"
#define USAGE_PRINT_ALL     "<program> <year>"
#define USAGE_ENROLL_IN     "<fn> <course>"
#define USAGE_ADD_GRADE     "<fn> <course> <grade>"
#define USAGE_PROTOCOL      "<course>"
#define USAGE_REPORT        "<fn>"

// Keywords for command 'change'
#define ARGUMENT_CHANGE_PROGRAM "program"
#define ARGUMENT_CHANGE_GROUP   "group"
#define ARGUMENT_CHANGE_YEAR    "year"

// Vector
#define VECTOR_DEFAULT_CAPACITY 16

// PassedCourse
#define MIN_COURSE_GRADE 2
#define MAX_COURSE_GRADE 6

// Student
#define MAX_FAC_NUMBER 1000000
#define MAX_YEAR 4
#define MAX_GROUP 8

#endif // CONSTANTS_HPP
