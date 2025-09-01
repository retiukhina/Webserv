# Webserv

#ARCHITECTURE CONCEPTS

event-driven architecture: non-blocking I/O operations; all network I/O must go through poll();use non-blocking sockets + poll() with timeouts and close connections that are idle for too long; fork is only allowed for CGI scripts execution (external programs like PHP) - this enforces a single-process, non-blocking server architecture for normal requests.

#SECURITY MESSURES

Content-Length of HTTP header tells your server how many bytes to expect, but it’s controlled by the client. Always validate it, limit it, and read incrementally to prevent attacks.