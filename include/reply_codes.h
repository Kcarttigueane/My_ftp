/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** reply_codes.h
*/

#pragma once

// ! Informational:

#define FTP_REPLY_110 "110 Restart marker reply.\r\n"
#define FTP_REPLY_120 "120 Service ready in nnn minutes.\r\n"
#define FTP_REPLY_125 "125 Data connection already open; transfer starting.\r\n"
#define FTP_REPLY_150 "150 File status okay; about to open data connection.\r\n"

// ! Successful:

#define FTP_REPLY_200 "200 Command okay.\r\n"
#define FTP_REPLY_226 \
    "226 Closing data connection. Requested file action successful.\r\n"
#define FTP_REPLY_250 "250 Requested file action okay, completed.\r\n"
#define FTP_REPLY_257 "257 " % s " created.\r\n"
#define FTP_REPLY_331 "331 User name okay, need password.\r\n"
#define FTP_REPLY_230 "230 User logged in, proceed.\r\n"

// ! Positive Intermediate:

#define FTP_REPLY_211 "211 System status, or system help reply.\r\n"
#define FTP_REPLY_212 "212 Directory status.\r\n"
#define FTP_REPLY_213 "213 File status.\r\n"
// #define FTP_REPLY_214 "214 Help message.\r\n"
#define FTP_REPLY_214 "214 Help message."
#define FTP_REPLY_215 "215 NAME system type.\r\n"
#define FTP_REPLY_220 "220 Service ready for new user.\r\n"
#define FTP_REPLY_221 "221 Service closing control connection.\r\n"
#define FTP_REPLY_225 "225 Data connection open; no transfer in progress.\r\n"
#define FTP_REPLY_227 "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n"
#define FTP_REPLY_229 "229 Entering Extended Passive Mode (|||port|).\r\n"
#define FTP_REPLY_232 "232 Login security extension active.\r\n"

// ! Transient Negative:

#define FTP_REPLY_421 \
    "421 Service not available, closing control connection.\r\n"
#define FTP_REPLY_425 "425 Can't open data connection.\r\n"
#define FTP_REPLY_426 "426 Connection closed; transfer aborted.\r\n"
#define FTP_REPLY_430 "430 Invalid username or password.\r\n"
#define FTP_REPLY_450 "450 Requested file action not taken.\r\n"
#define FTP_REPLY_452                                                \
    "452 Requested action not taken. Insufficient storage space in " \
    "system.\r\n"

// ! Permanent Negative:

#define FTP_REPLY_500 "500 Syntax error, command unrecognized.\r\n"
#define FTP_REPLY_501 "501 Syntax error in parameters or arguments.\r\n"
#define FTP_REPLY_502 "502 Command not implemented.\r\n"
#define FTP_REPLY_503 "503 Bad sequence of commands.\r\n"
#define FTP_REPLY_504 "504 Command not implemented for that parameter.\r\n"
#define FTP_REPLY_530 "530 Not logged in.\r\n"
#define FTP_REPLY_532 "532 Need account for storing files.\r\n"
#define FTP_REPLY_550                                                          \
    "550 Requested action not taken. File unavailable (e.g., file not found, " \
    "no access).\r\n"
#define FTP_REPLY_551 "551 Requested action aborted: page type unknown.\r\n"
#define FTP_REPLY_552                                                      \
    "552 Requested file action aborted. Exceeded storage allocation (for " \
    "current directory or dataset).\r\n"
#define FTP_REPLY_553 "553 Requested action not taken. File name not allowed.\r"
