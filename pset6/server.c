//
// server.c
//
// David J. Malan
// malan@harvard.edu
//

// feature test macro requirements
#define _GNU_SOURCE
// Remove the following line to compile on OSX?
// #define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED

// limits on an HTTP request's size, based on Apache's
// http://httpd.apache.org/docs/2.2/mod/core.html
#define LimitRequestFields 50
#define LimitRequestFieldSize 4094
#define LimitRequestLine 8190

// number of octets for buffered reads
#define OCTETS 512

// header files
#include <arpa/inet.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include <ctype.h>

// types
typedef char octet;

// prototypes
bool connected(void);
bool error(unsigned short code);
void handler(int signal);
ssize_t load(void);
const char* lookup(const char* extension);
ssize_t parse(void);
void reset(void);
void start(short port, const char* path);
void stop(void);

// server's root
char* root = NULL;

// file descriptor for sockets
int cfd = -1, sfd = -1;

// buffer for request
octet* request = NULL;

// FILE pointer for files
FILE* file = NULL;

// buffer for response-body
octet* body = NULL;

// length of file extension
int len_ext = 0;

int main(int argc, char* argv[])
{
    // a global variable defined in errno.h that's "set by system
    // calls and some library functions [to a nonzero value]
    // in the event of an error to indicate what went wrong"
    errno = 0;

    // default to a random port
    int port = 0;

    // usage
    const char* usage = "Usage: server [-p port] /path/to/root";

    // parse command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, "hp:")) != -1)
    {
        switch (opt)
        {
            // -h
            case 'h':
                printf("%s\n", usage);
                return 0;

            // -p port
            case 'p':
                port = atoi(optarg);
                break;
        }
    }

    // ensure port is a non-negative short and path to server's root is specified
    if (port < 0 || port > SHRT_MAX || argv[optind] == NULL || strlen(argv[optind]) == 0)
    {
        // announce usage
        printf("%s\n", usage);

        // return 2 just like bash's builtins
        return 2;
    }

    // start server
    start(port, argv[optind]);

    // listen for SIGINT (aka control-c)
    signal(SIGINT, handler);

    // accept connections one at a time
    while (true)
    {
        // reset server's state
        reset();

        // wait until client is connected
        if (connected())
        {
            // parse client's HTTP request
            ssize_t octets = parse();
            if (octets == -1)
            {
                continue;
            }

            // extract request's request-line
            // http://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html
            const char* haystack = request;
            char* needle = strstr(haystack, "\r\n");
            if (needle == NULL)
            {
                error(400);
                continue;
            }
            else if (needle - haystack + 2 > LimitRequestLine)
            {
                error(414);
                continue;
            }
            char line[needle - haystack + 2 + 1];
            strncpy(line, haystack, needle - haystack + 2);
            line[needle - haystack + 2] = '\0';

            // log request-line
            printf("%s", line);

            // TODO: validate request-line

            // Ensure that request-line (which is already stored for you in a variable called line) is consistent with these rules.
            // If it is not, respond to the browser with 400 Bad Request.

            // loop through line to see if it has the right structure
            // (TODO put something here so its not infinite if it never finds CRLF)

            // request-target has two parts: absolute-path and query
            int len_line = needle - haystack + 1;
            int len_method = 0;
            int len_reqt = 0;
            int len_httpv = 0;
            int idx_reqt = 0;

            // get the length of the portion of request-line that is method by looking for first space
            for(int i = 0; line[i] != 32; i++)
            {
                // check that the end of request-line hasn't been reached without having found first space, or method name is not too long
                if ((line[i] == 10 && line[i-1] == 13) || i > 100)
                {
                    error(400);
                    continue;
                }
                else
                {
                    len_method = i + 1;
                }
            }

            // get the index of end of request-target, stopping when second space character is reached
            for(int i = len_method + 1; line[i] != 32; i++)
            {
                // check that the end of request-line hasn't been reached without having found the second space, or request-target isn't too long
                if ((line[i] == 10 && line[i-1] == 13) || i > 100 + len_method)
                {
                    error(400);
                    continue;
                }
                else
                {
                    idx_reqt = i;
                }
            }

            // calculate the length of request-target from the last index of request-target in request-line
            len_reqt = idx_reqt - len_method;

            // calculate the length of the HTTP-verion
            len_httpv = len_line - idx_reqt - 3;

            // further verify format of request-line
            if (len_method == 0 || len_reqt ==0 || len_httpv == 0 || (line[len_line] != 10 && line[len_line - 1] != 13))
            {
                error(400);
                continue;
            }

            // if first line of request-target does not begin with '/'
            if (line[len_method + 1] != 47)
            {
                error(501);
                continue;
            }

            // check that request-target does NOT contain a '"'
            for (int i = len_method + 1; i < len_method + len_reqt + 1; i++)
            {
                if (line[i] == 34)
                {
                    error(400);
                    continue;
                }
            }

            // TODO

            // declare the request-target string and allocate the right amount of memory for it
            char request[len_reqt + 1];

            // set the request-target string with the data from request-line
            for (int i = 0; i < len_reqt + 1; i++)
            {
                request[i] = line[len_method + i + 1];
            }

            // declare integer that is location of period
            int idx_per = 0;

            for (int i = 0; request[i] != 46; i++)
            {
                if (i > 300)
                {
                    error(501);
                    continue;
                }
                idx_per = idx_per + 1;
            }

            // declare a string which holds the method name
            char method[len_method + 1];

            // now check that the method is GET
            if (len_method == 3)
            {
                // populate the method string with the method info from the line string
                for (int i = 0; i < len_method + 1; i++)
                {
                    method[i] = line[i];
                }

                // make last character in method string the null character
                method[len_method] = '\0';

                // check that the method is get
                if (strcmp(method, "GET") != 0)
                {
                    error(405);
                    continue;
                }
            }
            else
            {
                error(405);
                continue;
            }

            // declare a string which holds the http-version name
            char httpv[len_httpv + 1];

            // now check that http-version is equal to HTTP/1.1
            if (len_httpv == 8)
            {
                // populate the method string with the http-version info from the line string
                for (int i = 0; i < len_httpv + 0; i++)
                {
                    httpv[i] = line[len_method + len_reqt + 2 + i];
                }

                // make last character in method string the null character
                httpv[len_httpv] = '\0';

                // check that the version is HTTP/1.1
                if (strcmp(httpv, "HTTP/1.1") != 0)
                {
                    error(505);
                    continue;
                }
            }
            else
            {
                error(505);
                continue;
            }

            // TODO: extract query from request-target

            int len_query = 0;
            int len_abspath = 0;

            // go through request-target until '?' is reached, marking end of path and beginning of query
            for (int i = 1; request[i-1] != 63 && i <= len_reqt; i++)
            {
                len_abspath = i;
            }

            // calculate the length of the query
            if (len_reqt == len_abspath)
            {
                len_query = 0;
            }
            else
            {
                len_query = len_reqt - len_abspath - 1;
            }

            // declare a string to store the query
            char query[len_query + 1];

            // take the query from the request-target
            if (len_query == 0)
            {
                query[0] = '\0';
            }
            else
            {
                for (int i = 0; i < len_query; i++)
                {
                    query[i] = request[len_abspath + i + 1];
                }
            }

            // end of query string is null character
            query[len_query] = '\0';

            // declare a string for the absolute-path
            char abspath[len_abspath + 1];

            if (len_abspath == 0)
            {
                abspath[0] = '\0';
            }
            else
            {
                for (int i = 0; i < len_abspath; i++)
                {
                    abspath[i] = request[i];
                }
            }

            // end of absolute-path string is null character
            abspath[len_abspath] = '\0';

            // TODO: concatenate root and absolute-path
            int len_root = strlen(root);
            int len_path = len_root + len_abspath;

            char path[len_path + 1];

            for (int i = 0; i < len_root; i++)
            {
                path[i] = root[i];
            }

            for (int i = len_root; i < len_path; i++)
            {
                path[i] = abspath[i - len_root];
            }

            // end of path string is null character
            path[len_path] = '\0';

            // TODO: ensure path exists
            int ex_path = 1;
            ex_path = access(path, F_OK);

            if (ex_path != 0)
            {
                error(404);
                continue;
            }

            // TODO: ensure path is readable
            int rd_path = 1;
            rd_path = access(path, R_OK);

            if (rd_path != 0)
            {
                error(403);
                continue;
            }

            // TODO: extract path's extension

            len_ext = len_abspath - idx_per - 1;

            char extension[len_ext + 1];

            for (int i = 0; i < len_ext; i++)
            {
                extension[i] = abspath[idx_per + 1 + i];
            }

            // end of extension string is null character
            extension[len_ext] = '\0';

            // dynamic content
            if (strcasecmp("php", extension) == 0)
            {
                // open pipe to PHP interpreter
                char* format = "QUERY_STRING=\"%s\" REDIRECT_STATUS=200 SCRIPT_FILENAME=\"%s\" php-cgi";
                char command[strlen(format) + (strlen(path) - 2) + (strlen(query) - 2) + 1];
                sprintf(command, format, query, path);
                file = popen(command, "r");
                if (file == NULL)
                {
                    error(500);
                    continue;
                }

                // load file
                ssize_t size = load();
                if (size == -1)
                {
                    error(500);
                    continue;
                }

                // subtract php-cgi's headers from body's size to get content's length
                haystack = body;
                needle = memmem(haystack, size, "\r\n\r\n", 4);
                if (needle == NULL)
                {
                    error(500);
                    continue;
                }
                size_t length = size - (needle - haystack + 4);

                // respond to client
                if (dprintf(cfd, "HTTP/1.1 200 OK\r\n") < 0)
                {
                    continue;
                }
                if (dprintf(cfd, "Connection: close\r\n") < 0)
                {
                    continue;
                }
                if (dprintf(cfd, "Content-Length: %i\r\n", length) < 0)
                {
                    continue;
                }
                if (write(cfd, body, size) == -1)
                {
                    continue;
                }
            }
            // static content
            else
            {
                // look up file's MIME type
                const char* type = lookup(extension);

                if (type == NULL)
                {
                    error(501);
                    continue;
                }

                // open file
                file = fopen(path, "r");
                if (file == NULL)
                {
                    error(500);
                    continue;
                }

                // load file
                ssize_t length = load();
                if (length == -1)
                {
                    error(500);
                    continue;
                }

                // TODO: respond to client
                if (dprintf(cfd, "HTTP/1.1 200 OK\r\n") < 0)
                {
                    continue;
                }
                if (dprintf(cfd, "Connection: close\r\n") < 0)
                {
                    continue;
                }
                if (dprintf(cfd, "Content-Length: %i\r\n", length) < 0)
                {
                    continue;
                }
                if (dprintf(cfd, "Content-type: %s\r\n\r\n", type) < 0)
                {
                    continue;
                }
                if (write(cfd, body, length) == -1)
                {
                    continue;
                }
            }

            // announce OK
            printf("\033[32m");
            printf("HTTP/1.1 200 OK");
            printf("\033[39m\n");
        }
    }
}

/**
 * Accepts a connection from a client, blocking (i.e., waiting) until one is heard.
 * Upon success, returns true; upon failure, returns false.
 */
bool connected(void)
{
    struct sockaddr_in cli_addr;
    memset(&cli_addr, 0, sizeof(cli_addr));
    socklen_t cli_len = sizeof(cli_addr);
    cfd = accept(sfd, (struct sockaddr*) &cli_addr, &cli_len);
    if (cfd == -1)
    {
        return false;
    }
    return true;
}

/**
 * Handles client errors (4xx) and server errors (5xx).
 */
bool error(unsigned short code)
{
    // ensure client's socket is open
    if (cfd == -1)
    {
        return false;
    }

    // ensure code is within range
    if (code < 400 || code > 599)
    {
        return false;
    }

    // determine Status-Line's phrase
    // http://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6.1
    const char* phrase = NULL;
    switch (code)
    {
        case 400: phrase = "Bad Request"; break;
        case 403: phrase = "Forbidden"; break;
        case 404: phrase = "Not Found"; break;
        case 405: phrase = "Method Not Allowed"; break;
        case 413: phrase = "Request Entity Too Large"; break;
        case 414: phrase = "Request-URI Too Long"; break;
        case 418: phrase = "I'm a teapot"; break;
        case 500: phrase = "Internal Server Error"; break;
        case 501: phrase = "Not Implemented"; break;
        case 505: phrase = "HTTP Version Not Supported"; break;
    }
    if (phrase == NULL)
    {
        return false;
    }

    // template
    char* template = "<html><head><title>%i %s</title></head><body><h1>%i %s</h1></body></html>";
    char content[strlen(template) + 2 * ((int) log10(code) + 1 - 2) + 2 * (strlen(phrase) - 2) + 1];
    int length = sprintf(content, template, code, phrase, code, phrase);

    // respond with Status-Line
    if (dprintf(cfd, "HTTP/1.1 %i %s\r\n", code, phrase) < 0)
    {
        return false;
    }

    // respond with Connection header
    if (dprintf(cfd, "Connection: close\r\n") < 0)
    {
        return false;
    }

    // respond with Content-Length header
    if (dprintf(cfd, "Content-Length: %i\r\n", length) < 0)
    {
        return false;
    }

    // respond with Content-Type header
    if (dprintf(cfd, "Content-Type: text/html\r\n") < 0)
    {
        return false;
    }

    // respond with CRLF
    if (dprintf(cfd, "\r\n") < 0)
    {
        return false;
    }

    // respond with message-body
    if (write(cfd, content, length) == -1)
    {
        return false;
    }

    // announce Response-Line
    printf("\033[31m");
    printf("%i %s", code, phrase);
    printf("\033[39m\n");

    return true;
}

/**
 * Loads file into message-body.
 */
ssize_t load(void)
{
    // ensure file is open
    if (file == NULL)
    {
        return -1;
    }

    // ensure body isn't already loaded
    if (body != NULL)
    {
        return -1;
    }

    // buffer for octets
    octet buffer[OCTETS];

    // read file
    ssize_t size = 0;
    while (true)
    {
        // try to read a buffer's worth of octets
        ssize_t octets = fread(buffer, sizeof(octet), OCTETS, file);

        // check for error
        if (ferror(file) != 0)
        {
            if (body != NULL)
            {
                free(body);
                body = NULL;
            }
            return -1;
        }

        // if octets were read, append to body
        if (octets > 0)
        {
            body = realloc(body, size + octets);
            if (body == NULL)
            {
                return -1;
            }
            memcpy(body + size, buffer, octets);
            size += octets;
        }

        // check for EOF
        if (feof(file) != 0)
        {
            break;
        }
    }
    return size;
}

/**
 * Handles signals.
 */
void handler(int signal)
{
    // control-c
    if (signal == SIGINT)
    {
        // ensure this isn't considered an error
        // (as might otherwise happen after a recent 404)
        errno = 0;

        // announce stop
        printf("\033[33m");
        printf("Stopping server\n");
        printf("\033[39m");

        // stop server
        stop();
    }
}

/**
 * Returns MIME type for supported extensions, else NULL.
 */
const char* lookup(const char* extension)
{
    // TODO

    // leave extension as a constant and declare a new string that will be extension, but lowercase
    char ext[len_ext + 1];
    ext[len_ext] = '\0';

    // lowercase each character of extension and assign it to lowercase extension string
    for (int i = 0; i < len_ext; i++)
    {
       ext[i] = tolower(extension[i]);
    }

    // check the lowercase extension is css, html, gif, etc and return appropriate MIME type
    if (strcmp(ext, "css") == 0)
    {
        return "text/css";
    }
    else if (strcmp(ext, "html") == 0)
    {
        return "text/html";
    }
    else if (strcmp(ext, "gif") == 0)
    {
        return "image/gif";
    }
    else if (strcmp(ext, "ico") == 0)
    {
        return "image/x-icon";
    }
    else if (strcmp(ext, "jpg") == 0)
    {
        return "image/jpeg";
    }
    else if (strcmp(ext, "js") == 0)
    {
        return "text/javascript";
    }
    else if (strcmp(ext, "png") == 0)
    {
        return "image/png";
    }
    else
    {
        return NULL;
    }
}

/**
 * Parses an HTTP request.
 */
ssize_t parse(void)
{
    // ensure client's socket is open
    if (cfd == -1)
    {
        return -1;
    }

    // ensure request isn't already parsed
    if (request != NULL)
    {
        return -1;
    }

    // buffer for octets
    octet buffer[OCTETS];

    // parse request
    ssize_t length = 0;
    while (true)
    {
        // read from socket
        ssize_t octets = read(cfd, buffer, sizeof(octet) * OCTETS);
        if (octets == -1)
        {
            error(500);
            return -1;
        }

        // if octets have been read, remember new length
        if (octets > 0)
        {
            request = realloc(request, length + octets);
            if (request == NULL)
            {
                return -1;
            }
            memcpy(request + length, buffer, octets);
            length += octets;
        }

        // else if nothing's been read, socket's been closed
        else
        {
            return -1;
        }

        // search for CRLF CRLF
        int offset = (length - octets < 3) ? length - octets : 3;
        char* haystack = request + length - octets - offset;
        char* needle = memmem(haystack, request + length - haystack, "\r\n\r\n", 4);
        if (needle != NULL)
        {
            // trim to one CRLF and null-terminate
            length = needle - request + 2 + 1;
            request = realloc(request, length);
            if (request == NULL)
            {
                return -1;
            }
            request[length - 1] = '\0';
            break;
        }

        // if buffer's full and we still haven't found CRLF CRLF,
        // then request is too large
        if (length - 1 >= LimitRequestLine + LimitRequestFields * LimitRequestFieldSize)
        {
            error(413);
            return -1;
        }
    }
    return length;
}

/**
 * Resets server's state, deallocating any resources.
 */
void reset(void)
{
    // free response's body
    if (body != NULL)
    {
        free(body);
        body = NULL;
    }

    // close file
    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }

    // free request
    if (request != NULL)
    {
        free(request);
        request = NULL;
    }

    // close client's socket
    if (cfd != -1)
    {
        close(cfd);
        cfd = -1;
    }
}

/**
 * Starts server.
 */
void start(short port, const char* path)
{
    // path to server's root
    root = realpath(path, NULL);
    if (root == NULL)
    {
        stop();
    }

    // ensure root exists
    if (access(root, F_OK) == -1)
    {
        stop();
    }

    // ensure root is executable
    if (access(root, X_OK) == -1)
    {
        stop();
    }

    // announce root
    printf("\033[33m");
    printf("Using %s for server's root", root);
    printf("\033[39m\n");

    // create a socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        stop();
    }

    // allow reuse of address (to avoid "Address already in use")
    int optval = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // assign name to socket
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
    {
        stop();
    }

    // listen for connections
    if (listen(sfd, SOMAXCONN) == -1)
    {
        stop();
    }

    // announce port in use
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    if (getsockname(sfd, (struct sockaddr*) &addr, &addrlen) == -1)
    {
        stop();
    }
    printf("\033[33m");
    printf("Listening on port %i", ntohs(addr.sin_port));
    printf("\033[39m\n");
}

/**
 * Stop server, deallocating any resources.
 */
void stop(void)
{
    // preserve errno across this function's library calls
    int errsv = errno;

    // reset server's state
    reset();

    // free root, which was allocated by realpath
    if (root != NULL)
    {
        free(root);
    }

    // close server socket
    if (sfd != -1)
    {
        close(sfd);
    }

    // terminate process
    if (errsv == 0)
    {
        // success
        exit(0);
    }
    else
    {
        // announce error
        printf("\033[33m");
        printf("%s", strerror(errsv));
        printf("\033[39m\n");

        // failure
        exit(1);
    }
}
