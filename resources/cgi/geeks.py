#!/usr/bin/env python

import cgi

# Parse the CGI form data
form = cgi.FieldStorage()

# Retrieve query parameters
your_name = form.getvalue('your_name')
company_name = form.getvalue('company_name')

# Print HTML response with styling
print("<html>")
print("<head>")
print("<title>CGI Example</title>")
print("<style>")
print("body {")
print("    background-color: #f0f0f0;")  # Light gray background color
print("    font-family: Arial, sans-serif;")  # Use Arial font
print("    padding: 20px;")  # Add padding to the body
print("}")
print("h1 {")
print("    color: #333333;")  # Dark gray heading color
print("}")
print("</style>")
print("</head>")
print("<body>")
print("<h1>Hello, {} is working in {}</h1>".format(your_name, company_name))
print("</body>")
print("</html>")
