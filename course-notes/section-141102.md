# CS50 Section 02-November-2014

* Controller - logic
* Model - database SQL, json
* View - how website is actually shown to the user
* In pset 7
* mysql is database
* phpmyadmin helps to view the sql database
* PhP is a web-based language, runs on webserver, allows us to dynamically generate a website
* PhP variables always start with `$` sign
* `$_GET` every variable we passed to form

```php
<?php
    foreach($names as $name)
    {
        print("<li>$name</li>")
    }
?>
```

* `<?= ?>` basically one variable in here to output it
* Templates = view

```sql
SELECT * FROM users WHERE
SELECT id FROM
```

* `*` is everything
* = ?", everything to replace ? with
* Remember to use backtick in phpmyadmin and not single quotes:

```sql
SELECT * FROM `users` WHERE username = ...
```

* Sanitizing inputs
* `<b>Robbie</b>` wont actually print out bold...
