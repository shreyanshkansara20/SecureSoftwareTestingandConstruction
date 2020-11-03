# XML External Entity (XXE) Injection
XML External Entity Injection is a web security vulnerability that enables an attacker to interfere with the application that is processing XML data. It allows an attacker to view files on the server filesystem, and to interact with any back-end or external system that application itself can access.

This repo shows sample XXE injection attack. It's a simple java application that reads data from XML file. This is where we can do some mischief.

# Usage

```bash
javac parseDocument.java
```
This will create a class file. We need to create/have contacts.xml so that our code can fetch data from it. This is where we can perform the XXE injection attack by adding an external entity. One can refer to contacts.xml and contacts.dtd for more information.

```bash
java parseDocument
```

After executing the code, the injected functionality will be executed.


# References
https://portswigger.net/web-security/xxe
https://owasp.org/www-community/vulnerabilities/XML_External_Entity_(XXE)_Processing
