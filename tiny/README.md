# Tiny Web Server
This is a Tiny Web Server provided by Carnegie Mellon University. Tiny uses the GET method to serve static content (text, HTML, GIF, and JPG files) out of ./ and to serve dynamic content by running CGI programs out of ./cgi-bin. The default page is home.html (rather than index.html) so that we can view the contents of the directory from a browser. This web server gives real idea to us of how web servers in real world works.

So when you download this server source files from CMU's Wesbite, the orginal server code comes with couple of vulnerabilities in order to teach students how to find vulnerabilities, what are those vulnerabilities and how to fight against them i.e. how to patch those vulnerabilities.

This project has patched version of the source code. The patches are made for Integer Overflow, File Path Traversal Vulnerability, Command Injection Vulnerability, Buffer Overflows and Format String Vulnerability.

According to the original source code, the server serves GET requests and one connection at a time. While this project includes modified source code which helps the server to server GET as well as POST requests and also can handle multiple connections from multiple clients.

# Configuration
Kindly read the README_tiny file present in this repo for the configuration of the server

# Usage
You can connect to the server either through the browser or via using telnet
Visit http://<host>:<port> in the browser

OR

```bash
telnet 127.0.0.1 <port>
```
You can request GET as well as POST. Basically POST request is required in order to server the dyanmic content here. So difference in the queries while using GET and POST request is shown below:

GET Request
```bash
telnet 127.0.0.1 <port>

GET /cgi-bin/adder?1&2
```

POST Request
```bash
telnet 127.0.0.1 <port>

POST /cgi-bin/adder

5&5
```

# References
http://www.cs.cmu.edu/afs/cs/academic/class/15213-f08/www/code/tiny/
