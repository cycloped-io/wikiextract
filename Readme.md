# Wikiextract

The utility converts the source Wikipedia text into pair of files:

* links.csv
 * id
 * line start
 * line end
 * column start
 * column stop
 * concept name
 * link name
* segments.csv
 * id
 * line start
 * line stop
 * column start
 * column stop
 * token type
 * segment

These files are useful for computing statistics of the number of links appearing
in the text for a given expression, etc.
