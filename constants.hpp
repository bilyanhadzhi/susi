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
#define COMMAND_OPEN        "open"
#define COMMAND_CLOSE       "close"
#define COMMAND_SAVE        "save"
#define COMMAND_SAVE_AS     "save_as"
#define COMMAND_HELP        "help"
#define COMMAND_EXIT        "exit"

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
#define USAGE_OPEN          "<filename>"
#define USAGE_SAVE_AS       "<filename>"

// Keywords for command 'change'
#define ARGUMENT_CHANGE_PROGRAM "program"
#define ARGUMENT_CHANGE_GROUP   "group"
#define ARGUMENT_CHANGE_YEAR    "year"

// Course Type names
#define NAME_COURSE_TYPE_NONE           "none"
#define NAME_COURSE_TYPE_MANDATORY      "mandatory"
#define NAME_COURSE_TYPE_FREE_ELECTIVE  "free elective"

// Student status names
#define NAME_STUDENT_STATUS_NONE        "none"
#define NAME_STUDENT_STATUS_ACTIVE      "active"
#define NAME_STUDENT_STATUS_INTERRUPTED "interrupted"
#define NAME_STUDENT_STATUS_GRADUATED   "graduated"

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
