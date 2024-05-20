#!/usr/bin/env python

import cgi

# Parse the CGI form data
form = cgi.FieldStorage()

# Retrieve query parameters
your_name = form.getvalue('your_name')
company_name = form.getvalue('company_name')

# Print HTML response
print("<html>")
print("<head><title>CGI Example</title></head>")
print("<body>")
print("<h1>Hello, {} is working in {}</h1>".format(your_name, company_name))
print("</body>")
print("</html>")
