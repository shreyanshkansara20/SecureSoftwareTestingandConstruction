# Insecure Deserialization
Insecure Deserialization is one of the vulnerability listed in OWASP TOP 10. It is when user-controllable data is deserialized by the website. This potentially enables attacker to manipulate the serialized objects maliciously which is then passed to the website for deserialization.

The impact of insecure deserialization can be very severe. It allows an attacker reuse the existing code in malicious ways resulting in numerous vulnerabilities such as remote code execution (RCE), privilege escalation, arbitrary file access and denial of service (DOS).

The repository consists of several java files which uses XML Serialization and Deserialization. The problem lies with instantiation of object before the type of class comparison i.e. The object of different class can be instantiated before typecasting because of the flaw in programming. Even if it shows ClassCastException, damage is already done with the instantiation of the object of different class.


# Usage
Use the following steps to see Insecure Deserialization

```bash
javac UserSettings.java
```

```bash
javac UserSettings2.java
```

```bash
javac XmlEncoder.java
```

```bash
javac XmlDecoder.java
```

```bash
java XmlEncoder
```

This will create xml file. Now what we can do is modify this file and change the class type to UserSettings2 and baam! The magic happens.

```bash
java XmlDecoder
```

As during the object instantitaion, Default Constructor, Destructor and Static Blocks gets executed, the output will give an assurance that the attack was successful.

# Reference
https://owasp.org/www-community/vulnerabilities/Deserialization_of_untrusted_data

https://owasp.org/www-project-top-ten/2017/A8_2017-Insecure_Deserialization.html

https://portswigger.net/web-security/deserialization
